

# File barycenters.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**barycenters.hpp**](barycenters_8hpp.md)

[Go to the documentation of this file](barycenters_8hpp.md)


```C++
#pragma once

#include <astro/frames/framework/frame_utilities.hpp>
#include <astro/systems/Barycenter.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif

namespace astrea {
namespace astro {

// Forward declarations — types only; completeness not required because member bodies
// are stored via CelestialBodyTypePack<Ts...>{}, which has no data members.

namespace star {

struct Sun;

} // namespace star

namespace planets {

struct Mercury;
struct Venus;
struct Earth;
struct Mars;
struct Jupiter;
struct Saturn;
struct Uranus;
struct Neptune;

} // namespace planets

namespace moons {

struct Moon;

} // namespace moons

namespace barycenters {

inline constexpr struct SolarSystemBarycenter final
    : Barycenter<"Solar System Barycenter">,
      CelestialBodyTypePack<star::Sun, planets::Mercury, planets::Venus, planets::Earth, planets::Mars, planets::Jupiter, planets::Saturn, planets::Uranus, planets::Neptune> {
} SolarSystemBarycenter;

inline constexpr struct MercurySunBarycenter final : Barycenter<"Mercury Barycenter", SolarSystemBarycenter>,
                                                     CelestialBodyTypePack<star::Sun, planets::Mercury> {
} MercurySunBarycenter;

inline constexpr struct VenusSunBarycenter final : Barycenter<"Venus Barycenter", SolarSystemBarycenter>,
                                                   CelestialBodyTypePack<star::Sun, planets::Venus> {
} VenusSunBarycenter;

inline constexpr struct EarthSunBarycenter final : Barycenter<"Earth Barycenter", SolarSystemBarycenter>,
                                                   CelestialBodyTypePack<star::Sun, planets::Earth> {
} EarthSunBarycenter;

inline constexpr struct MarsSunBarycenter final : Barycenter<"Mars Barycenter", SolarSystemBarycenter>,
                                                  CelestialBodyTypePack<star::Sun, planets::Mars> {
} MarsSunBarycenter;

inline constexpr struct JupiterSunBarycenter final : Barycenter<"Jupiter Barycenter", SolarSystemBarycenter>,
                                                     CelestialBodyTypePack<star::Sun, planets::Jupiter> {
} JupiterSunBarycenter;

inline constexpr struct SaturnSunBarycenter final : Barycenter<"Saturn Barycenter", SolarSystemBarycenter>,
                                                    CelestialBodyTypePack<star::Sun, planets::Saturn> {
} SaturnSunBarycenter;

inline constexpr struct UranusSunBarycenter final : Barycenter<"Uranus Barycenter", SolarSystemBarycenter>,
                                                    CelestialBodyTypePack<star::Sun, planets::Uranus> {
} UranusSunBarycenter;

inline constexpr struct NeptuneSunBarycenter final : Barycenter<"Neptune Barycenter", SolarSystemBarycenter>,
                                                     CelestialBodyTypePack<star::Sun, planets::Neptune> {
} NeptuneSunBarycenter;

inline constexpr struct EarthMoonBarycenter final : Barycenter<"Earth-Moon Barycenter", SolarSystemBarycenter>,
                                                    CelestialBodyTypePack<planets::Earth, moons::Moon> {
} EarthMoonBarycenter;


} // namespace barycenters

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf)>
    get_position_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_position_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf)>
    get_velocity_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_velocity_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf)>
    get_acceleration_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_acceleration_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea
```


