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

#include <trace/analysis/stats/FoldsOfCoverage.hpp>

#include <trace/risesets/AccessArray.hpp>

using mp_units::one;

namespace astrea {
namespace trace {

FoldsOfCoverage::FoldsOfCoverage(const AccessArray& access, const Time& resolution, const Time& start, const Time& end)
{
    // get all receiver ids
    gtl::btree_set<std::size_t> ids;
    for (const auto& [idPair, risesets] : access) {
        if (risesets.size() == 0) { continue; }
        ids.insert(idPair.receiver);
    }

    const std::size_t nTimes = ((end - start) / resolution).numerical_value_in(one) + 1; // +1 to include end
    for (const auto& id : ids) {
        // collect all risesets for this receiver
        std::vector<RiseSetArray> allRisesets;
        for (const auto& [idPair, risesets] : access) {
            if (risesets.size() == 0) { continue; }
            if (idPair.receiver == id) { allRisesets.push_back(risesets); }
        }

        // loop over time
        _folds[id] = std::vector<std::size_t>(nTimes, 0);
        for (std::size_t iTime = 0; iTime < nTimes; ++iTime) {
            const Time t = start + iTime * resolution;

            // check every riseset if it has access at this time
            for (const auto& riseset : allRisesets) {
                if (riseset.has_access(t)) { ++_folds[id][iTime]; }
            }
        }
    }

    // Get stats
    for (const auto& [id, foldsVector] : _folds) {
        _stats[id] = Stats<std::size_t>(foldsVector);
    }
}

} // namespace trace
} // namespace astrea