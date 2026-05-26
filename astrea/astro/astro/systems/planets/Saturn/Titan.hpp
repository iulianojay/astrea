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

namespace astrea {
namespace astro {

namespace moons {

/**
 * @class Titan
 * @brief Represents the Titan celestial body.
 *
 * This class provides properties and methods specific to Titan, including its physical and orbital parameters.
 */
inline constexpr struct Titan final : CelestialBody<"Titan", planets::Saturn> {
} Titan;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Titan>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(J2000),
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

} // namespace astro
} // namespace astrea