/**
 * @file Uranus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Uranus class.
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

static const CelestialBodyParameters DEFAULT_URANUS_PARAMS{
    .name          = "Uranus",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(5793939.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(86.8 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(25559.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(24973.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(25559.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(5.176385869757780 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(3343.43e-6 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(82.23 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(-501.1600928074246 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(30685.4 * mp_units::non_si::day),
    .semimajorAxis          = Distance(19.18916464 * mp_units::iau::unit_symbols::au),
    .eccentricity           = Unitless(0.04725744 * mp_units::one),
    .inclination            = Angle(0.77263783 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(74.01692503 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(170.95427630 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(313.23810451 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(-0.00196176 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004397 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.00242939 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(0.04240589 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.40805281 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(428.48202785 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Uranus
 * @brief Represents the Uranus celestial body.
 *
 * This class provides properties and methods specific to Uranus, including its physical and orbital parameters.
 */
class Uranus : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Uranus class.
     *
     * Initializes the Uranus object with predefined physical and orbital parameters.
     */
    constexpr Uranus() :
        CelestialBody(DEFAULT_URANUS_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Uranus class.
     */
    ~Uranus() = default;

    /**
     * @brief Get the unique identifier for the Uranus celestial body.
     *
     * @return CelestialBodyId The unique identifier for Uranus.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::URANUS; };

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

    /**
     * @brief Get the position of the Uranus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Uranus.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Uranus at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

  private:
    /**
     * @brief Get the coefficients for the linear expansion of the Uranus' orientation angles.
     *
     * This function provides the coefficients used in the linear expansion to calculate
     * the orientation angles of Uranus over time.
     *
     * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00058331 * rad / (JulianCentury * JulianCentury), -0.97731848 * rad, 0.17689245 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea