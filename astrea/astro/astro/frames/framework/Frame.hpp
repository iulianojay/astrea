/**
 * @file Frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Frame in astrea.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <astro/frames/framework/Axis.hpp>
#include <astro/frames/framework/Origin.hpp>
#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

/**
 * @brief Empty base class for all frames in astrea. This allows us to use std::derived_from to check if a type is a frame.
 */
struct FrameBase {
    template <IsFrame Lhs, IsFrame Rhs>
    [[nodiscard]] friend consteval bool operator==(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
};

} // namespace detail

template <mp_units::symbol_text, auto...>
struct Frame;

// /**
//  * @brief Frame with origin and axis only (no name, no parent).
//  */
// template <IsOrigin auto _origin_, IsAxis auto _axis_>
// struct Frame<_origin_, _axis_> : detail::FrameBase {
//     static constexpr auto origin = _origin_; //!< The central body associated with the frame.
//     static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
// };

/**
 * @brief Frame with name, origin, and axis (no parent).
 */
template <mp_units::symbol_text _name_, IsOrigin auto _origin_, IsAxis auto _axis_>
struct Frame<_name_, _origin_, _axis_> : detail::FrameBase {
    static constexpr auto name   = _name_;   //!< The name of the frame.
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
};

// /**
//  * @brief Frame with origin, axis, and parent (no name).
//  */
// template <IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
// struct Frame<_origin_, _axis_, _parent_> : detail::FrameBase {
//     static constexpr auto origin = _origin_; //!< The central body associated with the frame.
//     static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
//     static constexpr auto parent = _parent_; //!< The parent frame of this frame.
// };

/**
 * @brief Frame with name, origin, axis, and parent.
 */
template <mp_units::symbol_text _name_, IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
struct Frame<_name_, _origin_, _axis_, _parent_> : detail::FrameBase {
    static constexpr auto name   = _name_;   //!< The name of the frame.
    static constexpr auto origin = _origin_; //!< The central body associated with the frame.
    static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
    static constexpr auto parent = _parent_; //!< The parent frame of this frame.
};


template <IsFrame Lhs, IsFrame Rhs>
[[nodiscard]] consteval bool equivalent(Lhs t, Rhs u)
{
    return equivalent(t.origin, u.origin) && equivalent(t.axis, u.axis) && has_same_parent(t, u);
}

} // namespace astro
} // namespace astrea