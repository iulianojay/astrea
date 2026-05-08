/**
 * @file SystemHierarchy.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the SystemHierarchy class, which manages celestial bodies and their interactions.
 * @date 2026-05-02
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

namespace astrea {
namespace astro {

struct no_node {};

template <class... ChildTrees>
struct SystemTree {
    using tuple_t = std::tuple<ChildTrees...>;
    tuple_t children;

    template <int N>
    static constexpr bool has_child()
    {
        if constexpr (N >= sizeof...(ChildTrees)) { return false; }
        else {
            return !std::is_same_v<std::tuple_element_t<N, tuple_t>, no_node>;
        }
    }

    template <int N>
    static constexpr auto child()
    {
        static_assert(N < sizeof...(ChildTrees), "Child index out of bounds.");
        if constexpr (N >= sizeof...(ChildTrees)) { return no_node{}; }
        else {
            return std::tuple_element_t<N, tuple_t>{};
        }
    }

    static constexpr std::size_t n_children() { return sizeof...(ChildTrees); }

    static constexpr bool has_parent() { return !std::is_same_v<std::tuple_element_t<0, tuple_t>, no_node>; }

    static constexpr auto parent()
    {
        if constexpr (sizeof...(ChildTrees) == 0) { return no_node{}; }
        else {
            return std::tuple_element_t<0, tuple_t>{};
        }
    }
};


} // namespace astro
} // namespace astrea