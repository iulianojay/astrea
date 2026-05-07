/**
 * @file frame_concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for frame concepts and other compile-time utilities.
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

#include <concepts>

#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {


namespace detail {

struct FrameBase;

template <typename T>
concept SymbolicConstant = (!std::is_const_v<T>) && (!std::is_reference_v<T>) && std::is_empty_v<T> &&
                           std::is_trivially_default_constructible_v<T> && std::is_trivially_copy_constructible_v<T> &&
                           std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>;

} // namespace detail

template <typename T>
concept IsFrame = std::derived_from<T, detail::FrameBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a frame is inertial.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is inertial (ICRF or J2000), false otherwise.
 */
template <typename Frame_T>
concept IsInertialFrame = (Frame_T::axis == FrameAxis::ICRF || Frame_T::axis == FrameAxis::J2000);

/**
 * @brief Concept to determine if a frame is body-fixed.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is body-fixed, false otherwise.
 */
template <typename Frame_T>
concept IsFixedRotatingFrame = (Frame_T::axis == FrameAxis::FIXED_ROTATING);

/**
 * @brief Concept to determine if a frame is static (inertial or body-fixed).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is static, false otherwise.
 */
template <typename Frame_T>
concept IsStaticFrame =
    (Frame_T::axis == FrameAxis::ICRF || Frame_T::axis == FrameAxis::J2000 || Frame_T::axis == FrameAxis::FIXED_ROTATING);

/**
 * @brief Concept to determine if a frame is dynamic (LVLH, RIC, VNB).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is dynamic, false otherwise.
 */
template <typename Frame_T>
concept IsDynamicFrame =
    (Frame_T::axis == FrameAxis::LVLH || Frame_T::axis == FrameAxis::RIC || Frame_T::axis == FrameAxis::VNB);

/**
 * @brief Concept to determine if two frames share the same origin.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same origin, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = (Frame_T::origin == Frame_U::origin);

/**
 * @brief Concept to determine if two frames share the same axis.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same axis, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameAxis = (Frame_T::axis == Frame_U::axis);

template <typename Frame_T>
concept IsDerivedFrame = IsFrame<Frame_T> && !std::is_same_v<typename Frame_T::parent, void>;

template <typename Frame_T>
concept HasSpatialOffset = requires { Frame_T::offset; };

template <typename Frame_T>
concept HasAngularOffset = requires { Frame_T::misalignment; };

template <typename Frame_T>
concept IsFixedOffsetFrame = IsDerivedFrame<Frame_T> && (HasSpatialOffset<Frame_T> || HasAngularOffset<Frame_T>);

/**
 * @brief Concept to determine if two frames are the same (same origin and same axis).
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames are the same, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept IsSameFrame = HasSameOrigin<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U> &&
                      std::is_same_v<typename Frame_T::parent, typename Frame_U::parent>;

} // namespace astro
} // namespace astrea