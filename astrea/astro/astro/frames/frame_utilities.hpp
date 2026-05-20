/**
 * @file frame_utilities.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for frame utilities in astrea.
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

#include <astro/frames/Frame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {


template <IsOrigin Origin_T>
inline consteval auto get_parent_name(Origin_T origin)
{
    return decltype(Origin_T::parent)::name;
}

template <IsOrigin Origin_T>
inline consteval auto get_parent(Origin_T origin)
{
    return Origin_T::parent;
}

template <IsOrigin Origin_T, IsAxis Axis_T>
inline consteval auto get_parent_frame(Origin_T origin, Axis_T axis)
{
    return Frame<get_parent_name(origin) + mp_units::symbol_text{ "_" } + Axis_T::name, get_parent(origin), axis>{};
}

template <IsOrigin Origin_T, IsAxis Axis_T>
inline consteval auto get_frame(Origin_T origin, Axis_T axis)
{
    return Frame<Origin_T::name + mp_units::symbol_text{ "_" } + Axis_T::name, origin, axis>{};
}

} // namespace astro
} // namespace astrea