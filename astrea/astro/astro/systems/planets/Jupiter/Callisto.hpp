/**
 * @file Callisto.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Callisto class.
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
#include <astro/systems/planets/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Callisto
 * @brief Represents the Callisto celestial body.
 *
 * This class provides properties and methods specific to Callisto, including its physical and orbital parameters.
 */
inline constexpr struct Callisto : CelestialBody<"Callisto", Jupiter> {
} Callisto;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Callisto>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2450464.5 })),
             .mu                     = GravParam(7179.3 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.10759 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2410.3 * km),
             .polarRadius            = Distance(2410.3 * km),
             .crashRadius            = Distance(2410.3 * km),
             .sphereOfInfluence      = Distance(0.003768525014695 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.486 * deg),
             .rotationRate           = AngularVelocity(21.571072760007375 * deg / day),
             .siderealPeriod         = Time(16.68901 * day),
             .semimajorAxis          = Distance(1882.7e3 * km),
             .eccentricity           = Unitless(0.007 * one),
             .inclination            = Angle(0.19 * deg),
             .rightAscension         = Angle(298.848 * deg),
             .longitudeOfPerigee     = Angle(351.491 * deg),
             .meanLongitude          = Angle(532.899 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(382503.98 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1012394.6 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(2837392757.1 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea