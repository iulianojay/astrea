#pragma once

#include <astro/frames/frame_utilities.hpp>
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

inline constexpr struct MercuryBarycenter final : Barycenter<"Mercury Barycenter", SolarSystemBarycenter>,
                                                  CelestialBodyTypePack<star::Sun, planets::Mercury> {
} MercuryBarycenter;

inline constexpr struct VenusBarycenter final : Barycenter<"Venus Barycenter", SolarSystemBarycenter>,
                                                CelestialBodyTypePack<star::Sun, planets::Venus> {
} VenusBarycenter;

inline constexpr struct EarthBarycenter final : Barycenter<"Earth Barycenter", SolarSystemBarycenter>,
                                                CelestialBodyTypePack<star::Sun, planets::Earth> {
} EarthBarycenter;

inline constexpr struct MarsBarycenter final : Barycenter<"Mars Barycenter", SolarSystemBarycenter>,
                                               CelestialBodyTypePack<star::Sun, planets::Mars> {
} MarsBarycenter;

inline constexpr struct JupiterBarycenter final : Barycenter<"Jupiter Barycenter", SolarSystemBarycenter>,
                                                  CelestialBodyTypePack<star::Sun, planets::Jupiter> {
} JupiterBarycenter;

inline constexpr struct SaturnBarycenter final : Barycenter<"Saturn Barycenter", SolarSystemBarycenter>,
                                                 CelestialBodyTypePack<star::Sun, planets::Saturn> {
} SaturnBarycenter;

inline constexpr struct UranusBarycenter final : Barycenter<"Uranus Barycenter", SolarSystemBarycenter>,
                                                 CelestialBodyTypePack<star::Sun, planets::Uranus> {
} UranusBarycenter;

inline constexpr struct NeptuneBarycenter final : Barycenter<"Neptune Barycenter", SolarSystemBarycenter>,
                                                  CelestialBodyTypePack<star::Sun, planets::Neptune> {
} NeptuneBarycenter;

inline constexpr struct EarthMoonBarycenter final : Barycenter<"Earth-Moon Barycenter", SolarSystemBarycenter>,
                                                    CelestialBodyTypePack<planets::Earth, moons::Moon> {
} EarthMoonBarycenter;


} // namespace barycenters

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr auto get_position_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_position_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr auto get_velocity_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_velocity_at_impl<ephemerides::EmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea