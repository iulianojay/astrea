/**
 * @file Stats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for calculating statistics.
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

#include <concepts>
#include <string>
#include <vector>

#include <gtl/btree.hpp>
#include <mp-units/concepts.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <trace/risesets/RiseSetArray.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

// Default percentiles to calculate for statistics.
static const std::vector<Unitless> DEFAULT_PERCENTILES{ 1, 5, 10, 25, 50, 75, 90, 95, 99 };

/**
 * @brief The Stats struct represents basic statistics (min, max, average, and percentiles) for a vector of values of type T.
 */
template <class T = Time>
struct Stats {

    /**
     * @brief Default constructor for Stats.
     */
    Stats() = default;

    /**
     * @brief Constructs a Stats object from a vector of values of type T. Deleted for non-Time types.
     *
     * @param values A vector of values to calculate statistics for.
     * @throws std::runtime_error If the input vector is empty.
     */
    Stats(const RiseSetArray& risesets, const RiseSetMetric& metric) = delete;

    /**
     * @brief Constructs a Stats object from a vector of values of type T.
     *
     * @param values A vector of values to calculate statistics for.
     * @throws std::runtime_error If the input vector is empty.
     */
    Stats(std::vector<T> values)
    {
        using mp_units::one;
        using mp_units::si::unit_symbols::s;

        if (values.size() == 0) { throw std::runtime_error("Cannot calculate statistics on an empty vector."); }

        // Sort automatically gives min, max, and sets up for percentile calcs
        std::sort(values.begin(), values.end());

        min = values[0];
        max = values[values.size() - 1];
        avg = T(); // this should be 0?
        for (const auto& time : values) {
            avg += time;
        }
        avg /= static_cast<double>(values.size());

        const std::size_t nTimes = values.size();
        for (const auto& pct : DEFAULT_PERCENTILES) {
            const std::size_t index = static_cast<std::size_t>(std::ceil(pct.numerical_value_in(one) * nTimes / 100)) - 1;
            percentiles.push_back(values[index]);
        }
    }

    /**
     * @brief Converts the statistics to a vector of strings for output.
     *
     * @return std::vector<std::string> A vector of strings representing the statistics.
     */
    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(3 + DEFAULT_PERCENTILES.size());

        retval.push_back(std::to_string(min));
        retval.push_back(std::to_string(avg));
        retval.push_back(std::to_string(max));
        for (const auto& pct : percentiles) {
            retval.push_back(std::to_string(pct));
        }

        return retval;
    }

    T min;                      //!< The minimum value in the vector.
    T max;                      //!< The maximum value in the vector.
    T avg;                      //!< The average value in the vector.
    std::vector<T> percentiles; //!< A vector of percentiles corresponding to the DEFAULT_PERCENTILES.
};

/**
 * @brief Specialization of the Stats struct for Time type, which can be constructed from a RiseSetArray and a RiseSetMetric.
 *
 * @tparam T The type of the statistics, specialized for Time.
 * @param risesets The RiseSetArray containing the rise and set times to calculate statistics for.
 * @param metric The RiseSetMetric indicating which metric to calculate statistics for (ACCESS_TIME or GAP).
 * @throws std::runtime_error If the RiseSetMetric is unrecognized.
 */
template <>
inline Stats<Time>::Stats(const RiseSetArray& risesets, const RiseSetMetric& metric)
{
    percentiles.reserve(DEFAULT_PERCENTILES.size());
    switch (metric) {
        case (RiseSetMetric::ACCESS_TIME): {
            *this = Stats(risesets.get_access_times());
            break;
        }
        case (RiseSetMetric::GAP): {
            *this = risesets.size() > 2 ? Stats(risesets.get_gap_times()) : Stats();
            break;
        }
        default: throw std::runtime_error("Unrecognized riseset metric.");
    }
}

/**
 * @brief Specialization of the to_string_vector method for Time type, which formats the Time values as strings.
 *
 * @return std::vector<std::string> A vector of strings representing the statistics, formatted as time strings.
 */
template <>
inline std::vector<std::string> Stats<Time>::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(3 + DEFAULT_PERCENTILES.size());

    retval.push_back(to_formatted_string(min));
    retval.push_back(to_formatted_string(avg));
    retval.push_back(to_formatted_string(max));
    for (const auto& pct : percentiles) {
        retval.push_back(to_formatted_string(pct));
    }

    return retval;
}

} // namespace trace
} // namespace astrea