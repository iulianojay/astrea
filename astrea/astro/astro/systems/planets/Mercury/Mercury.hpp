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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
#include <ephemerides/Mercury/MercuryEphemerisTable.hpp>
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

namespace astrea {
namespace astro {

// Forward-declare frame types to avoid circular include with frames.hpp
namespace frames {
namespace solar_system_barycenter {
struct icrf;
}
} // namespace frames

namespace planets {

/**
 * @class Mercury
 * @brief Represents the Mercury celestial body.
 *
 * This class provides properties and methods specific to Mercury, including its physical and orbital parameters.
 */
inline constexpr struct Mercury : CelestialBody<"Mercury", barycenters::SolarSystemBarycenter> {
} Mercury;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Mercury>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::unit_symbols::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(22032.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.330 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2439.7 * km),
             .polarRadius            = Distance(2439.7 * km),
             .crashRadius            = Distance(2464.7 * km),
             .sphereOfInfluence      = Distance(0.011239389492058 * au),
             .j2                     = Unitless(60.0e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.034 * deg),
             .rotationRate           = AngularVelocity(6.138107416879796 * deg / day),
             .siderealPeriod         = Time(87.969 * day),
             .semimajorAxis          = Distance(0.38709927 * au),
             .eccentricity           = Unitless(0.20563593 * one),
             .inclination            = Angle(7.00497902 * deg),
             .rightAscension         = Angle(48.33076593 * deg),
             .longitudeOfPerigee     = Angle(77.45779628 * deg),
             .meanLongitude          = Angle(252.25032350 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00000037 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.00001906 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00594749 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.12534081 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.16047689 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(149472.67411175 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

/**
 * @brief Get the position of the Mercury at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Mercury.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Mercury at the given date.
 */
template <>
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf> get_position_at<planets::Mercury>(const Date& date)
{
    return get_position_at_impl<MercuryEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Mercury at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Mercury.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Mercury at the given date.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at<planets::Mercury>(const Date& date)
{
    return get_velocity_at_impl<MercuryEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

} // namespace astro
} // namespace astrea