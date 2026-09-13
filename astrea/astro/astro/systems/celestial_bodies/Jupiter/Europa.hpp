/**
 * @file Europa.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Europa class.
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
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {

namespace moons {

/**
 * @class Europa
 * @brief Represents the Europa celestial body.
 *
 * This class provides properties and methods specific to Europa, including its physical and orbital parameters.
 */
inline constexpr struct Europa final : CelestialBody<"Europa", planets::Jupiter> {
} Europa;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Europa>()
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
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2450464.5 })),
             .mu                     = GravParam(3202.7 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.04800 * (mag_power<10, 24> * kg)),
             .equatorialRadius       = Distance(1560.8 * km),
             .polarRadius            = Distance(1560.8 * km),
             .crashRadius            = Distance(1560.8 * km),
             .sphereOfInfluence      = Distance(9.72669393872e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.146 * deg),
             .rotationRate           = AngularVelocity(101.3747257602471 * deg / day),
             .siderealPeriod         = Time(3.551181 * day),
             .semimajorAxis          = Distance(671.1e3 * km),
             .eccentricity           = Unitless(0.009 * one),
             .inclination            = Angle(0.47 * deg),
             .rightAscension         = Angle(219.106 * deg),
             .longitudeOfPerigee     = Angle(308.076 * deg),
             .meanLongitude          = Angle(479.092 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(4293665.52 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(97263536.4 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(13427026021.5 * deg / jc) };
}

} // namespace astro
} // namespace astrea