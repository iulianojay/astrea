/**
 * @file concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Concept definitions for astrodynamics.
 * @date 2025-10-09
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

/**
 * @brief Concept to determine if a frame is inertial.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is inertial (ICRF or J2000), false otherwise.
 */
template <typename Frame_T>
concept IsInertialFrame = (Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000);

/**
 * @brief Concept to determine if a frame is body-fixed.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is body-fixed, false otherwise.
 */
template <typename Frame_T>
concept IsBodyFixedFrame = (Frame_T::get_axis() == FrameAxis::BODY_FIXED);

/**
 * @brief Concept to determine if a frame is static (inertial or body-fixed).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is static, false otherwise.
 */
template <typename Frame_T>
concept IsStaticFrame =
    (Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 || Frame_T::get_axis() == FrameAxis::BODY_FIXED);

/**
 * @brief Concept to determine if a frame is dynamic (LVLH, RIC, VNB).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is dynamic, false otherwise.
 */
template <typename Frame_T>
concept IsDynamicFrame =
    (Frame_T::get_axis() == FrameAxis::LVLH || Frame_T::get_axis() == FrameAxis::RIC || Frame_T::get_axis() == FrameAxis::VNB);

/**
 * @brief Concept to determine if two frames share the same origin.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same origin, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = (Frame_T::get_origin() == Frame_U::get_origin());

/**
 * @brief Concept to determine if two frames share the same axis.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same axis, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameAxis = (Frame_T::get_axis() == Frame_U::get_axis());

/**
 * @brief Concept to determine if two frames are the same (same origin and same axis).
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames are the same, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept IsSameFrame = HasSameOrigin<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U>;

} // namespace astro
} // namespace astrea