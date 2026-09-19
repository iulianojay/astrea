/**
 * @file PositionCache.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for position caching trace library.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <vector>

#include <gtl/phmap.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/angular_elements.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

using EcefRadiusVec = astro::RadiusVector<astro::frames::earth::earth_fixed>;

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
     *
     * @param nPlatforms Number of platforms to cache
     */
    void reserve(std::size_t nPlatforms);

    /**
     * @brief Add a platform to the cache
     *
     * @param platformId Unique ID of the platform
     * @param nTimesteps Number of timesteps to cache for this platform
     * @return std::size_t Index of the platform in the cache
     */
    std::size_t add_platform(std::size_t platformId, std::size_t nTimesteps);

    /**
     * @brief Set position for a platform at a specific timestep
     *
     * @param platformIdx Index of the platform in the cache
     * @param timeIdx Index of the timestep
     * @param position ECI position vector to cache
     */
    void set_position(std::size_t platformIdx, std::size_t timeIdx, const EcefRadiusVec& position);

    /**
     * @brief Get position by platform ID and time index
     *
     * @param platformId Unique ID of the platform
     * @param timeIdx Index of the timestep
     * @return const EcefRadiusVec& Cached ECI position vector
     */
    const EcefRadiusVec& get_position_by_id(std::size_t platformId, std::size_t timeIdx) const;

    /**
     * @brief Get position by platform index and time index (faster)
     *
     * @param platformIdx Index of the platform in the cache
     * @param timeIdx Index of the timestep
     * @return const EcefRadiusVec& Cached ECI position vector
     */
    const EcefRadiusVec& get_position_by_index(std::size_t platformIdx, std::size_t timeIdx) const;

    /**
     * @brief Convert platform ID to internal index
     *
     * @param platformId Unique ID of the platform
     * @return std::size_t Index of the platform in the cache
     */
    std::size_t get_index(std::size_t platformId) const;

    /**
     * @brief Get platform ID from internal index
     *
     * @param platformIdx Index of the platform in the cache
     * @return std::size_t Unique ID of the platform
     */
    std::size_t get_platform_id(std::size_t platformIdx) const;

    /**
     * @brief Get number of platforms
     *
     * @return std::size_t Number of platforms in the cache
     */
    std::size_t n_platforms() const;

    /**
     * @brief Get number of timesteps
     *
     * @return std::size_t Number of timesteps cached per platform
     */
    std::size_t n_timesteps() const;

    /**
     * @brief Clear all data
     */
    void clear();

  private:
    std::vector<std::size_t> _platformIds;                   //!< Platform IDs in order
    std::vector<std::vector<EcefRadiusVec>> _positions;      //!< [platformIdx][timeIdx]
    gtl::flat_hash_map<std::size_t, std::size_t> _idToIndex; //!< Map from platform ID to index
};

} // namespace trace
} // namespace astrea
