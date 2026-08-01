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

#ifdef ASTREA_BUILD_SUN_EPHEMERIS
#include <ephemerides/Sun/SunEphemerisTable.hpp>
#endif // ASTREA_BUILD_SUN_EPHEMERIS

namespace astrea {
namespace astro {

namespace star {

/**
 * @class Sun
 * @brief Represents the Sun celestial body.
 *
 * This class provides properties and methods specific to the Sun, including its physical and orbital parameters.
 */
inline constexpr struct Sun final : CelestialBody<"Sun", barycenters::SolarSystemBarycenter> {
} Sun;

} // namespace star

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<star::Sun>()
{
    using namespace mp_units;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::STAR,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2451544.5 })),
             .mu                     = GravParam(1.32712e11 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(1988500.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(695700.0 * km),
             .polarRadius            = Distance(695700.0 * km),
             .crashRadius            = Distance(795700.0 * km),
             .sphereOfInfluence      = Distance(1.0e18 * km),
             .j2                     = Unitless(0.2e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(0.0 * deg / day),
             .siderealPeriod         = Time(0.0 * day),
             .semimajorAxis          = Distance(0.0 * km),
             .eccentricity           = Unitless(0.0 * one),
             .inclination            = Angle(0.0 * deg),
             .rightAscension         = Angle(0.0 * deg),
             .longitudeOfPerigee     = Angle(0.0 * deg),
             .meanLongitude          = Angle(0.0 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(0.0 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

/**
 * @brief Get the position of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Sun.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Sun at the given date.
 */
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(star::Sun, axes::icrf)> get_position_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_position_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Sun.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Sun at the given date.
 */
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(star::Sun, axes::icrf)> get_velocity_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_velocity_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

/**
 * @brief Get the acceleration of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the acceleration of the Sun.
 * @return AccelerationVector<frames::solar_system_barycenter::icrf> The acceleration of the Sun at the given date.
 */
template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(star::Sun, axes::icrf)>
    get_acceleration_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_acceleration_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_SUN_EPHEMERIS

} // namespace astro
} // namespace astrea