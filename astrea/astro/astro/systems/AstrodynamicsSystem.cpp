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

#include <astro/frames/frames.hpp>
#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

RadiusVector<frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const
{
    const auto pos1 = get_body(id1)->get_position_at(date);
    const auto pos2 = get_body(id2)->get_position_at(date);
    return pos1 - pos2;
}

} // namespace astro
} // namespace astrea