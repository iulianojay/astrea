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
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

static CelestialBodyParameters DEFAULT_CALLISTO_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(7179.3 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.10759 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.003768525014695 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.486 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(21.571072760007375 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(16.68901 * mp_units::non_si::day),
    .semimajorAxis          = Distance(1882.7e3 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.007 * mp_units::one),
    .inclination            = Angle(0.19 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(298.848 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(351.491 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(532.899 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(382503.98 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(1012394.6 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(2837392757.1 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Callisto
 * @brief Represents the Callisto celestial body.
 *
 * This class provides properties and methods specific to Callisto, including its physical and orbital parameters.
 */
inline constexpr struct Callisto : CelestialBody<"Callisto", Jupiter, DEFAULT_CALLISTO_PARAMS> {
} Callisto;

} // namespace planets
} // namespace astro
} // namespace astrea