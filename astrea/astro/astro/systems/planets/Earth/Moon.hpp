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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/planets/Earth/Earth.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/MoonEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

/**
 * @class Moon
 * @brief Represents the Moon celestial body.
 *
 * This class provides properties and methods specific to the Moon, including its physical and orbital parameters.
 */
inline constexpr struct Moon : CelestialBody<"Moon", Earth> {
} Moon;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Moon>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(4902.8 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.073 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1737.5 * km),
             .polarRadius            = Distance(1736.0 * km),
             .crashRadius            = Distance(1737.5 * km),
             .sphereOfInfluence      = Distance(0.006602718630998 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(1.543 * deg),
             .rotationRate           = AngularVelocity(13.176195007686115 * deg / day),
             .siderealPeriod         = Time(27.3220 * day),
             .semimajorAxis          = Distance(380318 * km),
             .eccentricity           = Unitless(0.063843 * one),
             .inclination            = Angle(5.28619 * deg),
             .rightAscension         = Angle(98.13908 * deg),
             .longitudeOfPerigee     = Angle(179.16058 * deg),
             .meanLongitude          = Angle(135.89122 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(6967741.9 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(28578547 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(1761137860.75 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Moon at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Moon.
 * @return RadiusVector<frames::earth::icrf> The position of the Moon at the given date.
 */
template <>
inline constexpr auto get_position_at<planets::Moon>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Moon, axes::icrf);
    return get_position_at_impl<planets::MoonEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Moon at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Moon.
 * @return VelocityVector<frames::earth::icrf> The velocity of the Moon at the given date.
 */
template <>
inline constexpr auto get_velocity_at<planets::Moon>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Moon, axes::icrf);
    return get_velocity_at_impl<planets::MoonEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea