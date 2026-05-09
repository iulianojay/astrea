/**
 * @file Neptune.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Neptune class.
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

static const CelestialBodyParameters DEFAULT_NEPTUNE_PARAMS{
    .name          = "Neptune",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(6836529.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(102.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(24764.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(24341.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(24764.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(8.651147189326089 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(3411e-6 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(28.32 * mp_units::angular::unit_symbols::deg),
    .rotationRate   = AngularVelocity(536.3128491620112 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod = Time(60189 * mp_units::non_si::day),
    .semimajorAxis  = Distance(30.06992276 * mp_units::iau::unit_symbols::au),
    .eccentricity   = Unitless(0.00859048 * mp_units::one),
    .inclination    = Angle(1.77004347 * mp_units::angular::unit_symbols::deg),
    .rightAscension = Angle(131.78422574 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(44.96476227 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(-55.12002969 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00026291 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.00005105 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.00035372 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(-0.00508664 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(-0.32241464 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(218.45945325 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Neptune
 * @brief Represents the Neptune celestial body.
 *
 * This class provides properties and methods specific to Neptune, including its physical and orbital parameters.
 */
class Neptune : public CelestialBody {

  public:
    using CelestialBody::CelestialBody;

    /**
     * @brief Default constructor for the Neptune class.
     *
     * Initializes the Neptune object with predefined physical and orbital parameters.
     */
    constexpr Neptune() :
        CelestialBody(DEFAULT_NEPTUNE_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Neptune class.
     */
    ~Neptune() = default;

    /**
     * @brief Get the unique identifier for the Neptune celestial body.
     *
     * @return CelestialBodyId The unique identifier for Neptune.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::NEPTUNE; };

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

    /**
     * @brief Get the position of the Neptune at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Neptune.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Neptune at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

    /**
     * @brief Get the velocity of the Neptune at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the velocity of the Neptune.
     * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Neptune at the given date.
     */
    VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const Date& date) const;

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

  private:
    /**
     * @brief Get the coefficients for the linear expansion of Neptune's orbital elements.
     *
     * This function returns a tuple containing the coefficients for the linear expansion of Neptune's
     * orbital elements, which are used to compute the position and velocity of Neptune over time.
     *
     * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00041348 * rad / (JulianCentury * JulianCentury), 0.68346318 * rad, -0.10162547 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea