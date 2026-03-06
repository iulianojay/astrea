/**
 * @file Titan.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Titan class.
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

static const CelestialBodyParameters DEFAULT_TITAN_PARAMS{
    .name          = "Titan",
    .parent        = CelestialBodyId::SATURN,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(8978.1 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.13455 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.004333361603448 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(27.359 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(22.577014429408919 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(15.94542 * mp_units::non_si::day),
    .semimajorAxis     = Distance(1221.83e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.0292 * mp_units::one),
    .inclination       = Angle(0.33 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(28.060 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(208.592 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(371.902 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(183934.15 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(551990.5 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(2969198512.13 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Titan
 * @brief Represents the Titan celestial body.
 *
 * This class provides properties and methods specific to Titan, including its physical and orbital parameters.
 */
class Titan : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Titan class.
     *
     * Initializes the Titan object with predefined physical and orbital parameters.
     */
    constexpr Titan() :
        CelestialBody(DEFAULT_TITAN_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Titan class.
     */
    ~Titan() = default;

    /**
     * @brief Find the atmospheric density at a given altitude and date.
     *
     * This function overrides the base class method to provide atmospheric density specific to Titan.
     *
     * @param date The date for which to find the atmospheric density.
     * @param altitude The altitude above the surface of Titan.
     * @return Density The atmospheric density at the specified altitude and date.
     */
    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    /**
     * @brief Get the unique identifier for the Titan celestial body.
     *
     * @return CelestialBodyId The unique identifier for Titan.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TITAN; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea