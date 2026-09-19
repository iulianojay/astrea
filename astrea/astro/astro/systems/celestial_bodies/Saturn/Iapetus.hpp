/**
 * @file Iapetus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Iapetus class.
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
#include <astro/systems/celestial_bodies/Saturn/Saturn.hpp>

namespace astrea {
namespace astro {

namespace moons {

/**
 * @class Iapetus
 * @brief Represents the Iapetus celestial body.
 *
 * This class provides properties and methods specific to Iapetus, including its physical and orbital parameters.
 */
inline constexpr struct Iapetus final : CelestialBody<"Iapetus", planets::Saturn> {
} Iapetus;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Iapetus>()
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
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(153.94 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00231 * (mag_power<10, 24> * kg)),
             .equatorialRadius       = Distance(765.0 * km),
             .polarRadius            = Distance(762.0 * km),
             .crashRadius            = Distance(765.0 * km),
             .sphereOfInfluence      = Distance(3.67746912467e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(26.766 * deg),
             .rotationRate           = AngularVelocity(79.690094078583286 * deg / day),
             .siderealPeriod         = Time(4.517500 * day),
             .semimajorAxis          = Distance(527.04e3 * km),
             .eccentricity           = Unitless(0.0010 * one),
             .inclination            = Angle(0.35 * deg),
             .rightAscension         = Angle(351.042 * deg),
             .longitudeOfPerigee     = Angle(232.661 * deg),
             .meanLongitude          = Angle(412.44 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(3616878.77 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(10841361.7 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(10489285497.13 * deg / jc) };
}

} // namespace astro
} // namespace astrea