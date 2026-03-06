

# File RiseSetStats.cpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**RiseSetStats.cpp**](RiseSetStats_8cpp.md)

[Go to the documentation of this file](RiseSetStats_8cpp.md)


```C++
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
    for (const auto& metric : ALL_RISE_SET_METRICS) {
        _stats[metric] = Stats(risesets, metric);
    }
}

std::vector<std::string> RiseSetStats::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(ALL_RISE_SET_METRICS.size() * Stats<Time>::size());

    for (const auto& metric : ALL_RISE_SET_METRICS) {
        const auto statStringVec = _stats.at(metric).to_string_vector();
        retval.insert(retval.end(), statStringVec.begin(), statStringVec.end());
    }

    return retval;
}

} // namespace trace
} // namespace astrea
```


