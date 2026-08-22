/**
 * @file Neptune.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Neptune class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
#include <astro/ephemerides/Neptune/NeptuneEphemerisTable.hpp>
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Neptune
 * @brief Represents the Neptune celestial body.
 *
 * This class provides properties and methods specific to Neptune, including its physical and orbital parameters.
 */
inline constexpr struct Neptune final : CelestialBody<"Neptune", barycenters::SolarSystemBarycenter> {
} Neptune;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Neptune>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2433282.5 })),
             .mu                     = GravParam(6836529.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(102.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(24764.0 * km),
             .polarRadius            = Distance(24341.0 * km),
             .crashRadius            = Distance(24764.0 * km),
             .sphereOfInfluence      = Distance(8.651147189326089 * au),
             .j2                     = Unitless(3411e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(28.32 * deg),
             .rotationRate           = AngularVelocity(536.3128491620112 * deg / day),
             .siderealPeriod         = Time(60189 * day),
             .semimajorAxis          = Distance(30.06992276 * au),
             .eccentricity           = Unitless(0.00859048 * one),
             .inclination            = Angle(1.77004347 * deg),
             .rightAscension         = Angle(131.78422574 * deg),
             .longitudeOfPerigee     = Angle(44.96476227 * deg),
             .meanLongitude          = Angle(-55.12002969 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00026291 * au / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.00005105 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.00035372 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(-0.00508664 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(-0.32241464 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(218.45945325 * deg / jc) };
}

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

/**
 * @brief Get the position of the Neptune at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Neptune.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Neptune at the given date.
 */
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Neptune, axes::icrf)>
    get_position_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_position_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Neptune at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Neptune.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Neptune at the given date.
 */
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Neptune, axes::icrf)>
    get_velocity_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_velocity_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

/**
 * @brief Get the acceleration of the Neptune at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the acceleration of the Neptune.
 * @return AccelerationVector<frames::solar_system_barycenter::icrf> The acceleration of the Neptune at the given date.
 */
template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Neptune, axes::icrf)>
    get_acceleration_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_acceleration_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

/**
 * @brief Get the coefficients for the linear expansion of Neptune's orbital elements.
 *
 * This function returns a tuple containing the coefficients for the linear expansion of Neptune's
 * orbital elements, which are used to compute the position and velocity of Neptune over time.
 *
 * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
 */
template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Neptune>()
{
    using astrea::units::unit_symbols::jc;
    using mp_units::si::unit_symbols::rad;
    return std::make_tuple(-0.00041348 * rad / (jc * jc), 0.68346318 * rad, -0.10162547 * rad, 7.67025000 * rad / jc);
}

} // namespace astro
} // namespace astrea