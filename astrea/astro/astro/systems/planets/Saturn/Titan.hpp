/**
 * @file Titan.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Titan class.
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
#include <astro/systems/planets/Saturn/Saturn.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

static CelestialBodyParameters DEFAULT_TITAN_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(8978.1 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(0.13455 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(0.004333361603448 * mp_units::iau::unit_symbols::au),
    .j2                     = Unitless(0.0 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(27.359 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularVelocity(22.577014429408919 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(15.94542 * mp_units::non_si::day),
    .semimajorAxis          = Distance(1221.83e3 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0292 * mp_units::one),
    .inclination            = Angle(0.33 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(28.060 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(208.592 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(371.902 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(183934.15 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(551990.5 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(2969198512.13 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @brief Type alias for Density on Titan.
 */
using TitanDensity = mp_units::quantity<mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm))>;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, TitanDensity> titanicAtmosphere = { // km, g/cm^3
    { 780.0 * mp_units::si::unit_symbols::km,
      1.00e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 790.0 * mp_units::si::unit_symbols::km,
      8.45e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 800.0 * mp_units::si::unit_symbols::km,
      7.16e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 810.0 * mp_units::si::unit_symbols::km,
      6.08e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 820.0 * mp_units::si::unit_symbols::km,
      5.17e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 830.0 * mp_units::si::unit_symbols::km,
      4.41e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 840.0 * mp_units::si::unit_symbols::km,
      3.77e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 850.0 * mp_units::si::unit_symbols::km,
      3.23e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 860.0 * mp_units::si::unit_symbols::km,
      2.78e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 870.0 * mp_units::si::unit_symbols::km,
      2.39e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 880.0 * mp_units::si::unit_symbols::km,
      2.06e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 890.0 * mp_units::si::unit_symbols::km,
      1.78e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 900.0 * mp_units::si::unit_symbols::km,
      1.54e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 910.0 * mp_units::si::unit_symbols::km,
      1.34e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 920.0 * mp_units::si::unit_symbols::km,
      1.16e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 930.0 * mp_units::si::unit_symbols::km,
      1.01e-12 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 940.0 * mp_units::si::unit_symbols::km,
      8.80e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 950.0 * mp_units::si::unit_symbols::km,
      7.67e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 960.0 * mp_units::si::unit_symbols::km,
      6.69e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 970.0 * mp_units::si::unit_symbols::km,
      5.84e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 980.0 * mp_units::si::unit_symbols::km,
      5.10e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 990.0 * mp_units::si::unit_symbols::km,
      4.46e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1000.0 * mp_units::si::unit_symbols::km,
      3.90e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1010.0 * mp_units::si::unit_symbols::km,
      1.81e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1020.0 * mp_units::si::unit_symbols::km,
      2.99e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1030.0 * mp_units::si::unit_symbols::km,
      2.62e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1040.0 * mp_units::si::unit_symbols::km,
      2.30e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1050.0 * mp_units::si::unit_symbols::km,
      2.02e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1060.0 * mp_units::si::unit_symbols::km,
      1.78e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1070.0 * mp_units::si::unit_symbols::km,
      1.56e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1080.0 * mp_units::si::unit_symbols::km,
      1.38e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1090.0 * mp_units::si::unit_symbols::km,
      1.21e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1100.0 * mp_units::si::unit_symbols::km,
      1.07e-13 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1110.0 * mp_units::si::unit_symbols::km,
      9.43e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1120.0 * mp_units::si::unit_symbols::km,
      8.33e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1130.0 * mp_units::si::unit_symbols::km,
      7.36e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1140.0 * mp_units::si::unit_symbols::km,
      6.51e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1150.0 * mp_units::si::unit_symbols::km,
      5.76e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1160.0 * mp_units::si::unit_symbols::km,
      5.10e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1170.0 * mp_units::si::unit_symbols::km,
      4.52e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1180.0 * mp_units::si::unit_symbols::km,
      4.01e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1190.0 * mp_units::si::unit_symbols::km,
      3.56e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1200.0 * mp_units::si::unit_symbols::km,
      3.16e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1210.0 * mp_units::si::unit_symbols::km,
      2.81e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1220.0 * mp_units::si::unit_symbols::km,
      2.50e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1230.0 * mp_units::si::unit_symbols::km,
      2.22e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1240.0 * mp_units::si::unit_symbols::km,
      1.98e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1250.0 * mp_units::si::unit_symbols::km,
      1.77e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1260.0 * mp_units::si::unit_symbols::km,
      1.58e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1270.0 * mp_units::si::unit_symbols::km,
      1.41e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1280.0 * mp_units::si::unit_symbols::km,
      1.26e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1290.0 * mp_units::si::unit_symbols::km,
      1.12e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) },
    { 1300.0 * mp_units::si::unit_symbols::km,
      1.00e-14 * mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm)) }
};

/**
 * @class Titan
 * @brief Represents the Titan celestial body.
 *
 * This class provides properties and methods specific to Titan, including its physical and orbital parameters.
 */
inline constexpr struct Titan : CelestialBody<"Titan", Saturn> {
} Titan;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Titan>()
{
    return planets::DEFAULT_TITAN_PARAMS;
}

/**
 * @brief Find the atmospheric density at a given altitude and date.
 *
 * This function overrides the base class method to provide atmospheric density specific to Titan.
 *
 * @param date The date for which to find the atmospheric density.
 * @param altitude The altitude above the surface of Titan.
 * @return Density The atmospheric density at the specified altitude and date.
 */

} // namespace astro
} // namespace astrea