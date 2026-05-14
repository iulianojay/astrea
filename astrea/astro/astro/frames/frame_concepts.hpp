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
struct OriginBase;
struct AxisBase;
struct CoordinateLineBase;

template <typename T>
concept SymbolicConstant = (!std::is_const_v<T>) && (!std::is_reference_v<T>) && std::is_empty_v<T> &&
                           std::is_trivially_default_constructible_v<T> && std::is_trivially_copy_constructible_v<T> &&
                           std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>;

} // namespace detail

template <typename T>
concept IsFrame = std::derived_from<T, detail::FrameBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsOrigin = std::derived_from<T, detail::OriginBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsAxis = std::derived_from<T, detail::AxisBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsCoordinateLine = std::derived_from<T, detail::CoordinateLineBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a frame is inertial.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is inertial (ICRF or J2000), false otherwise.
 */
template <typename T>
concept IsInertialFrame = true; // TODO: Figure this out

/**
 * @brief Concept to determine if a frame is body-fixed.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is body-fixed, false otherwise.
 */
template <typename T>
concept IsFixedRotatingFrame = requires { T::rotation_rate; };

/**
 * @brief Concept to determine if a frame is static (inertial or body-fixed).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is static, false otherwise.
 */
template <typename T>
concept IsStaticFrame = (IsInertialFrame<T> || IsFixedRotatingFrame<T>);

/**
 * @brief Concept to determine if a frame is dynamic (LVLH, RIC, VNB).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is dynamic, false otherwise.
 */
template <typename T>
concept IsDynamicFrame = !IsStaticFrame<T>;

/**
 * @brief Concept to determine if two frames share the same origin.
 *
 * @tparam T The first frame type to check.
 * @tparam U The second frame type to check.
 * @return true if both frames share the same origin, false otherwise.
 */
template <IsFrame T, IsFrame U>
consteval bool has_same_origin(T t, U u)
{
    return T::origin == U::origin;
}

/**
 * @brief Concept to determine if two frames share the same axis.
 *
 * @tparam T The first frame type to check.
 * @tparam U The second frame type to check.
 * @return true if both frames share the same axis, false otherwise.
 */
template <IsFrame T, IsFrame U>
consteval bool has_same_axis(T t, U u)
{
    return T::axis == U::axis;
}

/**
 * @brief Concept to determine if a frame is derived from another frame (i.e., it has a parent member).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is derived from another frame, false otherwise.
 */
template <typename T>
concept IsDerivedFrame = IsFrame<T> && requires { T::parent; };

/**
 * @brief Concept to determine if a frame is a root frame (i.e., it has no parent member).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is a root frame, false otherwise.
 */
template <typename T>
concept IsRootFrame = IsFrame<T> && !IsDerivedFrame<T>;

/**
 * @brief Concept to determine if a frame has a fixed spatial offset from its parent frame.
 *
 * @tparam T The frame type to check.
 * @return true if the frame has a fixed spatial offset, false otherwise.
 */
template <typename T>
concept HasSpatialOffset = requires { T::origin::offset; };

/**
 * @brief Concept to determine if a frame has a fixed angular offset from its parent frame.
 *
 * @tparam T The frame type to check.
 * @return true if the frame has a fixed angular offset, false otherwise.
 */
template <typename T>
concept HasAngularOffset = requires { T::axis::misalignment; };

/**
 * @brief Concept to determine if a frame is a FixedOffsetFrame, which is defined as a frame that is derived from
 * another frame and has either a spatial offset, an angular offset, or both.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is a FixedOffsetFrame, false otherwise.
 */
template <typename T>
concept IsFixedOffsetFrame = IsDerivedFrame<T> && (HasSpatialOffset<T> || HasAngularOffset<T>);

template <IsFrame T, IsFrame U>
consteval bool has_same_parent(T t, U u)
{
    return false;
}

template <IsFrame T, IsFrame U>
    requires(IsDerivedFrame<T> && IsDerivedFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return T::parent == U::parent;
}

template <IsFrame T, IsFrame U>
    requires(IsRootFrame<T> && IsRootFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return true;
}

/**
 * @brief Concept to determine if two frames are the same (same origin and same axis).
 *
 * @tparam T The first frame type to check.
 * @tparam U The second frame type to check.
 * @return true if both frames are the same, false otherwise.
 */
template <typename T, typename U>
consteval bool is_same_frame(T t, U u)
{
    return has_same_origin(t, u) && has_same_axis(t, u) && has_same_parent(t, u);
}

} // namespace astro
} // namespace astrea