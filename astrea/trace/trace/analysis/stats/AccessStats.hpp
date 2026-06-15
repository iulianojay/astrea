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

#include <gtl/phmap.hpp>

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

    /**
     * @brief Converts the statistics to a vector of strings for output.
     *
     * @return std::vector<std::string> A vector of strings representing the statistics for each receiver ID and metric.
     */
    std::vector<std::string> to_string_vector() const;

    /**
     * @brief Accesses the rise/set statistics for all receivers.
     *
     * @return const RiseSetStats& A reference to the RiseSetStats object containing the statistics for the given receiver ID.
     */
    const auto& get_riseset_statistics() const { return _stats; }

    /**
     * @brief Accesses the rise/set statistics for a given receiver ID.
     *
     * @param receiverId The ID of the receiver to access statistics for.
     * @return const RiseSetStats& A reference to the RiseSetStats object containing the statistics for the given receiver ID.
     */
    const auto& get_riseset_statistics(std::size_t receiverId) const { return _stats.at(receiverId); }

    /**
     * @brief Accesses the access statistics for a given receiver ID and AccessMetric.
     *
     * @param receiverId The ID of the receiver to access statistics for.
     * @param metric The AccessMetric to access statistics for.
     * @return const Time& A reference to the Time object containing the statistic for the given receiver ID and metric.
     */
    const auto& get_access_metric(std::size_t receiverId, const AccessMetric& metric) const
    {
        return _accessMetrics.at(receiverId).at(metric);
    }

    /**
     * @brief Accesses the access statistics for all receiver IDs and AccessMetrics.
     *
     * @return const gtl::flat_hash_map<std::size_t, gtl::flat_hash_map<AccessMetric, Time>>& A reference to the map
     * containing the access metrics for all receiver IDs and AccessMetrics.
     */
    const auto& get_access_metrics() const { return _accessMetrics; }

    /**
     * @brief Accesses the rise/set statistics for a given receiver ID.
     *
     * @param receiverId The ID of the receiver to access statistics for.
     * @return const RiseSetStats& A reference to the RiseSetStats object containing the statistics for the given receiver ID.
     */
    const auto& get_access_statistics(const AccessMetric& metric) const { return _accessStats.at(metric); }

    /**
     * @brief Accesses the statistics for a given RiseSetMetric.
     *
     * @param metric The RiseSetMetric to access statistics for.
     * @return const Stats<Time>& A reference to the Stats<Time> object containing the statistics for the given metric.
     */
    const auto& get_hyper_statistics(const RiseSetMetric& metric) const { return _hyperStats.at(metric); }

    /**
     * @brief Accesses the statistics for a given RiseSetMetric.
     *
     * @param metric The RiseSetMetric to access statistics for.
     * @return Stats<Time>& A reference to the Stats<Time> object containing the statistics for the given metric.
     */
    auto& get_hyper_statistics(const RiseSetMetric& metric) { return _hyperStats[metric]; }

  private:
    gtl::flat_hash_map<std::size_t, RiseSetArray> _risesets;         //!< Union of all risesets to any single receiver
    gtl::flat_hash_map<std::size_t, RiseSetStats> _stats;            //!< Stats on risesets
    gtl::flat_hash_map<RiseSetMetric, HyperStats<Time>> _hyperStats; //!< Statistics on riseset stats

    gtl::flat_hash_map<std::size_t, gtl::flat_hash_map<AccessMetric, Time>> _accessMetrics; //!< Access metric values
    gtl::flat_hash_map<AccessMetric, Stats<Time>> _accessStats;                             //!< Access stats
};

} // namespace trace
} // namespace astrea