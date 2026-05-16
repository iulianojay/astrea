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
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

static CelestialBodyParameters DEFAULT_DEIMOS_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(7.112e-4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(10.6e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(11.1 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(9.1 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(11.15 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(7.23133636677e-07 * mp_units::iau::unit_symbols::au),
    .j2                     = Unitless(0.0 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(25.199 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularVelocity(27092.28308927283 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(0.31891 * mp_units::non_si::day),
    .semimajorAxis          = Distance(9378.0 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0151 * mp_units::one),
    .inclination            = Angle(1.08 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(207.784 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(357.841 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(448.9 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(57302029 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(171830131 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(148603627216.0 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

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
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Deimos>()
{
    return planets::DEFAULT_DEIMOS_PARAMS;
}

} // namespace astro
} // namespace astrea