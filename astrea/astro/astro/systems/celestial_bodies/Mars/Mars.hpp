/**
 * @file Mars.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Mars class.
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

#include <map>

#include <astro/astro.fwd.hpp>
#include <astro/astro.macros.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_MARS_EPHEMERIS
#include <astro/ephemerides/Mars/MarsEphemerisTable.hpp>
#endif // ASTREA_BUILD_MARS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Mars
 * @brief Represents the Mars celestial body.
 *
 * This class provides properties and methods specific to Mars, including its physical and orbital parameters.
 */
inline constexpr struct Mars final : CelestialBody<"Mars", barycenters::SolarSystemBarycenter> {
} Mars;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Mars>()
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
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(42828.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.642 * (mag_power<10, 24> * kg)),
             .equatorialRadius       = Distance(3396.2 * km),
             .polarRadius            = Distance(3376.2 * km),
             .crashRadius            = Distance(3496.2 * km),
             .sphereOfInfluence      = Distance(0.057732173855358 * au),
             .j2                     = Unitless(1960.45e-6 * one),
             .j3                     = Unitless(0.000036 * one),
             .axialTilt              = Angle(25.19 * deg),
             .rotationRate           = AngularVelocity(350.8928680212322 * deg / day),
             .siderealPeriod         = Time(686.980 * day),
             .semimajorAxis          = Distance(1.52371034 * au),
             .eccentricity           = Unitless(0.09339410 * one),
             .inclination            = Angle(1.84969142 * deg),
             .rightAscension         = Angle(49.55953891 * deg),
             .longitudeOfPerigee     = Angle(-23.94362959 * deg),
             .meanLongitude          = Angle(-4.55343205 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00001847 * au / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.00007882 * one / jc),
             .inclinationRate        = BodyAngularVelocity(-0.00813131 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(-0.29257343 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.44441088 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(19140.30268499 * deg / jc),
             // https://pds-geosciences.wustl.edu/mro/mro-m-rss-5-sdp-v1/mrors_1xxx/data/shadr/ - normalized?
             .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Mars/jgmro_120f_sha.tab" };
}

/**
 * @brief Calculate the atmospheric density at a given altitude and date.
 *
 * This function uses a simple exponential model to estimate the atmospheric density
 * based on the altitude above the surface of Mars. The model parameters are based on
 * average conditions and do not account for seasonal or diurnal variations.
 *
 * @param date The date for which to calculate the atmospheric density.
 * @param altitude The altitude above the surface of Mars in kilometers.
 * @return Density The estimated atmospheric density in kg/m^3.
 */

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

/**
 * @brief Get the position of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Mars.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Mars at the given date.
 */
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Mars, axes::icrf)>
    get_position_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_position_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Mars.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Mars at the given date.
 */
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Mars, axes::icrf)>
    get_velocity_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_velocity_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

/**
 * @brief Get the acceleration of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the acceleration of the Mars.
 * @return AccelerationVector<frames::solar_system_barycenter::icrf> The acceleration of the Mars at the given date.
 */
template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Mars, axes::icrf)>
    get_acceleration_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_acceleration_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_MARS_EPHEMERIS

} // namespace astro
} // namespace astrea