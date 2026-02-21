/**
 * @file RiseSetStats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for calculating riseset statistics.
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

#include <trace/trace.fwd.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {


struct Stats {

    Stats() = default;

    Stats(const RiseSetArray& risesets, const RiseSetMetric& metric);

    Stats(std::vector<Time> values);

    std::vector<std::string> to_string_vector() const;

    Time min;
    Time max;
    Time avg;
    std::vector<Time> percentiles;

    std::vector<Unitless> defaultPercentiles{ 1, 5, 10, 25, 50, 75, 90, 95, 99 };
};


struct RiseSetStats {

    RiseSetStats() = default;

    RiseSetStats(const std::size_t sender, const std::size_t receiver, const RiseSetArray& risesets);

    std::vector<std::string> to_string_vector() const;

    std::size_t sender;
    std::size_t receiver;

    gtl::btree_map<RiseSetMetric, Stats> stats;
};

} // namespace trace
} // namespace astrea
