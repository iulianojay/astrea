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

static CelestialBodyParameters DEFAULT_RHEA_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(120.50 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00181 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(746.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(712.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(761.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.002253931200283 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(41.940 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(4.537995330226328 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(79.33018 * mp_units::non_si::day),
    .semimajorAxis  = Distance(3561.3e3 * mp_units::si::unit_symbols::km),
    .eccentricity   = Unitless(0.0283 * mp_units::one),
    .inclination    = Angle(14.72 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(81.105 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(352.711 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(554.5 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(37688.33 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(11498.3 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(59680892.45 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

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
    return planets::DEFAULT_RHEA_PARAMS;
}

} // namespace astro
} // namespace astrea