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

#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
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
    if constexpr (IsDerivedOrigin<Origin_T> && IsRootAxis<Axis_T>) {
        return Frame<origin.parent.name + mp_units::symbol_text{ "_" } + axis.name, origin.parent, axis>{};
    }
    else if constexpr (IsRootOrigin<Origin_T> && IsDerivedAxis<Axis_T>) {
        return Frame<origin.name + mp_units::symbol_text{ "_" } + axis.parent.name, origin, axis.parent>{};
    }
    else if constexpr (IsDerivedOrigin<Origin_T> && IsDerivedAxis<Axis_T>) {
        return Frame<origin.parent.name + mp_units::symbol_text{ "_" } + axis.parent.name, origin.parent, axis.parent>{};
    }
    else {
        static_assert(always_false<Origin_T>, "Frame has no parent.");
    }
}

template <IsOrigin Origin_T, IsAxis Axis_T>
inline consteval auto make_frame(Origin_T origin, Axis_T axis)
{
    return Frame<origin.name + mp_units::symbol_text{ "_" } + axis.name, origin, axis>{};
}

template <IsAxis Axis_T, IsAxis Axis_U>
inline consteval auto find_axis_in_ancestors(Axis_T axis, Axis_U target)
{
    if constexpr (equivalent(axis.parent, target)) { return axis.parent; }
    else if constexpr (IsDerivedAxis<decltype(axis.parent)>) {
        return find_axis_in_ancestors(axis.parent, target);
    }
    else {
        static_assert(always_false<Axis_T>, "Axis ancestory does not contain the target axis.");
    }
}

template <IsAxis Axis_T, IsAxis Axis_U>
inline consteval auto find_common_ancestor(Axis_T axis, Axis_U axis_u)
{
    if constexpr (equivalent(axis, axis_u)) { return axis; }
    else if constexpr (IsDerivedAxis<Axis_T> && IsRootAxis<Axis_U>) {
        return find_axis_in_ancestors(axis, axis_u);
    }
    else if constexpr (IsRootAxis<Axis_T> && IsDerivedAxis<Axis_U>) {
        return find_axis_in_ancestors(axis_u, axis);
    }
    else if constexpr (IsDerivedAxis<Axis_T> && IsDerivedAxis<Axis_U>) {
        // Recursively dig through just one tree until it's no longer derived
        return find_common_ancestor(axis.parent, axis_u);
    }
    else {
        static_assert(always_false<Axis_T>, "No common ancestor found between the two frames.");
    }
}

template <IsAxis auto axis, IsAxis auto axis_u>
concept HasCommonAncestor = requires { find_common_ancestor(axis, axis_u); };

} // namespace astro
} // namespace astrea