/**
 * @file Rhea.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Rhea class.
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
#include <astro/systems/planets/Saturn/Saturn.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Rhea
 * @brief Represents the Rhea celestial body.
 *
 * This class provides properties and methods specific to Rhea, including its physical and orbital parameters.
 */
inline constexpr struct Rhea : CelestialBody<"Rhea", Saturn> {
} Rhea;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Rhea>()
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
             .mu                     = GravParam(120.50 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00181 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(746.0 * km),
             .polarRadius            = Distance(712.0 * km),
             .crashRadius            = Distance(761.0 * km),
             .sphereOfInfluence      = Distance(0.002253931200283 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(41.940 * deg),
             .rotationRate           = AngularVelocity(4.537995330226328 * deg / day),
             .siderealPeriod         = Time(79.33018 * day),
             .semimajorAxis          = Distance(3561.3e3 * km),
             .eccentricity           = Unitless(0.0283 * one),
             .inclination            = Angle(14.72 * deg),
             .rightAscension         = Angle(81.105 * deg),
             .longitudeOfPerigee     = Angle(352.711 * deg),
             .meanLongitude          = Angle(554.5 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(37688.33 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(11498.3 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(59680892.45 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea