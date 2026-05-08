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

/**
 * @brief Empty base class for all frames in astrea. This allows us to use std::derived_from to check if a type is a frame.
 */
struct FrameBase {};

} // namespace detail

/**
 * @brief Base class for all frames in astrea. Frames are defined by their name, origin celestial body, axis type, and parent frame.
 *
 * @tparam _name_ The name of the frame as a compile-time fixed string.
 * @tparam _origin_ The celestial body associated with the frame (e.g., Earth, Mars).
 * @tparam _axis_ The axis type of the frame (e.g., ICRF, J2000, FIXED_ROTATING).
 * @tparam _parent_ The parent frame from which this frame is derived. Defaults to void for root frames.
 */
template <mp_units::basic_fixed_string _name_, CelestialBodyId _origin_, FrameAxis _axis_, typename _parent_ = void>
struct Frame : detail::FrameBase {
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
    static constexpr auto name   = _name_;   //!< The name of the frame.
    using parent                 = _parent_; //!< The parent frame of this frame.
};


} // namespace astro
} // namespace astrea