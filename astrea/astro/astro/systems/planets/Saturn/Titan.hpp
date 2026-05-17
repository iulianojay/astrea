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
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::unit_symbols::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(8978.1 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.13455 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2575.0 * km),
             .polarRadius            = Distance(2575.0 * km),
             .crashRadius            = Distance(2575.0 * km),
             .sphereOfInfluence      = Distance(0.004333361603448 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(27.359 * deg),
             .rotationRate           = AngularVelocity(22.577014429408919 * deg / day),
             .siderealPeriod         = Time(15.94542 * day),
             .semimajorAxis          = Distance(1221.83e3 * km),
             .eccentricity           = Unitless(0.0292 * one),
             .inclination            = Angle(0.33 * deg),
             .rightAscension         = Angle(28.060 * deg),
             .longitudeOfPerigee     = Angle(208.592 * deg),
             .meanLongitude          = Angle(371.902 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(183934.15 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(551990.5 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(2969198512.13 * deg / JulianCentury) };
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
Density find_atmospheric_density<planets::Titan>(const Date& date, const Distance& altitude) const
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::cm;
    using mp_units::si::unit_symbols::g;
    using mp_units::si::unit_symbols::km;

    /**
     * @brief Type alias for Density on Titan.
     */
    using TitanDensity = quantity<g / pow<3>(cm)>;

    // Altitude Conditions(TABLE 7-4, Vallado)
    static const std::map<Altitude, TitanDensity> titanicAtmosphere = {
        // km, g/cm^3
        { 780.0 * km, 1.00e-12 * g / (pow<3>(cm)) },  { 790.0 * km, 8.45e-12 * g / (pow<3>(cm)) },
        { 800.0 * km, 7.16e-12 * g / (pow<3>(cm)) },  { 810.0 * km, 6.08e-12 * g / (pow<3>(cm)) },
        { 820.0 * km, 5.17e-12 * g / (pow<3>(cm)) },  { 830.0 * km, 4.41e-12 * g / (pow<3>(cm)) },
        { 840.0 * km, 3.77e-12 * g / (pow<3>(cm)) },  { 850.0 * km, 3.23e-12 * g / (pow<3>(cm)) },
        { 860.0 * km, 2.78e-12 * g / (pow<3>(cm)) },  { 870.0 * km, 2.39e-12 * g / (pow<3>(cm)) },
        { 880.0 * km, 2.06e-12 * g / (pow<3>(cm)) },  { 890.0 * km, 1.78e-12 * g / (pow<3>(cm)) },
        { 900.0 * km, 1.54e-12 * g / (pow<3>(cm)) },  { 910.0 * km, 1.34e-12 * g / (pow<3>(cm)) },
        { 920.0 * km, 1.16e-12 * g / (pow<3>(cm)) },  { 930.0 * km, 1.01e-12 * g / (pow<3>(cm)) },
        { 940.0 * km, 8.80e-13 * g / (pow<3>(cm)) },  { 950.0 * km, 7.67e-13 * g / (pow<3>(cm)) },
        { 960.0 * km, 6.69e-13 * g / (pow<3>(cm)) },  { 970.0 * km, 5.84e-13 * g / (pow<3>(cm)) },
        { 980.0 * km, 5.10e-13 * g / (pow<3>(cm)) },  { 990.0 * km, 4.46e-13 * g / (pow<3>(cm)) },
        { 1000.0 * km, 3.90e-13 * g / (pow<3>(cm)) }, { 1010.0 * km, 1.81e-13 * g / (pow<3>(cm)) },
        { 1020.0 * km, 2.99e-13 * g / (pow<3>(cm)) }, { 1030.0 * km, 2.62e-13 * g / (pow<3>(cm)) },
        { 1040.0 * km, 2.30e-13 * g / (pow<3>(cm)) }, { 1050.0 * km, 2.02e-13 * g / (pow<3>(cm)) },
        { 1060.0 * km, 1.78e-13 * g / (pow<3>(cm)) }, { 1070.0 * km, 1.56e-13 * g / (pow<3>(cm)) },
        { 1080.0 * km, 1.38e-13 * g / (pow<3>(cm)) }, { 1090.0 * km, 1.21e-13 * g / (pow<3>(cm)) },
        { 1100.0 * km, 1.07e-13 * g / (pow<3>(cm)) }, { 1110.0 * km, 9.43e-14 * g / (pow<3>(cm)) },
        { 1120.0 * km, 8.33e-14 * g / (pow<3>(cm)) }, { 1130.0 * km, 7.36e-14 * g / (pow<3>(cm)) },
        { 1140.0 * km, 6.51e-14 * g / (pow<3>(cm)) }, { 1150.0 * km, 5.76e-14 * g / (pow<3>(cm)) },
        { 1160.0 * km, 5.10e-14 * g / (pow<3>(cm)) }, { 1170.0 * km, 4.52e-14 * g / (pow<3>(cm)) },
        { 1180.0 * km, 4.01e-14 * g / (pow<3>(cm)) }, { 1190.0 * km, 3.56e-14 * g / (pow<3>(cm)) },
        { 1200.0 * km, 3.16e-14 * g / (pow<3>(cm)) }, { 1210.0 * km, 2.81e-14 * g / (pow<3>(cm)) },
        { 1220.0 * km, 2.50e-14 * g / (pow<3>(cm)) }, { 1230.0 * km, 2.22e-14 * g / (pow<3>(cm)) },
        { 1240.0 * km, 1.98e-14 * g / (pow<3>(cm)) }, { 1250.0 * km, 1.77e-14 * g / (pow<3>(cm)) },
        { 1260.0 * km, 1.58e-14 * g / (pow<3>(cm)) }, { 1270.0 * km, 1.41e-14 * g / (pow<3>(cm)) },
        { 1280.0 * km, 1.26e-14 * g / (pow<3>(cm)) }, { 1290.0 * km, 1.12e-14 * g / (pow<3>(cm)) },
        { 1300.0 * km, 1.00e-14 * g / (pow<3>(cm)) }
    };

    const auto iter = titanicAtmosphere.upper_bound(altitude);
    return (iter != titanicAtmosphere.end()) ? iter->second : Density::zero();
}

} // namespace astro
} // namespace astrea