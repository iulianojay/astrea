#pragma once

#include <astro/systems/CelestialBody.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif

namespace astrea {
namespace astro {
namespace barycenters {

struct SolarSystemBarycenter : Barycenter<mp_units::basic_fixed_string{ "Solar System Barycenter" }> {};

struct MercuryBarycenter : Barycenter<mp_units::basic_fixed_string{ "Mercury Barycenter" }, SolarSystemBarycenter{}> {};
struct VenusBarycenter : Barycenter<mp_units::basic_fixed_string{ "Venus Barycenter" }, SolarSystemBarycenter{}> {};
struct EarthBarycenter : Barycenter<mp_units::basic_fixed_string{ "Earth Barycenter" }, SolarSystemBarycenter{}> {};
struct MarsBarycenter : Barycenter<mp_units::basic_fixed_string{ "Mars Barycenter" }, SolarSystemBarycenter{}> {};
struct JupiterBarycenter : Barycenter<mp_units::basic_fixed_string{ "Jupiter Barycenter" }, SolarSystemBarycenter{}> {};
struct SaturnBarycenter : Barycenter<mp_units::basic_fixed_string{ "Saturn Barycenter" }, SolarSystemBarycenter{}> {};
struct UranusBarycenter : Barycenter<mp_units::basic_fixed_string{ "Uranus Barycenter" }, SolarSystemBarycenter{}> {};
struct NeptuneBarycenter : Barycenter<mp_units::basic_fixed_string{ "Neptune Barycenter" }, SolarSystemBarycenter{}> {};

struct EarthMoonBarycenter : Barycenter<mp_units::basic_fixed_string{ "Earth-Moon Barycenter" }, SolarSystemBarycenter{}> {
    using ParentIcrf = frames::solar_system_barycenter::icrf; //!< The SSB-centric ICRF frame in which EMB position is expressed.
    using ParentJ2000 = frames::solar_system_barycenter::j2000; //!< The SSB-centric J2000 frame.
};

} // namespace barycenters

// Forward-declare the frame types to avoid circular include with frames.hpp
namespace frames {
namespace solar_system_barycenter {
struct icrf;
struct j2000;
} // namespace solar_system_barycenter
namespace earth_barycenter {
struct icrf;
} // namespace earth_barycenter
namespace earth {
struct icrf;
} // namespace earth
} // namespace frames

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf>
    get_position_at<barycenters::EarthMoonBarycenter{}>(const Date& date)
{
    return get_position_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf>
    get_velocity_at<barycenters::EarthMoonBarycenter{}>(const Date& date)
{
    return get_velocity_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea