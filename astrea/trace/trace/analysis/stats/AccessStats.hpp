/**
 * @file AccessStats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for calculating access statistics.
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

#include <string>
#include <vector>

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/HyperStats.hpp>
#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/analysis/stats/Stats.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/IdPair.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

/**
 * @brief The AccessStats struct represents statistics for access times based on an AccessArray.
 *
 * It contains maps for aggregate rise sets and their statistics for each receiver ID, as well as individual rise set
 * statistics for each sender-receiver pair and hyper statistics for each receiver ID.
 */
struct AccessStats {
    /**
     * @brief Default constructor for AccessStats.
     */
    AccessStats() = default;

    /**
     * @brief Constructs an AccessStats object from an AccessArray.
     *
     * @param accesses The AccessArray containing the access times to calculate statistics for.
     */
    AccessStats(const AccessArray& accesses);

    gtl::btree_map<std::size_t, RiseSetArray> aggregateRisesets; //!< Union of all risesets to a single receiver
    gtl::btree_map<std::size_t, RiseSetStats> aggregateRisesetStats; //!< Stats of union of all risesets to a single receiver

    gtl::btree_map<IdPair, RiseSetStats> risesetStats; //!< Single viewer/target riseset stats
    gtl::btree_map<std::size_t, gtl::btree_map<RiseSetMetric, HyperStats<Time>>> stats; //!< Hyper stats on single viewer/target riseset stats
};

} // namespace trace
} // namespace astrea