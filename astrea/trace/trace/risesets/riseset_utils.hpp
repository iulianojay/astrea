/**
 * @file riseset_utils.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Utility functions for manipulating RiseSetArray objects.
 * @date 2025-08-03
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

#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Union of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The union of the two RiseSetArray objects.
 */
RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b);

/**
 * @brief Intersection of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The intersection of the two RiseSetArray objects.
 */
RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b);

/**
 * @brief Difference of two RiseSetArray objects.
 *
 * @param a The first RiseSetArray.
 * @param b The second RiseSetArray.
 * @return RiseSetArray The difference of the two RiseSetArray objects.
 */
RiseSetArray riseset_difference(const RiseSetArray& a, const RiseSetArray& b);

} // namespace trace
} // namespace astrea