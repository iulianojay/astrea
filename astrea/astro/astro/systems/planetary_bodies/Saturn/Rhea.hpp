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

static const CelestialBodyParameters DEFAULT_RHEA_PARAMS{
    .name          = "Rhea",
    .parent        = CelestialBodyId::SATURN,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(120.50 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.00181 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(746.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(712.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(761.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.002253931200283 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(0.0 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(41.940 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(4.537995330226328 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(79.33018 * mp_units::non_si::day),
    .semimajorAxis      = Distance(3561.3e3 * mp_units::si::unit_symbols::km),
    .eccentricity       = Unitless(0.0283 * mp_units::one),
    .inclination        = Angle(14.72 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(81.105 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(352.711 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(554.5 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(37688.33 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(11498.3 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(59680892.45 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Rhea
 * @brief Represents the Rhea celestial body.
 *
 * This class provides properties and methods specific to Rhea, including its physical and orbital parameters.
 */
class Rhea : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
    using CelestialBody::CelestialBody;

     * @brief Default constructor for the Rhea class.
     *
     * Initializes the Rhea object with predefined physical and orbital parameters.
     */
    constexpr Rhea() :
        CelestialBody(DEFAULT_RHEA_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Rhea class.
     */
    ~Rhea() = default;

    /**
     * @brief Get the unique identifier for the Rhea celestial body.
     *
     * @return CelestialBodyId The unique identifier for Rhea.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::RHEA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea