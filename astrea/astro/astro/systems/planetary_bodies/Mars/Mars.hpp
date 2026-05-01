/**
 * @file Mars.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Mars class.
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

static const CelestialBodyParameters DEFAULT_MARS_PARAMS{
    .name          = "Mars",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(42828.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.642 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(3396.2 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(3376.2 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(3496.2 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(1960.45e-6 * mp_units::one),
    .j3                = Unitless(0.000036 * mp_units::one),
    .axialTilt         = Angle(25.19 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(686.980 * mp_units::non_si::day),
    .semimajorAxis  = Distance(1.52371034 * mp_units::iau::unit_symbols::au),
    .eccentricity   = Unitless(0.09339410 * mp_units::one),
    .inclination    = Angle(1.84969142 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(49.55953891 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(-23.94362959 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(-4.55343205 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00001847 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.00007882 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.00813131 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(-0.29257343 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.44441088 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(19140.30268499 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Mars
 * @brief Represents the Mars celestial body.
 *
 * This class provides properties and methods specific to Mars, including its physical and orbital parameters.
 */
class Mars : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Mars class.
     *
     * Initializes the Mars object with predefined physical and orbital parameters.
     */
    constexpr Mars() :
        CelestialBody(DEFAULT_MARS_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Mars class.
     */
    ~Mars() = default;

    /**
     * @brief Calculate the atmospheric density at a given altitude and date.
     *
     * This function uses a simple exponential model to estimate the atmospheric density
     * based on the altitude above the surface of Mars. The model parameters are based on
     * average conditions and do not account for seasonal or diurnal variations.
     *
     * @param date The date for which to calculate the atmospheric density.
     * @param altitude The altitude above the surface of Mars in kilometers.
     * @return Density The estimated atmospheric density in kg/m^3.
     */
    Density find_atmospheric_density(const State& state) const override;

    /**
     * @brief Get the unique identifier for the Mars celestial body.
     *
     * @return CelestialBodyId The unique identifier for Mars.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MARS; };

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

    /**
     * @brief Get the position of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Mars.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Mars at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

    /**
     * @brief Get the velocity of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the velocity of the Mars.
     * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Mars at the given date.
     */
    VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const Date& date) const;

#endif // ASTREA_BUILD_MARS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea