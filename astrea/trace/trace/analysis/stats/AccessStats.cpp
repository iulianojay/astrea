/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <trace/analysis/stats/AccessStats.hpp>

#include <trace/risesets/AccessArray.hpp>

namespace astrea {
namespace trace {


AccessStats::AccessStats(const AccessArray& accesses)
{
    // Aggregate risesets for receivers only
    for (const auto& [idPair, risesets] : accesses) {
        if (risesets.size() == 0) { continue; }
        risesetStats[idPair] = RiseSetStats(risesets);
        aggregateRisesets[idPair.receiver] |= risesets;
    }

    for (const auto& [id, risesets] : aggregateRisesets) {
        // Get hyper-statistics for each riseset metric
        for (const auto& metric : { RiseSetMetric::ACCESS_TIME, RiseSetMetric::GAP }) {
            std::vector<Stats<Time>> statsVec;
            for (const auto& [idPair, risesets] : accesses) {
                if (idPair.sender == id || idPair.receiver == id) {
                    const auto& stats = risesetStats.at(idPair).stats;
                    statsVec.push_back(stats.at(metric));
                }
            }
            stats[id][metric] = HyperStats<Time>(statsVec);
        }

        // Get stats on risesets unioned over each receiver
        aggregateRisesetStats[id] = RiseSetStats(risesets);
    }
}

} // namespace trace
} // namespace astrea
