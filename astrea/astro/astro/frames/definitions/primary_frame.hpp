/**
 * @file primary_frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Registration point for the primary frame used across astrea.
 * @date 2025-04-22
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

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>

namespace astrea {
namespace astro {

namespace frames {

inline constexpr auto primary       = frames::earth::icrf;
inline constexpr auto primary_fixed = frames::earth::earth_fixed;

} // namespace frames

static_assert(IsInertialFrame<std::decay_t<decltype(frames::primary)>>, "The primary frame must be inertial.");

} // namespace astro
} // namespace astrea
