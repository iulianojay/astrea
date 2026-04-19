/**
 * @file Iapetus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Iapetus class.
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

static const CelestialBodyParameters DEFAULT_IAPETUS_PARAMS{
    .name          = "Iapetus",
    .parent        = CelestialBodyId::SATURN,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(153.94 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00231 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(765.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(762.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(765.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(3.67746912467e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(26.766 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(79.690094078583286 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(4.517500 * mp_units::non_si::day),
    .semimajorAxis          = Distance(527.04e3 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0010 * mp_units::one),
    .inclination            = Angle(0.35 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(351.042 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(232.661 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(412.44 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(3616878.77 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(10841361.7 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(10489285497.13 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Iapetus
 * @brief Represents the Iapetus celestial body.
 *
 * This class provides properties and methods specific to Iapetus, including its physical and orbital parameters.
 */
class Iapetus : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Iapetus class.
     *
     * Initializes the Iapetus object with predefined physical and orbital parameters.
     */
    constexpr Iapetus() :
        CelestialBody(DEFAULT_IAPETUS_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Iapetus class.
     */
    ~Iapetus() = default;

    /**
     * @brief Get the unique identifier for the Iapetus celestial body.
     *
     * @return CelestialBodyId The unique identifier for Iapetus.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::IAPETUS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea