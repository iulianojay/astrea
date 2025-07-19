#include <access/platforms/ground/Grid.hpp>

#include <ranges>

#include <mp-units/math.h>

namespace accesslib {

using astro::Angle;
using astro::Unitless;

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

    const std::size_t nLat = std::ceil((abs(lat4 - lat1) / spacing).numerical_value_in(mp_units::one)) + 1;
    const std::size_t nLon = std::ceil((abs(lon4 - lon1) / spacing).numerical_value_in(mp_units::one)) + 1;

    // Build out linear vector of lats/lons
    std::vector<Angle> lats = create_uniformly_spaced_vector(lat1, lat4, spacing);
    std::vector<Angle> lons = create_uniformly_spaced_vector(lon1, lon4, spacing);

    // Iterate and store
    std::vector<GroundPoint> grounds;
    for (const auto& [lat, lon] : std::views::cartesian_product(lats, lons)) {
        grounds.emplace_back(GroundPoint(lat, lon));
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

std::vector<astro::Angle> Grid::create_uniformly_spaced_vector(const Angle& first, const Angle& second, const Angle& spacing) const
{
    const std::size_t nAngles = std::ceil((abs(second - first) / spacing).numerical_value_in(mp_units::one)) + 1;
    std::vector<Angle> angles(nAngles);
    std::generate(angles.begin(), angles.end(), [ii = 0, minAngle = std::min(first, second), maxAngle = std::max(first, second), &spacing]() mutable {
        return std::min(minAngle + (ii++) * spacing, maxAngle);
    });
    return angles;
}

} // namespace accesslib