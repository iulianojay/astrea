/**
 * @file Io.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Io class.
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

static const CelestialBodyParameters DEFAULT_IO_PARAMS{
    .name          = "Io",
    .parent        = CelestialBodyId::JUPITER,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(5959.9 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.08932 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1821.5 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1821.5 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1841.5 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(7.83731997166e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.13 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(203.4889307674133 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(1.769138 * mp_units::non_si::day),
    .semimajorAxis  = Distance(421.8e3 * mp_units::si::unit_symbols::km),
    .eccentricity   = Unitless(0.004 * mp_units::one),
    .inclination    = Angle(0.04 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(43.977 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(128.106 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(470.127 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(17466307.28 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(97220153.4 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(26853983280.3 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Io
 * @brief Represents the Io celestial body.
 *
 * This class provides properties and methods specific to Io, including its physical and orbital parameters.
 */
class Io : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Io class.
     *
     * Initializes the Io object with predefined physical and orbital parameters.
     */
    constexpr Io() :
        CelestialBody(DEFAULT_IO_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Io class.
     */
    ~Io() = default;

    /**
     * @brief Get the unique identifier for the Io celestial body.
     *
     * @return CelestialBodyId The unique identifier for Io.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::IO; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea