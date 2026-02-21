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


HyperStats::HyperStats(const std::vector<Stats>& statsVec)
{
    std::vector<Time> minVals;
    std::vector<Time> maxVals;
    std::vector<Time> avgVals;
    std::vector<std::vector<Time>> pctVals;

    const std::size_t statsSize = statsVec.size();
    minVals.reserve(statsSize);
    maxVals.reserve(statsSize);
    avgVals.reserve(statsSize);

    const std::size_t nPercentiles = Stats().defaultPercentiles.size();
    pctVals.resize(nPercentiles);
    for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
        pctVals[ii].reserve(statsSize);
    }

    // stats of stats. oh joy
    for (const auto& stats : statsVec) {
        minVals.push_back(stats.min);
        maxVals.push_back(stats.max);
        avgVals.push_back(stats.avg);

        for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
            pctVals[ii].push_back(stats.percentiles[ii]);
        }
    }

    min = Stats(minVals);
    max = Stats(maxVals);
    avg = Stats(avgVals);
    for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
        percentiles.push_back(Stats(pctVals[ii]));
    }
}


std::vector<std::string> HyperStats::to_string_vector() const
{
    std::vector<std::string> retval;

    const auto minStrVec = min.to_string_vector();
    const auto avgStrVec = avg.to_string_vector();
    const auto maxStrVec = max.to_string_vector();

    retval.reserve(minStrVec.size() * minStrVec.size());
    retval.insert(retval.end(), minStrVec.begin(), minStrVec.end());
    retval.insert(retval.end(), avgStrVec.begin(), avgStrVec.end());
    retval.insert(retval.end(), maxStrVec.begin(), maxStrVec.end());

    for (const auto& pct : percentiles) {
        const auto pctStrVec = pct.to_string_vector();
        retval.insert(retval.end(), pctStrVec.begin(), pctStrVec.end());
    }

    return retval;
}


AccessStats::AccessStats(const AccessArray& accesses)
{
    gtl::btree_set<std::size_t> ids;
    for (const auto& [idPair, risesets] : accesses) {
        ids.insert(idPair.sender);
        ids.insert(idPair.receiver);
        risesetStats[idPair] = RiseSetStats(idPair.sender, idPair.receiver, risesets);
    }

    for (const auto& id : ids) {
        std::vector<Stats> accessStatsVec;
        std::vector<Stats> gapStatsVec;
        for (const auto& [idPair, risesets] : accesses) {
            if (idPair.sender == id || idPair.receiver == id) {
                const auto& stats = risesetStats.at(idPair);
                accessStatsVec.push_back(stats.stats.at(RiseSetMetric::ACCESS_TIME));
                gapStatsVec.push_back(stats.stats.at(RiseSetMetric::GAP));
            }
        }
        stats[id] = std::make_pair(HyperStats(accessStatsVec), HyperStats(gapStatsVec));
    }
}

} // namespace trace
} // namespace astrea
