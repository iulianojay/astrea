/**
 * @file Mercury.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Mercury class.
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

static const CelestialBodyParameters DEFAULT_MERCURY_PARAMS{
    .name          = "Mercury",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(22032.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.330 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(2439.7 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(2439.7 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(2464.7 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.011239389492058 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(60.0e-6 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(0.034 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(6.138107416879796 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(87.969 * mp_units::non_si::day),
    .semimajorAxis      = Distance(0.38709927 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.20563593 * mp_units::one),
    .inclination        = Angle(7.00497902 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(48.33076593 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(77.45779628 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(252.25032350 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.00000037 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.00001906 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(-0.00594749 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.12534081 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.16047689 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(149472.67411175 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Mercury
 * @brief Represents the Mercury celestial body.
 *
 * This class provides properties and methods specific to Mercury, including its physical and orbital parameters.
 */
class Mercury : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Mercury class.
     *
     * Initializes the Mercury object with predefined physical and orbital parameters.
     */
    constexpr Mercury() :
        CelestialBody(DEFAULT_MERCURY_PARAMS)
    {
    }

    /**
     * @brief Default destructor for the Mercury class.
     */
    ~Mercury() = default;

    /**
     * @brief Get the unique identifier for the Mercury celestial body.
     *
     * @return CelestialBodyId The unique identifier for Mercury.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MERCURY; };

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

    /**
     * @brief Get the position of the Mercury at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Mercury.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Mercury at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea