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

#include <astro/systems/planetary_bodies/Earth/Moon.hpp>

#include <map>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Earth/MoonEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> Moon::get_position_at(const Date& date) const
{
    const auto positionMoonFromEarth = get_position_at_impl<MoonEphemerisTable, frames::earth::icrf>(date);
    return positionMoonFromEarth.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea