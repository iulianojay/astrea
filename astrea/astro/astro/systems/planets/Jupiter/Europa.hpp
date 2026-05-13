/**
 * @file Europa.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Europa class.
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

static CelestialBodyParameters DEFAULT_EUROPA_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(3202.7 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.04800 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(9.72669393872e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.146 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(101.3747257602471 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(3.551181 * mp_units::non_si::day),
    .semimajorAxis  = Distance(671.1e3 * mp_units::si::unit_symbols::km),
    .eccentricity   = Unitless(0.009 * mp_units::one),
    .inclination    = Angle(0.47 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(219.106 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(308.076 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(479.092 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(4293665.52 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(97263536.4 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(13427026021.5 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Europa
 * @brief Represents the Europa celestial body.
 *
 * This class provides properties and methods specific to Europa, including its physical and orbital parameters.
 */
inline constexpr struct Europa : CelestialBody<"Europa", Jupiter, DEFAULT_EUROPA_PARAMS> {
} Europa;

} // namespace planets
} // namespace astro
} // namespace astrea