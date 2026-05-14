/**
 * @file Sun.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Sun class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_SUN_EPHEMERIS
#include <ephemerides/Sun/SunEphemerisTable.hpp>
#endif // ASTREA_BUILD_SUN_EPHEMERIS

namespace astrea {
namespace astro {

    // Forward-declare frame types to avoid circular include with frames.hpp
    namespace frames { namespace solar_system_barycenter { struct icrf; } }

namespace planets {

static CelestialBodyParameters DEFAULT_SUN_PARAMS{
    .type          = CelestialBodyType::STAR,
    .referenceDate = Date("2000-01-01 00:00:00"),
    .mu = GravParam(1.32712e11 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(1988500.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(695700.0 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(695700.0 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(795700.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(1.0e18 * mp_units::si::unit_symbols::km),
    .j2                     = Unitless(0.2e-6 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(0.0 * mp_units::non_si::day),
    .semimajorAxis          = Distance(0.0 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0 * mp_units::one),
    .inclination            = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Sun
 * @brief Represents the Sun celestial body.
 *
 * This class provides properties and methods specific to the Sun, including its physical and orbital parameters.
 */
inline constexpr struct Sun : CelestialBody<"Sun", barycenters::SolarSystemBarycenter{}> {
} Sun;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Sun>()
{
    return planets::DEFAULT_SUN_PARAMS;
}

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

/**
 * @brief Get the position of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Sun.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Sun at the given date.
 */
template <>
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf> get_position_at<planets::Sun>(const Date& date)
{
    return get_position_at_impl<SunEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Sun.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Sun at the given date.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at<planets::Sun>(const Date& date)
{
    return get_velocity_at_impl<SunEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_SUN_EPHEMERIS

} // namespace astro
} // namespace astrea