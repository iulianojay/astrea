/**
 * @file Saturn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Saturn class.
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

static const CelestialBodyParameters DEFAULT_SATURN_PARAMS{
    .name          = "Saturn",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(37931187.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(568.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(60268.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(54364.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(60268.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(5.453426873248700 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(16298e-6 * mp_units::one),
    .j3                 = Unitless(26.73 * mp_units::one),
    .axialTilt          = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(810.8108108108107 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(10759.22 * mp_units::non_si::day),
    .semimajorAxis      = Distance(9.53667594 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.05386179 * mp_units::one),
    .inclination        = Angle(2.48599187 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(113.66242448 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(92.59887831 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(49.95424423 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(-0.00125060 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(-0.00050991 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.00193609 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.28867794 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(-0.41897216 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(1222.49362201 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Saturn
 * @brief Represents the Saturn celestial body.
 *
 * This class provides properties and methods specific to Saturn, including its physical and orbital parameters.
 */
class Saturn : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Saturn class.
     *
     * Initializes the Saturn object with predefined physical and orbital parameters.
     */
    constexpr Saturn() :
        CelestialBody(DEFAULT_SATURN_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Saturn class.
     */
    ~Saturn() = default;

    /**
     * @brief Get the unique identifier for the Saturn celestial body.
     *
     * @return CelestialBodyId The unique identifier for Saturn.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::SATURN; };

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

    /**
     * @brief Get the position of the Saturn at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Saturn.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Saturn at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

  private:
    /**
     * @brief Get the coefficients for the linear expansion of Saturn's orbital elements.
     *
     * This function returns a tuple containing the coefficients used in the linear expansion
     * of Saturn's orbital elements, which are essential for calculating its position and motion
     * over time.
     *
     * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00025899 * rad / (JulianCentury * JulianCentury), -0.13434469 * rad, 0.87320147 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea