/**
 * @file SpatialIndex.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for spatial indexing functions in the astrea trace library.
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

#include <unordered_set>
#include <vector>

#include <units/units.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Geographic bin for spatial partitioning
 */
struct GeographicBin {
    Angle latMin, latMax;
    Angle lonMin, lonMax;
    std::vector<std::size_t> groundPointIndices;

    bool contains(const Angle& lat, const Angle& lon) const
    {
        return lat >= latMin && lat <= latMax && lon >= lonMin && lon <= lonMax;
    }
};

/**
 * @brief Spatial index for efficient ground point queries
 *
 * Divides the Earth's surface into geographic bins to quickly find
 * which ground points are near a satellite's subsatellite point
 */
class SpatialIndex {
  public:
    /**
     * @brief Construct spatial index with specified bin size
     *
     * @param binSize Angular size of each bin (smaller = more bins, finer resolution)
     */
    SpatialIndex(const Angle& binSize = 10.0 * mp_units::si::unit_symbols::deg);

    SpatialIndex(const GroundPointRefVec& groundPoints);

    /**
     * @brief Add a ground point to the index
     *
     * @param groundPointIdx Index of the ground point being added (used for lookup)
     * @param lat Latitude of the ground point
     * @param lon Longitude of the ground point
     */
    void add_ground_point(std::size_t groundPointIdx, const Angle& lat, const Angle& lon);

    /**
     * @brief Get ground points within a radius of a lat/lon position
     *
     * @param lat Latitude of center point
     * @param lon Longitude of center point
     * @param radius Angular radius to search
     * @return Set of ground point indices within radius
     */
    std::unordered_set<std::size_t> get_nearby_ground_points(const Angle& lat, const Angle& lon, const Angle& radius) const;

    /**
     * @brief Get all ground point indices
     *
     * @return std::vector<std::size_t> Vector of all ground point indices in the index
     */
    std::vector<std::size_t> get_all_ground_points() const;

    /**
     * @brief Clear all ground points from the index
     */
    void clear();

  private:
    Angle _binSize;
    std::size_t _nLatBins;
    std::size_t _nLonBins;
    std::vector<GeographicBin> _bins;

    /**
     * @brief Get latitude bin index for a given latitude
     *
     * @param lat Latitude angle
     * @return std::size_t Index of the latitude bin
     */
    std::size_t get_lat_bin_index(const Angle& lat) const;

    /**
     * @brief Get longitude bin index for a given longitude
     *
     * @param lon Longitude angle
     * @return std::size_t Index of the longitude bin
     */
    std::size_t get_lon_bin_index(const Angle& lon) const;

    /**
     * @brief Get overall bin index for given latitude and longitude
     *
     * @param lat Latitude angle
     * @param lon Longitude angle
     * @return std::size_t Overall index of the geographic bin
     */
    std::size_t get_bin_index(const Angle& lat, const Angle& lon) const;
};

} // namespace trace
} // namespace astrea
