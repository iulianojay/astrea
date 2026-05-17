/**
 * @file Mars.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Mars class.
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

#include <map>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_MARS_EPHEMERIS
#include <ephemerides/Mars/MarsEphemerisTable.hpp>
#endif // ASTREA_BUILD_MARS_EPHEMERIS

namespace astrea {
namespace astro {

// Forward-declare frame types to avoid circular include with frames.hpp
namespace frames {
namespace solar_system_barycenter {
struct icrf;
}
} // namespace frames

namespace planets {

/**
 * @class Mars
 * @brief Represents the Mars celestial body.
 *
 * This class provides properties and methods specific to Mars, including its physical and orbital parameters.
 */
inline constexpr struct Mars : CelestialBody<"Mars", barycenters::SolarSystemBarycenter> {
} Mars;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Mars>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::unit_symbols::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(42828.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.642 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(3396.2 * km),
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
             .semimajorAxisRate      = InterplanetaryVelocity(0.00001847 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.00007882 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00813131 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.29257343 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.44441088 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(19140.30268499 * deg / JulianCentury) };
}

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, Density> martianAtmosphere = { // km, kg/m^3
    { 2.0 * mp_units::si::unit_symbols::km,
      1.19e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 4.0 * mp_units::si::unit_symbols::km,
      1.10e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 6.0 * mp_units::si::unit_symbols::km,
      1.02e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 8.0 * mp_units::si::unit_symbols::km,
      9.39e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 10.0 * mp_units::si::unit_symbols::km,
      8.64e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 12.0 * mp_units::si::unit_symbols::km,
      7.93e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 14.0 * mp_units::si::unit_symbols::km,
      7.25e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 16.0 * mp_units::si::unit_symbols::km,
      6.61e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 18.0 * mp_units::si::unit_symbols::km,
      6.00e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 20.0 * mp_units::si::unit_symbols::km,
      5.43e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 22.0 * mp_units::si::unit_symbols::km,
      4.89e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 24.0 * mp_units::si::unit_symbols::km,
      3.91e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 26.0 * mp_units::si::unit_symbols::km,
      3.32e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 28.0 * mp_units::si::unit_symbols::km,
      2.82e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 30.0 * mp_units::si::unit_symbols::km,
      2.40e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 32.0 * mp_units::si::unit_symbols::km,
      2.04e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 34.0 * mp_units::si::unit_symbols::km,
      1.73e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 36.0 * mp_units::si::unit_symbols::km,
      1.47e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 38.0 * mp_units::si::unit_symbols::km,
      1.25e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 40.0 * mp_units::si::unit_symbols::km,
      1.06e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 45.0 * mp_units::si::unit_symbols::km,
      7.03e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 50.0 * mp_units::si::unit_symbols::km,
      4.67e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 55.0 * mp_units::si::unit_symbols::km,
      3.10e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 60.0 * mp_units::si::unit_symbols::km,
      2.06e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 65.0 * mp_units::si::unit_symbols::km,
      1.36e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 70.0 * mp_units::si::unit_symbols::km,
      9.11e-4 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 75.0 * mp_units::si::unit_symbols::km,
      6.05e-4 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 80.0 * mp_units::si::unit_symbols::km,
      4.02e-4 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) }
};

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
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf> get_position_at<planets::Mars>(const Date& date)
{
    return get_position_at_impl<MarsEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Mars.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Mars at the given date.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at<planets::Mars>(const Date& date)
{
    return get_velocity_at_impl<MarsEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_MARS_EPHEMERIS

} // namespace astro
} // namespace astrea