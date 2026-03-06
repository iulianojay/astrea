

# File Grid.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**Grid.cpp**](Grid_8cpp.md)

[Go to the documentation of this file](Grid_8cpp.md)


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

#include <trace/platforms/ground/Grid.hpp>

#include <ranges>

#include <mp-units/math.h>

namespace astrea {
namespace trace {

std::vector<GroundPoint>
    Grid::build_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& spacing, const Unitless& weight) const
{
    switch (gridType) {
        case (GridType::UNIFORM): return build_uniform_grid(corner1, corner4, spacing); break;
        case (GridType::EQUAL_AREA): return build_equal_area_grid(corner1, corner4, spacing); break;
        case (GridType::WEIGHTED_NS):
        case (GridType::WEIGHTED_EW): return build_weighted_grid(corner1, corner4, gridType, spacing, weight); break;
        case (GridType::MANUAL):
            throw std::runtime_error("Manual grids can only be constructed from a vector of GroundPoints.");
        default: throw std::runtime_error("Unrecognized GridType.");
    }
}

std::vector<GroundPoint> Grid::build_uniform_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const
{
    // Setup
    const auto& lat1 = corner1.first;
    const auto& lon1 = corner1.second;
    const auto& lat4 = corner4.first;
    const auto& lon4 = corner4.second;

    // Build out linear vector of lats/lons
    std::vector<Angle> lats = create_uniformly_spaced_vector(lat1, lat4, spacing);
    std::vector<Angle> lons = create_uniformly_spaced_vector(lon1, lon4, spacing);

    // Iterate and store
    std::vector<GroundPoint> grounds;
    for (const auto& [lat, lon] : std::views::cartesian_product(lats, lons)) {
        grounds.emplace_back(GroundPoint(_parent, lat, lon));
    }
    return grounds;
}

std::vector<GroundPoint> Grid::build_equal_area_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const
{
    throw std::runtime_error("Equal area grids have not been implemented yet.");
}

std::vector<GroundPoint>
    Grid::build_weighted_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& spacing, const Unitless& weight) const
{
    throw std::runtime_error("Weighted grids have not been implemented yet.");
}

std::vector<Angle> Grid::create_uniformly_spaced_vector(const Angle& first, const Angle& second, const Angle& spacing) const
{
    const std::size_t nAngles = std::ceil((abs(second - first) / spacing).numerical_value_in(mp_units::one)) + 1;
    std::vector<Angle> angles(nAngles);
    std::generate(angles.begin(), angles.end(), [ii = 0, minAngle = std::min(first, second), maxAngle = std::max(first, second), &spacing]() mutable {
        return std::min(minAngle + (ii++) * spacing, maxAngle);
    });
    return angles;
}

} // namespace trace
} // namespace astrea
```


