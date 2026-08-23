/**
 * @file Titania.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Titania class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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
#include <astro/systems/celestial_bodies/Uranus/Uranus.hpp>

namespace astrea {
namespace astro {

namespace moons {

/**
 * @class Titania
 * @brief Represents the Titania celestial body.
 *
 * This class provides properties and methods specific to Titania, including its physical and orbital parameters.
 */
inline constexpr struct Titania final : CelestialBody<"Titania", planets::Uranus> {
} Titania;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Titania>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2444239.5 })),
             .mu                     = GravParam(228.2 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00342 * (mag_power<10, 24> * kg)),
             .equatorialRadius       = Distance(788.9 * km),
             .polarRadius            = Distance(788.9 * km),
             .crashRadius            = Distance(1568.9 * km),
             .sphereOfInfluence      = Distance(7.55070955998e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(41.351424275146869 * deg / day),
             .siderealPeriod         = Time(8.70586 * day),
             .semimajorAxis          = Distance(436.30e3 * km),
             .eccentricity           = Unitless(0.0011 * one),
             .inclination            = Angle(0.08 * deg),
             .rightAscension         = Angle(99.771 * deg),
             .longitudeOfPerigee     = Angle(24.17 * deg),
             .meanLongitude          = Angle(48.785 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(663360.1 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1465712.68 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(5438764533.33 * deg / jc) };
}

} // namespace astro
} // namespace astrea