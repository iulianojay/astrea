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

#include <trace/analysis/PositionCache.hpp>

namespace astrea {
namespace trace {

void PositionCache::reserve(std::size_t nPlatforms, std::size_t nTimesteps)
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

void PositionCache::set_position(std::size_t platformIdx, std::size_t timeIdx, const EciRadiusVec& position)
{
    _positions[platformIdx][timeIdx] = position;
}

const EciRadiusVec& PositionCache::get_position_by_id(std::size_t platformId, std::size_t timeIdx) const
{
    return _positions[_idToIndex.at(platformId)][timeIdx];
}

const EciRadiusVec& PositionCache::get_position_by_index(std::size_t platformIdx, std::size_t timeIdx) const
{
    return _positions[platformIdx][timeIdx];
}

const std::vector<EciRadiusVec>& PositionCache::get_platform_positions_by_id(std::size_t platformId) const
{
    return _positions[_idToIndex.at(platformId)];
}

const std::vector<EciRadiusVec>& PositionCache::get_platform_positions_by_index(std::size_t platformIdx) const
{
    return _positions[platformIdx];
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
