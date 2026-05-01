/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/systems/planetary_bodies/Uranus/Uranus.hpp>

#include <map>

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Uranus/UranusEphemerisTable.hpp>
#endif // ASTREA_BUILD_URANUS_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionUbFromSsb = get_position_at_impl<UranusEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionUbFromSsb; // TODO: Add correction for Uranus' position from Uranus barycenter
}

VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at(const Date& date) const
{
    const auto velocityUbFromSsb = get_velocity_at_impl<UranusEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return velocityUbFromSsb; // TODO: Add correction for Uranus' velocity from Uranus barycenter
}

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea