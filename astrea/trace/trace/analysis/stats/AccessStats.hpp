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

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/IdPair.hpp>

namespace astrea {
namespace trace {

struct HyperStats {

    HyperStats() = default;

    HyperStats(const std::vector<Stats>& statsVec);

    std::vector<std::string> to_string_vector() const;

    Stats min;
    Stats max;
    Stats avg;
    std::vector<Stats> percentiles;
};

struct AccessStats {
    AccessStats() = default;

    AccessStats(const AccessArray& accesses);

    gtl::btree_map<std::size_t, std::pair<HyperStats, HyperStats>> stats;
    gtl::btree_map<IdPair, RiseSetStats> risesetStats;
};

} // namespace trace
} // namespace astrea