/**
 * @file Triton.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Triton class.
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

static const CelestialBodyParameters DEFAULT_TRITON_PARAMS{
    .name          = "Triton",
    .parent        = CelestialBodyId::NEPTUNE,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(1427.6 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.0214 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.001198560847624 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(28.33 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(61.257264516014864 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(5.87685 * mp_units::non_si::day),
    .semimajorAxis     = Distance(354.76e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.000016 * mp_units::one),
    .inclination       = Angle(157.345 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(177.608 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(243.75 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(596.007 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(188523.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(523952.8 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(8055241569.86 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Triton
 * @brief Represents the Triton celestial body.
 *
 * This class provides properties and methods specific to Triton, including its physical and orbital parameters.
 */
class Triton : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Triton class.
     *
     * Initializes the Triton object with predefined physical and orbital parameters.
     */
    constexpr Triton() :
        CelestialBody(DEFAULT_TRITON_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Triton class.
     */
    ~Triton() = default;

    /**
     * @brief Get the unique identifier for the Triton celestial body.
     *
     * @return CelestialBodyId The unique identifier for Triton.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TRITON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea