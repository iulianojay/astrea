/**
 * @file SpatialIndex.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Spatial partitioning for fast access analysis
 * @date 2026-02-10
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 */
#pragma once

#include <unordered_set>
#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <units/units.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
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
    SpatialIndex(const Angle& binSize = 10.0 * mp_units::angular::unit_symbols::deg) :
        _binSize(binSize)
    {
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::deg;
        using namespace mp_units;

        // Calculate nber of bins
        _nLatBins = static_cast<std::size_t>(ceil<one>(Angle(180.0 * deg) / binSize));
        _nLonBins = static_cast<std::size_t>(ceil<one>(Angle(360.0 * deg) / binSize));

        // Create bins
        _bins.resize(_nLatBins * _nLonBins);

        for (std::size_t iLat = 0; iLat < _nLatBins; ++iLat) {
            for (std::size_t iLon = 0; iLon < _nLonBins; ++iLon) {
                const std::size_t binIdx = iLat * _nLonBins + iLon;

                _bins[binIdx].latMin = -90.0 * deg + iLat * binSize;
                _bins[binIdx].latMax = _bins[binIdx].latMin + binSize;
                _bins[binIdx].lonMin = -180.0 * deg + iLon * binSize;
                _bins[binIdx].lonMax = _bins[binIdx].lonMin + binSize;
            }
        }
    }

    /**
     * @brief Add a ground point to the index
     */
    void add_ground_point(std::size_t groundPointIdx, const Angle& lat, const Angle& lon)
    {
        const std::size_t binIdx = get_bin_index(lat, lon);
        _bins[binIdx].groundPointIndices.push_back(groundPointIdx);
    }

    /**
     * @brief Get ground points within a radius of a lat/lon position
     *
     * @param lat Latitude of center point
     * @param lon Longitude of center point
     * @param radius Angular radius to search
     * @return Set of ground point indices within radius
     */
    std::unordered_set<std::size_t> get_nearby_ground_points(const Angle& lat, const Angle& lon, const Angle& radius) const
    {
        using namespace mp_units;

        std::unordered_set<std::size_t> result;

        // Determine which bins to check based on radius
        const std::size_t centerLatBin = get_lat_bin_index(lat);
        const std::size_t centerLonBin = get_lon_bin_index(lon);

        // Calculate bin radius (how many bins away to check)
        const std::size_t binRadius = static_cast<std::size_t>(ceil<one>(radius / _binSize)) + 1;

        // Check all bins within radius
        for (std::size_t iLat = 0; iLat < _nLatBins; ++iLat) {
            if (abs(static_cast<int>(iLat) - static_cast<int>(centerLatBin)) > static_cast<int>(binRadius)) {
                continue; // Skip bins too far away
            }

            for (std::size_t iLon = 0; iLon < _nLonBins; ++iLon) {
                if (abs(static_cast<int>(iLon) - static_cast<int>(centerLonBin)) > static_cast<int>(binRadius)) {
                    continue; // Skip bins too far away
                }

                const std::size_t binIdx = iLat * _nLonBins + iLon;
                const auto& bin          = _bins[binIdx];

                // Add all ground points in this bin
                for (const auto& gpIdx : bin.groundPointIndices) {
                    result.insert(gpIdx);
                }
            }
        }

        return result;
    }

    /**
     * @brief Get all ground point indices
     */
    std::vector<std::size_t> get_all_ground_points() const
    {
        std::unordered_set<std::size_t> uniquePoints;
        for (const auto& bin : _bins) {
            for (const auto& idx : bin.groundPointIndices) {
                uniquePoints.insert(idx);
            }
        }
        return std::vector<std::size_t>(uniquePoints.begin(), uniquePoints.end());
    }

    /**
     * @brief Clear all ground points from the index
     */
    void clear()
    {
        for (auto& bin : _bins) {
            bin.groundPointIndices.clear();
        }
    }

  private:
    Angle _binSize;
    std::size_t _nLatBins;
    std::size_t _nLonBins;
    std::vector<GeographicBin> _bins;

    std::size_t get_lat_bin_index(const Angle& lat) const
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;
        std::size_t idx = static_cast<std::size_t>((Angle(lat + 90.0 * deg) / _binSize).numerical_value_in(one));
        return std::min(idx, _nLatBins - 1);
    }

    std::size_t get_lon_bin_index(const Angle& lon) const
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;
        std::size_t idx = static_cast<std::size_t>((Angle(lon + 180.0 * deg) / _binSize).numerical_value_in(one));
        return std::min(idx, _nLonBins - 1);
    }

    std::size_t get_bin_index(const Angle& lat, const Angle& lon) const
    {
        return get_lat_bin_index(lat) * _nLonBins + get_lon_bin_index(lon);
    }
};

} // namespace trace
} // namespace astrea
