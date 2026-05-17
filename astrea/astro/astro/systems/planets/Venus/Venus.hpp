/**
 * @file Venus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Venus class.
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

#include <map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
#include <ephemerides/Venus/VenusEphemerisTable.hpp>
#endif // ASTREA_BUILD_VENUS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Venus
 * @brief Represents the Venus celestial body.
 *
 * This class provides properties and methods specific to Venus, including its physical and orbital parameters.
 */
inline constexpr struct Venus : CelestialBody<"Venus", barycenters::SolarSystemBarycenter> {
} Venus;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Venus>()
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
             .mu                     = GravParam(324860.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(4.87 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(6051.8 * km),
             .polarRadius            = Distance(6051.8 * km),
             .crashRadius            = Distance(6301.8 * km),
             .sphereOfInfluence      = Distance(0.061640255733634 * au),
             .j2                     = Unitless(4.458e-6 * one),
             .j3                     = Unitless(-0.0000025323e-6 * one),
             .axialTilt              = Angle(2.64 * deg),
             .rotationRate           = AngularVelocity(-1.481329081370229 * deg / day),
             .siderealPeriod         = Time(224.701 * day),
             .semimajorAxis          = Distance(0.72333566 * au),
             .eccentricity           = Unitless(0.00677672 * one),
             .inclination            = Angle(3.39467605 * deg),
             .rightAscension         = Angle(76.67984255 * deg),
             .longitudeOfPerigee     = Angle(131.60246718 * deg),
             .meanLongitude          = Angle(181.97909950 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00000390 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00004107 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00078890 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.27769418 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.00268329 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(58517.81538729 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

/**
 * @brief Get the position of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Venus.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Venus at the given date.
 */
template <>
inline constexpr auto get_position_at<planets::Venus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Venus, axes::icrf);
    return get_position_at_impl<VenusEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Venus.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Venus at the given date.
 */
template <>
inline constexpr auto get_velocity_at<planets::Venus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Venus, axes::icrf);
    return get_velocity_at_impl<VenusEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_VENUS_EPHEMERIS

} // namespace astro
} // namespace astrea