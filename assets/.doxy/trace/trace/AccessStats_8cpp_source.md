

# File AccessStats.cpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**AccessStats.cpp**](AccessStats_8cpp.md)

[Go to the documentation of this file](AccessStats_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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
        _risesets[idPair.receiver] |= risesets;
    }

    // Get stats and access metrics for each receiver ID
    for (const auto& [id, risesets] : _risesets) {
        _stats[id]                                      = RiseSetStats(risesets);
        _accessMetrics[id][AccessMetric::AVG_DAILY_VIS] = risesets.average_daily_vis_time();
        _accessMetrics[id][AccessMetric::MTTA]          = risesets.mean_time_to_access();
    }

    // Get stats for each access metric
    for (const auto& metric : ALL_ACCESS_METRICS) {
        std::vector<Time> metricVec;
        for (const auto& [id, metricValues] : _accessMetrics) {
            metricVec.push_back(metricValues.at(metric));
        }
        _accessStats[metric] = Stats<Time>(metricVec);
    }

    // Get hyper-statistics for each riseset metric
    for (const auto& metric : ALL_RISE_SET_METRICS) {
        std::vector<Stats<Time>> statsVec;
        for (const auto& [id, risesets] : _risesets) {
            statsVec.push_back(_stats.at(id).at(metric));
        }
        _hyperStats[metric] = HyperStats<Time>(statsVec);
    }
}

std::vector<std::string> AccessStats::to_string_vector() const
{
    std::vector<std::string> retval;
    const std::size_t nReceivers      = _stats.size();
    const std::size_t nStats          = Stats<Time>::size();
    const std::size_t nHyperStats     = HyperStats<Time>::size();
    const std::size_t nRiseSetMetrics = ALL_RISE_SET_METRICS.size();
    const std::size_t nAccessMetrics  = ALL_ACCESS_METRICS.size();
    retval.reserve(nReceivers * nStats + nHyperStats * nRiseSetMetrics + nReceivers * nAccessMetrics + nAccessMetrics * nStats);

    // TODO: Another weakly enforced order
    // _stats -> _hyperStats -> _accessMetrics -> _accessStats
    for (const auto& metric : ALL_RISE_SET_METRICS) {
        for (const auto& [id, riseSetStats] : _stats) {
            const auto statStringVec = riseSetStats.at(metric).to_string_vector();
            retval.insert(retval.end(), statStringVec.begin(), statStringVec.end());
        }
    }

    for (const auto& metric : ALL_RISE_SET_METRICS) {
        const auto hyperStatsStrVec = _hyperStats.at(metric).to_string_vector();
        retval.insert(retval.end(), hyperStatsStrVec.begin(), hyperStatsStrVec.end());
    }

    for (const auto& metric : ALL_ACCESS_METRICS) {
        for (const auto& [id, accessMetrics] : _accessMetrics) {
            retval.push_back(to_formatted_string(accessMetrics.at(metric)));
        }
    }

    for (const auto& metric : ALL_ACCESS_METRICS) {
        const auto accessStatsStrVec = _accessStats.at(metric).to_string_vector();
        retval.insert(retval.end(), accessStatsStrVec.begin(), accessStatsStrVec.end());
    }

    return retval;
}

} // namespace trace
} // namespace astrea
```


