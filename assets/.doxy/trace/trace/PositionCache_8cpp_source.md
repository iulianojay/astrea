

# File PositionCache.cpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**PositionCache.cpp**](PositionCache_8cpp.md)

[Go to the documentation of this file](PositionCache_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <trace/analysis/PositionCache.hpp>

namespace astrea {
namespace trace {

void PositionCache::reserve(std::size_t nPlatforms)
{
    _platformIds.reserve(nPlatforms);
    _positions.reserve(nPlatforms);
}

std::size_t PositionCache::add_platform(std::size_t platformId, std::size_t nTimesteps)
{
    const std::size_t idx = _platformIds.size();
    _platformIds.push_back(platformId);
    _positions.emplace_back(nTimesteps);
    _idToIndex[platformId] = idx;
    return idx;
}

void PositionCache::set_position(std::size_t platformIdx, std::size_t timeIdx, const EcefRadiusVec& position)
{
    _positions[platformIdx][timeIdx] = position;
}

const EcefRadiusVec& PositionCache::get_position_by_id(std::size_t platformId, std::size_t timeIdx) const
{
    const auto& positions = _positions[_idToIndex.at(platformId)];
    if (positions.size() == 1) {
        // If only one timestep, assume fixed position
        return positions[0];
    }
    return positions[timeIdx];
}

const EcefRadiusVec& PositionCache::get_position_by_index(std::size_t platformIdx, std::size_t timeIdx) const
{
    const auto& positions = _positions[platformIdx];
    if (positions.size() == 1) {
        // If only one timestep, assume fixed position
        return positions[0];
    }
    return positions[timeIdx];
}

std::size_t PositionCache::get_index(std::size_t platformId) const { return _idToIndex.at(platformId); }

std::size_t PositionCache::get_platform_id(std::size_t platformIdx) const { return _platformIds[platformIdx]; }

std::size_t PositionCache::n_platforms() const { return _platformIds.size(); }

std::size_t PositionCache::n_timesteps() const { return _positions.empty() ? 0 : _positions[0].size(); }

void PositionCache::clear()
{
    _platformIds.clear();
    _positions.clear();
    _idToIndex.clear();
}

} // namespace trace
} // namespace astrea
```


