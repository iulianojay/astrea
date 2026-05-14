/**
 * @file Phobos.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Phobos class.
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

static CelestialBodyParameters DEFAULT_PHOBOS_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(9.85e-5 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(2.4e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(6.2 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(5.1 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(6.25 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(9.98573371442e-07 * mp_units::iau::unit_symbols::au),
    .j2                     = Unitless(0.0 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularVelocity(1128.844 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(1.26244 * mp_units::non_si::day),
    .semimajorAxis          = Distance(23459.0 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0005 * mp_units::one),
    .inclination            = Angle(1.79 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(24.525 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(285.254 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(610.583 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(2376381 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(7111440.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(37503046910.7 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Phobos
 * @brief Represents the Phobos celestial body.
 *
 * This class provides properties and methods specific to Phobos, including its physical and orbital parameters.
 */
inline constexpr struct Phobos : CelestialBody<"Phobos", Mars> {
} Phobos;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Phobos>()
{
    return planets::DEFAULT_PHOBOS_PARAMS;
}

} // namespace astro
} // namespace astrea