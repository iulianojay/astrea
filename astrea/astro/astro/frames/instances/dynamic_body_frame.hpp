/**
 * @file dynamic_body_frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for dynamic body frames.
 * @date 2025-08-05
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

#include <astro/frames/DynamicFrame.hpp>
#include <astro/frames/Frame.hpp>

namespace astrea {
namespace astro {
namespace frames {
namespace dynamic {

inline constexpr struct body final : Frame<"body", DynamicOrigin<"body">{}, DynamicAxis<"body">{}> {
} body;

} // namespace dynamic
} // namespace frames
} // namespace astro
} // namespace astrea