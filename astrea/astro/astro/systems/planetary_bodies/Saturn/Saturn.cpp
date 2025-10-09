/*
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/systems/planetary_bodies/Saturn/Saturn.hpp>

#include <map>

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Saturn/SaturnEphemerisTable.hpp>
#endif // ASTREA_BUILD_SATURN_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionSbFromSsb = get_position_at_impl<SaturnEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionSbFromSsb; // TODO: Add correction for Saturn's position from Saturn barycenter
}

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea