/**
 * @file HyperStats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for calculating statistics of statistics.
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

#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/analysis/stats/Stats.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/IdPair.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

/**
 * @brief The HyperStats struct represents statistics of statistics, allowing for the calculation of statistics on a vector of Stats<T>.
 *
 * It contains Stats<T> for the minimum, maximum, and average values across the input Stats<T> vector, as well as a vector of Stats<T> for each percentile.
 */
template <class T = Time>
struct HyperStats {

    /**
     * @brief Default constructor for HyperStats.
     */
    HyperStats() = default;

    /**
     * @brief Constructs a HyperStats object from a vector of Stats<T>.
     *
     * @param statsVec A vector of Stats<T> to calculate the statistics of.
     * @throws std::runtime_error If the input vector is empty.
     */
    HyperStats(const std::vector<Stats<T>>& statsVec)
    {
        std::vector<T> minVals;
        std::vector<T> maxVals;
        std::vector<T> avgVals;
        std::vector<std::vector<T>> pctVals;

        const std::size_t statsSize = statsVec.size();
        minVals.reserve(statsSize);
        maxVals.reserve(statsSize);
        avgVals.reserve(statsSize);

        const std::size_t nPercentiles = DEFAULT_PERCENTILES.size();
        pctVals.resize(nPercentiles);
        for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
            pctVals[ii].reserve(statsSize);
        }

        // stats of stats. oh joy
        for (const auto& stats : statsVec) {
            // assume this marks the Stats as empty
            if (stats.percentiles.size() == 0) { continue; }

            minVals.push_back(stats.min);
            maxVals.push_back(stats.max);
            avgVals.push_back(stats.avg);

            for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
                pctVals[ii].push_back(stats.percentiles[ii]);
            }
        }

        min = Stats<T>(minVals);
        max = Stats<T>(maxVals);
        avg = Stats<T>(avgVals);
        for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
            percentiles.push_back(Stats<T>(pctVals[ii]));
        }
    }

    /**
     * @brief Converts the statistics of statistics to a vector of strings for output.
     *
     * @return std::vector<std::string> A vector of strings representing the statistics of statistics.
     */
    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(HyperStats<T>::size());

        const auto minStrVec = min.to_string_vector();
        const auto avgStrVec = avg.to_string_vector();
        const auto maxStrVec = max.to_string_vector();

        retval.insert(retval.end(), minStrVec.begin(), minStrVec.end());
        retval.insert(retval.end(), avgStrVec.begin(), avgStrVec.end());
        retval.insert(retval.end(), maxStrVec.begin(), maxStrVec.end());

        for (const auto& pct : percentiles) {
            const auto pctStrVec = pct.to_string_vector();
            retval.insert(retval.end(), pctStrVec.begin(), pctStrVec.end());
        }

        return retval;
    }

    static constexpr std::size_t size() { return Stats<T>::size() * (3 + DEFAULT_PERCENTILES.size()); }

    Stats<T> min;                      //!< Statistics for the minimum values across the input Stats<T> vector.
    Stats<T> max;                      //!< Statistics for the maximum values across the input Stats<T> vector.
    Stats<T> avg;                      //!< Statistics for the average values across the input Stats<T> vector.
    std::vector<Stats<T>> percentiles; //!< Statistics for each percentile across the input Stats<T> vector.
};

} // namespace trace
} // namespace astrea