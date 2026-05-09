/**
 * @file Moon.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Moon class.
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

static const CelestialBodyParameters DEFAULT_MOON_PARAMS{
    .name          = "Moon",
    .parent        = CelestialBodyId::EARTH,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(4902.8 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.073 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1737.5 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1736.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1737.5 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.006602718630998 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(1.543 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(13.176195007686115 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(27.3220 * mp_units::non_si::day),
    .semimajorAxis          = Distance(380318 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.063843 * mp_units::one),
    .inclination            = Angle(5.28619 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(98.13908 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(179.16058 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(135.89122 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(6967741.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(28578547 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(1761137860.75 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Moon
 * @brief Represents the Moon celestial body.
 *
 * This class provides properties and methods specific to the Moon, including its physical and orbital parameters.
 */
class Moon : public CelestialBody {
  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Moon class.
     *
     * Initializes the Moon object with predefined physical and orbital parameters.
     */
    constexpr Moon() :
        CelestialBody(DEFAULT_MOON_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Moon class.
     */
    ~Moon() = default;

    /**
     * @brief Get the unique identifier for the Moon celestial body.
     *
     * @return CelestialBodyId The unique identifier for the Moon.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MOON; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

    /**
     * @brief Get the position of the Moon at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Moon.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Moon at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

    /**
     * @brief Get the velocity of the Moon at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the velocity of the Moon.
     * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Moon at the given date.
     */
    VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const Date& date) const;

#endif // ASTREA_BUILD_EARTH_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea