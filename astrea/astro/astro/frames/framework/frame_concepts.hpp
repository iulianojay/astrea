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

namespace astrea {
namespace astro {


namespace detail {

// Base classes for each frame component type, used to identify them in concepts. These are not intended to be used directly by users.
struct FrameBase;
struct OriginBase;
struct AxisBase;
struct CoordinateLineBase;
struct BodyFixedFrameBase;
struct SynodicFrameBase;

/**
 * @brief A symbolic constant is a type that is empty, trivially constructible, trivially copyable, trivially moveable, and trivially destructible.
 */
template <typename T>
concept SymbolicConstant = (!std::is_const_v<T>) && (!std::is_reference_v<T>) && std::is_empty_v<T> &&
                           std::is_trivially_default_constructible_v<T> && std::is_trivially_copy_constructible_v<T> &&
                           std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>;

} // namespace detail

/**
 * @brief Concept to determine if a type is a frame, which is defined as a type that derives from FrameBase and is a symbolic constant.
 */
template <typename T>
concept IsFrame = std::derived_from<T, detail::FrameBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a type is an origin, which is defined as a type that derives from OriginBase and is a symbolic constant.
 */
template <typename T>
concept IsOrigin = std::derived_from<T, detail::OriginBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a type is an axis, which is defined as a type that derives from AxisBase and is a symbolic constant.
 */
template <typename T>
concept IsAxis = std::derived_from<T, detail::AxisBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a frame is inertial.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is inertial (ICRF or J2000), false otherwise.
 */
template <typename T>
concept IsInertialFrame = true; // IsFrame<T> && (T::axis == axes::icrf || T::axis == axes::j2000); // TODO: Generalize this idea

/**
 * @brief Concept to determine if a frame is body-fixed.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is body-fixed, false otherwise.
 */
template <typename T>
concept IsBodyFixedFrame = std::derived_from<T, detail::BodyFixedFrameBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a frame is a synodic frame.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is a synodic frame, false otherwise.
 */
template <typename T>
concept IsSynodicFrame = std::derived_from<T, detail::SynodicFrameBase> && detail::SymbolicConstant<T>;

/**
 * @brief Concept to determine if a frame is static (inertial or body-fixed).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is static, false otherwise.
 */
template <typename T>
concept IsStaticFrame = (IsInertialFrame<T> || IsBodyFixedFrame<T>);

/**
 * @brief Concept to determine if a frame is dynamic (LVLH, RIC, VNB).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is dynamic, false otherwise.
 */
template <typename T>
concept IsDynamicFrame = !IsStaticFrame<T>;

/**
 * @brief Concept to determine if an origin is derived from another origin (i.e., it has a parent member).
 */
template <typename T>
concept IsDerivedOrigin = IsOrigin<T> && requires { T::parent; };

/**
 * @brief Concept to determine if an origin is a root origin (i.e., it has no parent member).
 */
template <typename T>
concept IsRootOrigin = IsOrigin<T> && !IsDerivedOrigin<T>;

/**
 * @brief Concept to determine if an axis is derived from another axis (i.e., it has a parent member).
 */
template <typename T>
concept IsDerivedAxis = IsAxis<T> && requires { T::parent; };

/**
 * @brief Concept to determine if an axis is a root axis (i.e., it has no parent member).
 */
template <typename T>
concept IsRootAxis = IsAxis<T> && !IsDerivedAxis<T>;

/**
 * @brief A helper variable template that is always false, used for static_asserts in templates that should never be instantiated.
 */
template <typename>
inline constexpr bool always_false = false;

/**
 * @brief Concept to determine if a frame is derived from another frame (i.e., it has a parent member).
 *
 * @tparam T The frame type to check.
 * @return true if the frame is derived from another frame, false otherwise.
 */
template <typename T>
concept IsDerivedFrame = IsFrame<T> && (requires { T::parent; } || IsDerivedOrigin<T> || IsDerivedAxis<T>);

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
concept HasSpatialOffset = requires { T::origin.offset; } || requires { T::offset; };

/**
 * @brief Concept to determine if a frame has a fixed angular offset from its parent frame.
 *
 * @tparam T The frame type to check.
 * @return true if the frame has a fixed angular offset, false otherwise.
 */
template <typename T>
concept HasAngularOffset = requires { T::axis.misalignment; } || requires { T::misalignment; };

/**
 * @brief Concept to determine if a frame is a FixedOffsetFrame, which is defined as a frame that is derived from
 * another frame and has either a spatial offset, an angular offset, or both.
 *
 * @tparam T The frame type to check.
 * @return true if the frame is a FixedOffsetFrame, false otherwise.
 */
template <typename T>
concept IsFixedOffsetFrame = IsDerivedFrame<T> && (HasSpatialOffset<T> || HasAngularOffset<T>);

/**
 * @brief Concept to determine if a frame is a derived directly from another
 *
 * @tparam T The frame type to check.
 * @tparam U The frame type to check against.
 * @return true if the frame is a child of the other frame, false otherwise.
 */
template <typename T, typename U>
concept IsChildOf = (IsDerivedAxis<decltype(T::axis)> && equivalent(T::axis.parent, U::axis)) ||
                    (IsDerivedOrigin<decltype(T::origin)> && equivalent(T::origin.parent, U::origin)) ||
                    (IsDerivedFrame<T> && equivalent(T::parent, U{}));

/**
 * @brief Helper function to determine if two frames share the same parent frame. This is used in the get_dcm function
 * for FixedOffsetFrames to ensure that the input and output frames share the same parent frame.
 *
 * @tparam T The type of the first frame.
 * @tparam U The type of the second frame.
 * @param t An instance of the first frame type (not used, only for type deduction).
 * @param u An instance of the second frame type (not used, only for type deduction).
 * @return true if the frames share the same parent frame, false otherwise.
 */
template <IsFrame T, IsFrame U>
consteval bool has_same_parent(T t, U u)
{
    return false;
}

/**
 * @brief Specialization of has_same_parent for frames that are both derived frames. This checks if the parent types are the same.
 *
 * @tparam T The type of the first frame, must be a derived frame.
 * @tparam U The type of the second frame, must be a derived frame.
 * @param t An instance of the first frame type (not used, only for type deduction).
 * @param u An instance of the second frame type (not used, only for type deduction).
 * @return true if the frames share the same parent frame, false otherwise.
 */
template <IsFrame T, IsFrame U>
    requires(IsDerivedFrame<T> && IsDerivedFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return std::is_same_v<decltype(T::parent), decltype(U::parent)>;
}

/**
 * @brief Specialization of has_same_parent for frames that are both root frames. Root frames are considered to share the same parent (themselves).
 *
 * @tparam T The type of the first frame, must be a root frame.
 * @tparam U The type of the second frame, must be a root frame.
 * @param t An instance of the first frame type (not used, only for type deduction).
 * @param u An instance of the second frame type (not used, only for type deduction).
 * @return true if the frames share the same parent frame, false otherwise.
 */
template <IsFrame T, IsFrame U>
    requires(IsRootFrame<T> && IsRootFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return true;
}

} // namespace astro
} // namespace astrea