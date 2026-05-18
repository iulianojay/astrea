/**
 * @file Uranus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Uranus class.
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

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
#include <ephemerides/Uranus/UranusEphemerisTable.hpp>
#endif // ASTREA_BUILD_URANUS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Uranus
 * @brief Represents the Uranus celestial body.
 *
 * This class provides properties and methods specific to Uranus, including its physical and orbital parameters.
 */
inline constexpr struct Uranus : CelestialBody<"Uranus", barycenters::SolarSystemBarycenter> {
} Uranus;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Uranus>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(5793939.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(86.8 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(25559.0 * km),
             .polarRadius            = Distance(24973.0 * km),
             .crashRadius            = Distance(25559.0 * km),
             .sphereOfInfluence      = Distance(5.176385869757780 * au),
             .j2                     = Unitless(3343.43e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(82.23 * deg),
             .rotationRate           = AngularVelocity(-501.1600928074246 * deg / day),
             .siderealPeriod         = Time(30685.4 * day),
             .semimajorAxis          = Distance(19.18916464 * au),
             .eccentricity           = Unitless(0.04725744 * one),
             .inclination            = Angle(0.77263783 * deg),
             .rightAscension         = Angle(74.01692503 * deg),
             .longitudeOfPerigee     = Angle(170.95427630 * deg),
             .meanLongitude          = Angle(313.23810451 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(-0.00196176 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00004397 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00242939 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(0.04240589 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.40805281 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(428.48202785 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

/**
 * @brief Get the position of the Uranus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Uranus.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Uranus at the given date.
 */
template <>
inline constexpr auto get_position_at<planets::Uranus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Uranus, axes::icrf);
    return get_position_at_impl<UranusEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Uranus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Uranus.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Uranus at the given date.
 */
template <>
inline constexpr auto get_velocity_at<planets::Uranus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Uranus, axes::icrf);
    return get_velocity_at_impl<UranusEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

/**
 * @brief Get the coefficients for the linear expansion of Uranus' orbital elements.
 *
 * This function returns a tuple containing the coefficients used in the linear expansion
 * of Uranus' orbital elements, which are essential for calculating its position and motion
 * over time.
 *
 * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
 */
template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Uranus>()
{
    using mp_units::angular::unit_symbols::rad;
    return std::make_tuple(0.00058331 * rad / (JulianCentury * JulianCentury), -0.97731848 * rad, 0.17689245 * rad, 7.67025000 * rad / JulianCentury);
}

} // namespace astro
} // namespace astrea