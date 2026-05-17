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

namespace astrea {
namespace astro {
namespace planets {

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
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date("1950-01-01 00:00:00"),
             .mu                     = GravParam(9.85e-5 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(2.4e-9 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(6.2 * km),
             .polarRadius            = Distance(5.1 * km),
             .crashRadius            = Distance(6.25 * km),
             .sphereOfInfluence      = Distance(9.98573371442e-07 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(1128.844 * deg / day),
             .siderealPeriod         = Time(1.26244 * day),
             .semimajorAxis          = Distance(23459.0 * km),
             .eccentricity           = Unitless(0.0005 * one),
             .inclination            = Angle(1.79 * deg),
             .rightAscension         = Angle(24.525 * deg),
             .longitudeOfPerigee     = Angle(285.254 * deg),
             .meanLongitude          = Angle(610.583 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(2376381 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(7111440.9 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(37503046910.7 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea