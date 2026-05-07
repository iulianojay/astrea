/**
 * @file Frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Frame in astrea.
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

#include <mp-units/ext/fixed_string.h>

#include <units/units.hpp>

#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct FrameBase {};


} // namespace detail

template <mp_units::basic_fixed_string _name, CelestialBodyId _origin, FrameAxis _axis, typename _parent = void>
struct Frame : detail::FrameBase {
    static constexpr auto origin = _origin; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis;   //!< The axis type of the frame.
    static constexpr auto name   = _name;   //!< The name of the frame.
    using parent                 = _parent; //!< The parent frame of this frame.
};


} // namespace astro
} // namespace astrea