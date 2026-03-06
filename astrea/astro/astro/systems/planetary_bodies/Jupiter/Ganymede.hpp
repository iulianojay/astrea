/**
 * @file Ganymede.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Ganymede class.
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

static const CelestialBodyParameters DEFAULT_GANYMEDE_PARAMS{
    .name          = "Ganymede",
    .parent        = CelestialBodyId::JUPITER,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(9887.8 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.14819 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(2631.2 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(2631.2 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(2631.2 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.002435315183093 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.198 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(50.317608940768210 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(7.154553 * mp_units::non_si::day),
    .semimajorAxis     = Distance(1070.4e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.001 * mp_units::one),
    .inclination       = Angle(0.18 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(63.552 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(255.969 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(573.509 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(976977.7 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(3016348.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(6619278519.62 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Ganymede
 * @brief Represents the Ganymede celestial body.
 *
 * This class provides properties and methods specific to Ganymede, including its physical and orbital parameters.
 */
class Ganymede : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Ganymede class.
     *
     * Initializes the Ganymede object with predefined physical and orbital parameters.
     */
    constexpr Ganymede() :
        CelestialBody(DEFAULT_GANYMEDE_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Ganymede class.
     */
    ~Ganymede() = default;

    /**
     * @brief Get the unique identifier for the Ganymede celestial body.
     *
     * @return CelestialBodyId The unique identifier for Ganymede.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::GANYMEDE; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea