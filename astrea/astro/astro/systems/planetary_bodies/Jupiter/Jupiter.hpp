/**
 * @file Jupiter.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Jupiter class.
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

static const CelestialBodyParameters DEFAULT_JUPITER_PARAMS{
    .name          = "Jupiter",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(126686535.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(1898.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(71492.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(66854.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(71492.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(14736e-6 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.13 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(4332.589 * mp_units::non_si::day),
    .semimajorAxis  = Distance(5.20288700 * mp_units::iau::unit_symbols::au),
    .eccentricity   = Unitless(0.04838624 * mp_units::one),
    .inclination    = Angle(1.30439695 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(100.47390909 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(14.72847983 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(34.39644051 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(-0.00011607 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00013253 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.00183714 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(0.20469106 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.21252668 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(3034.74612775 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Jupiter
 * @brief Represents the Jupiter celestial body.
 *
 * This class provides properties and methods specific to Jupiter, including its physical and orbital parameters.
 */
class Jupiter : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Jupiter class.
     *
     * Initializes the Jupiter object with predefined physical and orbital parameters.
     */
    constexpr Jupiter() :
        CelestialBody(DEFAULT_JUPITER_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Jupiter class.
     */
    ~Jupiter() = default;

    /**
     * @brief Get the unique identifier for the Jupiter celestial body.
     *
     * @return CelestialBodyId The unique identifier for Jupiter.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::JUPITER; };

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

    /**
     * @brief Get the position of the Jupiter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Jupiter.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Jupiter at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

  private:
    /**
     * @brief Get the linear expansion coefficients for Jupiter's orbital elements.
     *
     * This function returns a tuple containing the coefficients for the linear expansion of Jupiter's
     * orbital elements, which are used to compute the position and velocity of Jupiter over time.
     *
     * @return CoefficientPack A tuple containing the linear expansion coefficients.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00012452 * rad / (JulianCentury * JulianCentury), 0.06064060 * rad, -0.35635438 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea