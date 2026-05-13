/**
 * @file barycenters.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the barycenters.
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

#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace barycenters {

struct SolarSystemBarycenter : Barycenter<"Solar System Barycenter"> {};

struct EarthMoonBarycenter : Barycenter<"Earth-Moon Barycenter", SolarSystemBarycenter> {};

} // namespace barycenters


#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Earth-Moon Barycenter.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Earth-Moon Barycenter at the given date.
 */
template <>
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf> get_position_at<EarthMoonBarycenter>(const Date& date)
{
    return get_position_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Earth-Moon Barycenter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Earth-Moon Barycenter.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Earth-Moon Barycenter at the given date.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at<EarthMoonBarycenter>(const Date& date)
{
    return get_velocity_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea