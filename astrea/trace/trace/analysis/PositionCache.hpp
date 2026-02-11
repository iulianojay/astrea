/**
 * @file PositionCache.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Optimized position caching for access analysis
 * @date 2026-02-10
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 */
#pragma once

#include <unordered_map>
#include <vector>

#include <gtl/btree.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

/**
 * @brief Contiguous memory cache for platform positions across time
 *
 * Uses structure-of-arrays layout for better cache locality and SIMD potential
 */
class PositionCache {
  public:
    PositionCache()  = default;
    ~PositionCache() = default;

    /**
     * @brief Reserve space for platforms and timesteps
     */
    void reserve(std::size_t nPlatforms, std::size_t nTimesteps)
    {
        _platformIds.reserve(nPlatforms);
        _positions.reserve(nPlatforms);
        _llaCache.reserve(nPlatforms);
    }

    /**
     * @brief Add a platform to the cache
     */
    std::size_t add_platform(std::size_t platformId, std::size_t nTimesteps)
    {
        const std::size_t idx = _platformIds.size();
        _platformIds.push_back(platformId);
        _positions.emplace_back(nTimesteps);
        _llaCache.emplace_back(nTimesteps);
        _idToIndex[platformId] = idx;
        return idx;
    }

    /**
     * @brief Set position for a platform at a specific timestep
     */
    void set_position(std::size_t platformIdx, std::size_t timeIdx, const EciRadiusVec& position, const astro::Geodetic& lla)
    {
        _positions[platformIdx][timeIdx] = position;
        _llaCache[platformIdx][timeIdx]  = lla;
    }

    /**
     * @brief Get position by platform ID and time index
     */
    const EciRadiusVec& get_position(std::size_t platformId, std::size_t timeIdx) const
    {
        return _positions[_idToIndex.at(platformId)][timeIdx];
    }

    /**
     * @brief Get LLA by platform ID and time index
     */
    const astro::Geodetic& get_lla(std::size_t platformId, std::size_t timeIdx) const
    {
        return _llaCache[_idToIndex.at(platformId)][timeIdx];
    }

    /**
     * @brief Get position by platform index and time index (faster)
     */
    const EciRadiusVec& get_position_fast(std::size_t platformIdx, std::size_t timeIdx) const
    {
        return _positions[platformIdx][timeIdx];
    }

    /**
     * @brief Get LLA by platform index and time index (faster)
     */
    const astro::Geodetic& get_lla_fast(std::size_t platformIdx, std::size_t timeIdx) const
    {
        return _llaCache[platformIdx][timeIdx];
    }

    /**
     * @brief Get all positions for a platform across time
     */
    const std::vector<EciRadiusVec>& get_platform_positions(std::size_t platformIdx) const
    {
        return _positions[platformIdx];
    }

    /**
     * @brief Get all LLAs for a platform across time
     */
    const std::vector<astro::Geodetic>& get_platform_lla(std::size_t platformIdx) const
    {
        return _llaCache[platformIdx];
    }

    /**
     * @brief Convert platform ID to internal index
     */
    std::size_t get_index(std::size_t platformId) const { return _idToIndex.at(platformId); }

    /**
     * @brief Get platform ID from internal index
     */
    std::size_t get_platform_id(std::size_t platformIdx) const { return _platformIds[platformIdx]; }

    /**
     * @brief Get nber of platforms
     */
    std::size_t n_platforms() const { return _platformIds.size(); }

    /**
     * @brief Get nber of timesteps
     */
    std::size_t n_timesteps() const { return _positions.empty() ? 0 : _positions[0].size(); }

    /**
     * @brief Clear all data
     */
    void clear()
    {
        _platformIds.clear();
        _positions.clear();
        _llaCache.clear();
        _idToIndex.clear();
    }

  private:
    std::vector<std::size_t> _platformIds;               //!< Platform IDs in order
    std::vector<std::vector<EciRadiusVec>> _positions;   //!< [platformIdx][timeIdx]
    std::vector<std::vector<astro::Geodetic>> _llaCache; //!< Cache for LLA
    gtl::btree_map<std::size_t, std::size_t> _idToIndex; //!< Map from platform ID to index
};

} // namespace trace
} // namespace astrea
