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

using mp_units::one;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {


Stats::Stats(const RiseSetArray& risesets, const RiseSetMetric& metric)
{
    percentiles.reserve(defaultPercentiles.size());
    switch (metric) {
        case (RiseSetMetric::ACCESS_TIME): *this = Stats(risesets.get_access_times()); break;
        case (RiseSetMetric::GAP): *this = Stats(risesets.get_gap_times()); break;
        default: throw std::runtime_error("Unrecognized riseset metric.");
    }
}

Stats::Stats(std::vector<Time> times)
{
    if (times.size() == 0) { throw std::runtime_error("Cannot calculate statistics on an empty vector."); }

    // Sort automatically gives min, max, and sets up for percentile calcs
    std::sort(times.begin(), times.end());

    min = times[0];
    max = times[times.size() - 1];
    avg = 0.0 * s;
    for (const auto& time : times) {
        avg += time;
    }
    avg /= static_cast<double>(times.size());

    const std::size_t nTimes = times.size();
    for (const auto& pct : defaultPercentiles) {
        const std::size_t index = static_cast<std::size_t>(std::ceil(pct.numerical_value_in(one) * nTimes)) - 1;
        percentiles.push_back(times[index]);
    }
}

std::vector<std::string> Stats::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(3 + defaultPercentiles.size());

    retval.push_back(to_formatted_string(min));
    retval.push_back(to_formatted_string(avg));
    retval.push_back(to_formatted_string(max));
    for (const auto& pct : percentiles) {
        retval.push_back(to_formatted_string(pct));
    }

    return retval;
}

RiseSetStats::RiseSetStats(const std::size_t sender, const std::size_t receiver, const RiseSetArray& risesets) :
    sender(sender),
    receiver(receiver)
{
    stats[RiseSetMetric::ACCESS_TIME] = Stats(risesets, RiseSetMetric::ACCESS_TIME);
    stats[RiseSetMetric::GAP]         = Stats(risesets, RiseSetMetric::GAP);
}

std::vector<std::string> RiseSetStats::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(stats.size() * (Stats().defaultPercentiles.size() + 3));

    for (const auto& [metric, stat] : stats) {
        const auto statStringVec = stat.to_string_vector();
        retval.insert(retval.end(), statStringVec.begin(), statStringVec.end());
    }

    return retval;
}

} // namespace trace
} // namespace astrea