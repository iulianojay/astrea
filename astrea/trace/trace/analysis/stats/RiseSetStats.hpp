/**
 * @file RiseSetStats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for calculating riseset statistics.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <gtl/phmap.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/Stats.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

/**
 * @brief The RiseSetStats struct represents statistics for rise and set times based on a RiseSetArray and a RiseSetMetric.
 *
 * It contains a map of RiseSetMetric to Stats<Time>, which holds the calculated statistics for each metric (GAP and ACCESS_TIME).
 */
struct RiseSetStats {

    /**
     * @brief Default constructor for RiseSetStats.
     */
    RiseSetStats() = default;

    /**
     * @brief Constructs a RiseSetStats object from a RiseSetArray and a RiseSetMetric.
     *
     * @param risesets The RiseSetArray containing the rise and set times to calculate statistics for.
     * @throws std::runtime_error If the RiseSetMetric is unrecognized.
     */
    RiseSetStats(const RiseSetArray& risesets);

    /**
     * @brief Converts the statistics to a vector of strings for output.
     *
     * @return std::vector<std::string> A vector of strings representing the statistics for each metric.
     */
    std::vector<std::string> to_string_vector() const;

    /**
     * @brief Accesses the statistics for a given RiseSetMetric.
     *
     * @param metric The RiseSetMetric to access statistics for.
     * @return const Stats<Time>& A reference to the Stats<Time> object containing the statistics for the given metric.
     */
    const auto& at(const RiseSetMetric& metric) const { return _stats.at(metric); }

    /**
     * @brief Accesses the statistics for a given RiseSetMetric.
     *
     * @param metric The RiseSetMetric to access statistics for.
     * @return Stats<Time>& A reference to the Stats<Time> object containing the statistics for the given metric.
     */
    auto& operator[](const RiseSetMetric& metric) { return _stats[metric]; }

  private:
    gtl::flat_hash_map<RiseSetMetric, Stats<Time>> _stats; //!< Map of RiseSetMetric to Stats<Time> containing the calculated statistics for each metric.
};

} // namespace trace
} // namespace astrea
