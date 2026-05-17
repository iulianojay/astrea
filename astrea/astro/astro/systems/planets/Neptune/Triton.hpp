/**
 * @file Triton.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Triton class.
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/planets/Neptune/Neptune.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Triton
 * @brief Represents the Triton celestial body.
 *
 * This class provides properties and methods specific to Triton, including its physical and orbital parameters.
 */
inline constexpr struct Triton : CelestialBody<"Triton", Neptune> {
} Triton;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Triton>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(1427.6 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.0214 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1353.4 * km),
             .polarRadius            = Distance(1353.4 * km),
             .crashRadius            = Distance(1353.4 * km),
             .sphereOfInfluence      = Distance(0.001198560847624 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(28.33 * deg),
             .rotationRate           = AngularVelocity(61.257264516014864 * deg / day),
             .siderealPeriod         = Time(5.87685 * day),
             .semimajorAxis          = Distance(354.76e3 * km),
             .eccentricity           = Unitless(0.000016 * one),
             .inclination            = Angle(157.345 * deg),
             .rightAscension         = Angle(177.608 * deg),
             .longitudeOfPerigee     = Angle(243.75 * deg),
             .meanLongitude          = Angle(596.007 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(188523.9 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(523952.8 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(8055241569.86 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea