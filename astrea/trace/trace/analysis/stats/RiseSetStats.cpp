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

#include <trace/analysis/stats/RiseSetStats.hpp>

#include <algorithm>

#include <mp-units/systems/si.h>

#include <trace/risesets/RiseSetArray.hpp>
#include <trace/risesets/riseset_utils.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

RiseSetStats::RiseSetStats(const RiseSetArray& risesets)
{
    stats[RiseSetMetric::ACCESS_TIME] = Stats(risesets, RiseSetMetric::ACCESS_TIME);
    stats[RiseSetMetric::GAP]         = Stats(risesets, RiseSetMetric::GAP);
}

std::vector<std::string> RiseSetStats::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(stats.size() * (DEFAULT_PERCENTILES.size() + 3));

    for (const auto& [metric, stat] : stats) {
        const auto statStringVec = stat.to_string_vector();
        retval.insert(retval.end(), statStringVec.begin(), statStringVec.end());
    }

    return retval;
}

} // namespace trace
} // namespace astrea