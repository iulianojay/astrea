#pragma once

#include <astro/frames/frame_utilities.hpp>
#include <astro/systems/CelestialBody.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif

namespace astrea {
namespace astro {
namespace barycenters {

inline constexpr struct SolarSystemBarycenter final : Barycenter<"Solar System Barycenter"> {
} SolarSystemBarycenter;

inline constexpr struct MercuryBarycenter final : Barycenter<"Mercury Barycenter", SolarSystemBarycenter> {
} MercuryBarycenter;

inline constexpr struct VenusBarycenter final : Barycenter<"Venus Barycenter", SolarSystemBarycenter> {
} VenusBarycenter;

inline constexpr struct EarthBarycenter final : Barycenter<"Earth Barycenter", SolarSystemBarycenter> {
} EarthBarycenter;

inline constexpr struct MarsBarycenter final : Barycenter<"Mars Barycenter", SolarSystemBarycenter> {
} MarsBarycenter;

inline constexpr struct JupiterBarycenter final : Barycenter<"Jupiter Barycenter", SolarSystemBarycenter> {
} JupiterBarycenter;

inline constexpr struct SaturnBarycenter final : Barycenter<"Saturn Barycenter", SolarSystemBarycenter> {
} SaturnBarycenter;

inline constexpr struct UranusBarycenter final : Barycenter<"Uranus Barycenter", SolarSystemBarycenter> {
} UranusBarycenter;

inline constexpr struct NeptuneBarycenter final : Barycenter<"Neptune Barycenter", SolarSystemBarycenter> {
} NeptuneBarycenter;

inline constexpr struct EarthMoonBarycenter final : Barycenter<"Earth-Moon Barycenter", SolarSystemBarycenter> {
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
    return get_position_at_impl<planets::EmbEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr auto get_velocity_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(barycenters::EarthMoonBarycenter, axes::icrf);
    return get_velocity_at_impl<planets::EmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea