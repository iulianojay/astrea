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

#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

RadiusVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const
{
    // If one is the parent of the other, easy
    const auto parent1 = get_body(id1)->get_parent();
    const auto parent2 = get_body(id2)->get_parent();

    if (parent1 == id2) { return get_body(id1)->get_position_at(date); }
    if (parent2 == id1) { return -get_body(id2)->get_position_at(date); }

    // Find the position using the root but it's fine to represent in ssb since it's just a relative position vector
    const CelestialBodyId root = find_common_root({ id1, id2 });

    const RadiusVector<frames::solar_system_barycenter::icrf> pos1 = get_position_relative_to_root(date, id1, root);
    const RadiusVector<frames::solar_system_barycenter::icrf> pos2 = get_position_relative_to_root(date, id2, root);

    return pos1 - pos2;
}

RadiusVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_position_relative_to_root(const Date& date, const CelestialBodyId id, const CelestialBodyId root) const
{
    auto object = id;
    auto parent = get_body(object)->get_parent();

    RadiusVector<frames::solar_system_barycenter::icrf> pos = get_body(object)->get_position_at(date);
    while (parent != root) {
        object = parent;
        parent = get_body(parent)->get_parent();
        pos += get_body(object)->get_position_at(date);
    }
    return pos;
}

} // namespace astro
} // namespace astrea