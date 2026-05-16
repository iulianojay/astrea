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

#include <astro/frames/Axis.hpp>
#include <astro/frames/Origin.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

/**
 * @brief Empty base class for all frames in astrea. This allows us to use std::derived_from to check if a type is a frame.
 */
struct FrameBase {};

} // namespace detail

template <auto...>
struct Frame;

/**
 * @brief Frame with origin and axis only (no name, no parent).
 */
template <IsOrigin auto _origin_, IsAxis auto _axis_>
struct Frame<_origin_, _axis_> : detail::FrameBase {
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
};

/**
 * @brief Frame with name, origin, and axis (no parent).
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _origin_, IsAxis auto _axis_>
struct Frame<_name_, _origin_, _axis_> : detail::FrameBase {
    static constexpr auto name   = _name_;   //!< The name of the frame.
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
};

/**
 * @brief Frame with origin, axis, and parent (no name).
 */
template <IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
struct Frame<_origin_, _axis_, _parent_> : detail::FrameBase {
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
    static constexpr auto parent = _parent_; //!< The parent frame of this frame.
};

/**
 * @brief Frame with name, origin, axis, and parent.
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
struct Frame<_name_, _origin_, _axis_, _parent_> : detail::FrameBase {
    static constexpr auto name   = _name_;   //!< The name of the frame.
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
    static constexpr auto parent = _parent_; //!< The parent frame of this frame.
};


template <auto...>
struct FixedRotatingFrame;

/**
 * @brief Fixed rotating frame without a parent frame (root body-fixed frame).
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _origin_, IsAxis auto _axis_, Coordinate _rotation_coordinate_>
struct FixedRotatingFrame<_name_, _origin_, _axis_, _rotation_coordinate_>
    : Frame<_name_, _origin_, FixedRotatingAxis<_axis_, _rotation_coordinate_>{}> {};

/**
 * @brief Fixed rotating frame with a parent frame.
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _origin_, IsAxis auto _axis_, Coordinate _rotation_coordinate_, IsFrame auto _parent_>
struct FixedRotatingFrame<_name_, _origin_, _axis_, _rotation_coordinate_, _parent_>
    : Frame<_name_, _origin_, FixedRotatingAxis<_axis_, _rotation_coordinate_>{}, _parent_> {};


template <mp_units::basic_fixed_string _name_>
struct DynamicOrigin : Origin<_name_> {};

template <mp_units::basic_fixed_string _name_>
struct DynamicAxis : Axis<_name_> {};

} // namespace astro
} // namespace astrea