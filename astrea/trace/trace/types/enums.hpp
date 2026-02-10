/**
 * @file enums.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains enums definitions for the astrea access library.
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

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Enumeration of statistical measures for RiseSetArray.
 */
enum class Stat : EnumType {
    MIN,  //!< Minimum value
    MEAN, //!< Mean value
    MAX,  //!< Maximum value
    PCT   //!< Percentile value
};

/**
 * @brief Enumeration for different rise/set metrics.
 */
enum class RisesetMetric : EnumType {
    GAP,        //!< Time gap between rise and set
    ACCESS_TIME //!< Time of access based on rise and set times
};

/**
 * @brief Enumeration for different grid types.
 */
enum class GridType : EnumType {
    UNIFORM,     //!< Uniform grid with equal spacing
    EQUAL_AREA,  //!< Equal area grid with varying spacing
    WEIGHTED_NS, //!< Weighted grid with North-South emphasis
    WEIGHTED_EW, //!< Weighted grid with East-West emphasis
    MANUAL       //!< Manual grid with user-defined points
};

} // namespace trace
} // namespace astrea