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
#include <trace/analysis/SpatialIndex.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>

#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/angular_elements.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>


using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;

namespace astrea {
namespace trace {

SpatialIndex::SpatialIndex(const Angle& binSize) :
    _binSize(binSize)
{
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

SpatialIndex::SpatialIndex(const GroundPointRefVec& groundPoints) :
    SpatialIndex() // delegate: initialise bins with the default bin size first
{
    for (std::size_t i = 0; i < groundPoints.size(); ++i) {
        add_ground_point(i, groundPoints[i]->get_latitude(), groundPoints[i]->get_longitude());
    }
}

void SpatialIndex::add_ground_point(std::size_t groundPointIdx, const Angle& lat, const Angle& lon)
{
    const std::size_t binIdx = get_bin_index(lat, lon);
    _bins[binIdx].groundPointIndices.push_back(groundPointIdx);
}

std::unordered_set<std::size_t> SpatialIndex::get_nearby_ground_points(const Angle& lat, const Angle& lon, const Angle& radius) const
{
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

std::vector<std::size_t> SpatialIndex::get_all_ground_points() const
{
    std::unordered_set<std::size_t> uniquePoints;
    for (const auto& bin : _bins) {
        for (const auto& idx : bin.groundPointIndices) {
            uniquePoints.insert(idx);
        }
    }
    return std::vector<std::size_t>(uniquePoints.begin(), uniquePoints.end());
}

void SpatialIndex::clear()
{
    for (auto& bin : _bins) {
        bin.groundPointIndices.clear();
    }
}

std::size_t SpatialIndex::get_lat_bin_index(const Angle& lat) const
{
    std::size_t idx = static_cast<std::size_t>((Angle(lat + 90.0 * deg) / _binSize).numerical_value_in(one));
    return std::min(idx, _nLatBins - 1);
}

std::size_t SpatialIndex::get_lon_bin_index(const Angle& lon) const
{
    std::size_t idx = static_cast<std::size_t>((Angle(lon + 180.0 * deg) / _binSize).numerical_value_in(one));
    return std::min(idx, _nLonBins - 1);
}

std::size_t SpatialIndex::get_bin_index(const Angle& lat, const Angle& lon) const
{
    return get_lat_bin_index(lat) * _nLonBins + get_lon_bin_index(lon);
}

} // namespace trace
} // namespace astrea
