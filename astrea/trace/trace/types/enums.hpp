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

#include <array>
#include <string>

#include <gtl/phmap.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Enumeration of statistical measures for RiseSetArray.
 */
enum class StatType : EnumType {
    MIN, //!< Minimum value
    AVG, //!< Mean value
    MAX, //!< Maximum value
    PCT  //!< Percentile value
};

static const std::array<StatType, 4> ALL_STAT_TYPES = { StatType::MIN, StatType::AVG, StatType::MAX, StatType::PCT };
static const gtl::flat_hash_map<StatType, std::string> STAT_TYPE_STRINGS = { { StatType::MIN, "MIN" },
                                                                             { StatType::AVG, "AVG" },
                                                                             { StatType::MAX, "MAX" },
                                                                             { StatType::PCT, "PCT" } };

/**
 * @brief Enumeration for different rise/set metrics.
 */
enum class RiseSetMetric : EnumType {
    GAP,        //!< Time gap between rise and set (equal to revisit)
    ACCESS_TIME //!< Time of access based on rise and set times
};

static const std::array<RiseSetMetric, 2> ALL_RISE_SET_METRICS = { RiseSetMetric::GAP, RiseSetMetric::ACCESS_TIME };
static const gtl::flat_hash_map<RiseSetMetric, std::string> RISE_SET_METRIC_STRINGS = { { RiseSetMetric::GAP, "GAP" },
                                                                                        { RiseSetMetric::ACCESS_TIME, "ACCESS_TIME" } };
/**
 * @brief Enumeration for different access metrics.
 */
enum class AccessMetric : EnumType {
    MTTA,         //!< Mean time to access
    AVG_DAILY_VIS //!< Average daily visibility time
};

static const std::array<AccessMetric, 2> ALL_ACCESS_METRICS = { AccessMetric::MTTA, AccessMetric::AVG_DAILY_VIS };
static const gtl::flat_hash_map<AccessMetric, std::string> ACCESS_METRIC_STRINGS = { { AccessMetric::MTTA, "MTTA" },
                                                                                     { AccessMetric::AVG_DAILY_VIS, "AVG_DAILY_VIS" } };

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

static const std::array<GridType, 5> ALL_GRID_TYPES                      = { GridType::UNIFORM,
                                                                             GridType::EQUAL_AREA,
                                                                             GridType::WEIGHTED_NS,
                                                                             GridType::WEIGHTED_EW,
                                                                             GridType::MANUAL };
static const gtl::flat_hash_map<GridType, std::string> GRID_TYPE_STRINGS = { { GridType::UNIFORM, "UNIFORM" },
                                                                             { GridType::EQUAL_AREA, "EQUAL_AREA" },
                                                                             { GridType::WEIGHTED_NS, "WEIGHTED_NS" },
                                                                             { GridType::WEIGHTED_EW, "WEIGHTED_EW" },
                                                                             { GridType::MANUAL, "MANUAL" } };

} // namespace trace
} // namespace astrea