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

/**
 * @brief Get the position of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf)>
    get_position_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_position_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf)>
    get_velocity_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_velocity_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea