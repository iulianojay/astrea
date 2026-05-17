/**
 * @file Saturn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Saturn class.
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

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS
#include <ephemerides/Saturn/SaturnEphemerisTable.hpp>
#endif // ASTREA_BUILD_SATURN_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Saturn
 * @brief Represents the Saturn celestial body.
 *
 * This class provides properties and methods specific to Saturn, including its physical and orbital parameters.
 */
inline constexpr struct Saturn : CelestialBody<"Saturn", barycenters::SolarSystemBarycenter> {
} Saturn;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Saturn>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(37931187.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(568.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(60268.0 * km),
             .polarRadius            = Distance(54364.0 * km),
             .crashRadius            = Distance(60268.0 * km),
             .sphereOfInfluence      = Distance(5.453426873248700 * au),
             .j2                     = Unitless(16298e-6 * one),
             .j3                     = Unitless(26.73 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(810.8108108108107 * deg / day),
             .siderealPeriod         = Time(10759.22 * day),
             .semimajorAxis          = Distance(9.53667594 * au),
             .eccentricity           = Unitless(0.05386179 * one),
             .inclination            = Angle(2.48599187 * deg),
             .rightAscension         = Angle(113.66242448 * deg),
             .longitudeOfPerigee     = Angle(92.59887831 * deg),
             .meanLongitude          = Angle(49.95424423 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(-0.00125060 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00050991 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.00193609 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.28867794 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(-0.41897216 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(1222.49362201 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

/**
 * @brief Get the position of the Saturn at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Saturn.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Saturn at the given date.
 */
template <>
inline constexpr auto get_position_at<planets::Saturn>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Saturn, axes::icrf);
    return get_position_at_impl<SaturnEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Saturn at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Saturn.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Saturn at the given date.
 */
template <>
inline constexpr auto get_velocity_at<planets::Saturn>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Saturn, axes::icrf);
    return get_velocity_at_impl<SaturnEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

/**
 * @brief Get the coefficients for the linear expansion of Saturn's orbital elements.
 *
 * This function returns a tuple containing the coefficients used in the linear expansion
 * of Saturn's orbital elements, which are essential for calculating its position and motion
 * over time.
 *
 * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
 */
template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Saturn>()
{
    using mp_units::angular::unit_symbols::rad;
    return std::make_tuple(0.00025899 * rad / (JulianCentury * JulianCentury), -0.13434469 * rad, 0.87320147 * rad, 38.35125000 * rad / JulianCentury);
}

} // namespace astro
} // namespace astrea