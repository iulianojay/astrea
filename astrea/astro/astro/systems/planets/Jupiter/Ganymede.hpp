/**
 * @file Ganymede.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Ganymede class.
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
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Ganymede
 * @brief Represents the Ganymede celestial body.
 *
 * This class provides properties and methods specific to Ganymede, including its physical and orbital parameters.
 */
inline constexpr struct Ganymede : CelestialBody<"Ganymede", Jupiter> {
} Ganymede;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Ganymede>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date("1997-01-16 00:00:00"),
             .mu                     = GravParam(9887.8 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.14819 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2631.2 * km),
             .polarRadius            = Distance(2631.2 * km),
             .crashRadius            = Distance(2631.2 * km),
             .sphereOfInfluence      = Distance(0.002435315183093 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.198 * deg),
             .rotationRate           = AngularVelocity(50.317608940768210 * deg / day),
             .siderealPeriod         = Time(7.154553 * day),
             .semimajorAxis          = Distance(1070.4e3 * km),
             .eccentricity           = Unitless(0.001 * one),
             .inclination            = Angle(0.18 * deg),
             .rightAscension         = Angle(63.552 * deg),
             .longitudeOfPerigee     = Angle(255.969 * deg),
             .meanLongitude          = Angle(573.509 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(976977.7 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(3016348.9 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(6619278519.62 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea