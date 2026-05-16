#pragma once

#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif

namespace astrea {
namespace astro {
namespace barycenters {

inline constexpr struct SolarSystemBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Solar System Barycenter" }> {
} SolarSystemBarycenter;

inline constexpr struct MercuryBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Mercury Barycenter" }, SolarSystemBarycenter> {
} MercuryBarycenter;

inline constexpr struct VenusBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Venus Barycenter" }, SolarSystemBarycenter> {
} VenusBarycenter;

inline constexpr struct EarthBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Earth Barycenter" }, SolarSystemBarycenter> {
} EarthBarycenter;

inline constexpr struct MarsBarycenter final : Barycenter<mp_units::basic_fixed_string{ "Mars Barycenter" }, SolarSystemBarycenter> {
} MarsBarycenter;

inline constexpr struct JupiterBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Jupiter Barycenter" }, SolarSystemBarycenter> {
} JupiterBarycenter;

inline constexpr struct SaturnBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Saturn Barycenter" }, SolarSystemBarycenter> {
} SaturnBarycenter;

inline constexpr struct UranusBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Uranus Barycenter" }, SolarSystemBarycenter> {
} UranusBarycenter;

inline constexpr struct NeptuneBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Neptune Barycenter" }, SolarSystemBarycenter> {
} NeptuneBarycenter;

inline constexpr struct EarthMoonBarycenter final
    : Barycenter<mp_units::basic_fixed_string{ "Earth-Moon Barycenter" }, SolarSystemBarycenter> {
} EarthMoonBarycenter;


} // namespace barycenters

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr RadiusVector<barycenters::EarthMoonBarycenter::parent_icrf>
    get_position_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    return get_position_at_impl<EmbEphemerisTable, barycenters::EarthMoonBarycenter::parent_icrf>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr VelocityVector<barycenters::EarthMoonBarycenter::parent_icrf>
    get_velocity_at<barycenters::EarthMoonBarycenter>(const Date& date)
{
    return get_velocity_at_impl<EmbEphemerisTable, barycenters::EarthMoonBarycenter::parent_icrf>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea