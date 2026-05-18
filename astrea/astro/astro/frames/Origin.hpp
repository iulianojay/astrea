/**
 * @file Origin.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Origin in astrea.
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

#include <type_traits>

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct OriginBase {};

} // namespace detail

template <mp_units::symbol_text, auto...>
struct Origin;

template <mp_units::symbol_text _name_>
struct Origin<_name_> : detail::OriginBase {
    static constexpr auto name = _name_; //!< The name of the origin.
};

template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct Origin<_name_, _parent_> : detail::OriginBase {
    static constexpr auto name   = _name_;   //!< The name of the origin.
    static constexpr auto parent = _parent_; //!< The parent origin of this origin, if any.
};

struct DynamicOrigin : Origin<"dynamic"> {};


template <IsFrame Frame_T, IsOrigin Origin_T>
inline consteval auto has_origin(Frame_T, Origin_T)
{
    return std::is_same_v<decltype(Frame_T::origin), Origin_T>;
}

} // namespace astro
} // namespace astrea