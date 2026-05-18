/**
 * @file Deimos.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Deimos class.
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
#include <astro/systems/planets/Mars/Mars.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Deimos
 * @brief Represents the Deimos celestial body.
 *
 * This class provides properties and methods specific to Deimos, including its physical and orbital parameters.
 */
inline constexpr struct Deimos : CelestialBody<"Deimos", Mars> {
} Deimos;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Deimos>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2433282.5 })),
             .mu                     = GravParam(7.112e-4 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(10.6e-9 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(11.1 * km),
             .polarRadius            = Distance(9.1 * km),
             .crashRadius            = Distance(11.15 * km),
             .sphereOfInfluence      = Distance(7.23133636677e-07 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(25.199 * deg),
             .rotationRate           = AngularVelocity(27092.28308927283 * deg / day),
             .siderealPeriod         = Time(0.31891 * day),
             .semimajorAxis          = Distance(9378.0 * km),
             .eccentricity           = Unitless(0.0151 * one),
             .inclination            = Angle(1.08 * deg),
             .rightAscension         = Angle(207.784 * deg),
             .longitudeOfPerigee     = Angle(357.841 * deg),
             .meanLongitude          = Angle(448.9 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(57302029 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(171830131 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(148603627216.0 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea