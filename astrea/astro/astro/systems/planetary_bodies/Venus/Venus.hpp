/**
 * @file Venus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Venus class.
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

static const CelestialBodyParameters DEFAULT_VENUS_PARAMS{
    .name          = "Venus",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(324860.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(4.87 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(6301.8 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.061640255733634 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(4.458e-6 * mp_units::one),
    .j3                = Unitless(-0.0000025323e-6 * mp_units::one),
    .axialTilt         = Angle(2.64 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(-1.481329081370229 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(224.701 * mp_units::non_si::day),
    .semimajorAxis          = Distance(0.72333566 * mp_units::iau::unit_symbols::au),
    .eccentricity           = Unitless(0.00677672 * mp_units::one),
    .inclination            = Angle(3.39467605 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(76.67984255 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(131.60246718 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(181.97909950 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00000390 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004107 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.00078890 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(-0.27769418 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.00268329 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(58517.81538729 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Venus
 * @brief Represents the Venus celestial body.
 *
 * This class provides properties and methods specific to Venus, including its physical and orbital parameters.
 */
class Venus : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Venus class.
     *
     * Initializes the Venus object with predefined physical and orbital parameters.
     */
    constexpr Venus() :
        CelestialBody(DEFAULT_VENUS_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Venus class.
     */
    ~Venus() = default;

    /**
     * @brief Find the atmospheric density at a given date and altitude.
     *
     * @param date The date for which to find the atmospheric density.
     * @param altitude The altitude at which to find the atmospheric density.
     * @return Density The atmospheric density at the given date and altitude.
     */
    Density find_atmospheric_density(const State& state) const override;

    /**
     * @brief Get the unique identifier for the Venus celestial body.
     *
     * @return CelestialBodyId The unique identifier for Venus.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::VENUS; };

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

    /**
     * @brief Get the position of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Venus.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Venus at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

    /**
     * @brief Get the velocity of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the velocity of the Venus.
     * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Venus at the given date.
     */
    VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const

#endif // ASTREA_BUILD_VENUS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea