/**
 * @file Titania.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Titania class.
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

static const CelestialBodyParameters DEFAULT_TITANIA_PARAMS{
    .name          = "Titania",
    .parent        = CelestialBodyId::URANUS,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1980-01-01 00:00:00"),
    .mu = GravParam(228.2 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00342 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(788.9 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(788.9 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1568.9 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(7.55070955998e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(41.351424275146869 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(8.70586 * mp_units::non_si::day),
    .semimajorAxis     = Distance(436.30e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.0011 * mp_units::one),
    .inclination       = Angle(0.08 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(99.771 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(24.17 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(48.785 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(663360.1 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(1465712.68 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(5438764533.33 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Titania
 * @brief Represents the Titania celestial body.
 *
 * This class provides properties and methods specific to Titania, including its physical and orbital parameters.
 */
class Titania : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Titania class.
     *
     * Initializes the Titania object with predefined physical and orbital parameters.
     */
    constexpr Titania() :
        CelestialBody(DEFAULT_TITANIA_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Titania class.
     */
    ~Titania() = default;

    /**
     * @brief Get the unique identifier for the Titania celestial body.
     *
     * @return CelestialBodyId The unique identifier for Titania.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TITANIA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea