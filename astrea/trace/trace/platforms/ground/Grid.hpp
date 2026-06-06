/**
 * @file Grid.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Grid class for managing a grid of ground points.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

#include <algorithm>
#include <cmath>
#include <ranges>
#include <stdexcept>
#include <vector>

#include <mp-units/math.h>

#include <units/units.hpp>

#include <astro/systems/system_concepts.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/types/enums.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Class representing a grid of ground points on the surface of a celestial body.
 *
 * The Grid class manages a collection of ground points, allowing for various grid configurations
 * such as uniform, equal area, and weighted grids. It provides methods to iterate over the ground
 * stations and access their properties.
 *
 * @tparam _body_ The celestial body NTTP this grid resides on.
 */
template <astro::IsCelestialBody auto _body_>
class Grid {
    using Point = GroundPoint<_body_>;

  public:
    /**
     * @brief Default constructor for the Grid class.
     *
     * Initializes an empty grid with no ground points.
     */
    Grid() = default;

    /**
     * @brief Construct a Grid from an explicit vector of ground points.
     *
     * @param groundPoints Vector of GroundPoint objects representing the grid.
     */
    Grid(const std::vector<Point>& groundPoints) :
        _groundPoints(groundPoints),
        _gridType(GridType::MANUAL)
    {
    }

    /**
     * @brief Construct a Grid from corner points and a grid type.
     *
     * @param corner1  First corner (latitude, longitude).
     * @param corner4  Fourth corner (latitude, longitude).
     * @param gridType Grid generation algorithm.
     * @param spacing  Angular spacing between points (default 5 deg).
     * @param weight   Weighting factor (default 0).
     */
    Grid(
        const LatLon& corner1,
        const LatLon& corner4,
        const GridType& gridType,
        const Angle& spacing   = 5.0 * mp_units::angular::unit_symbols::deg,
        const Unitless& weight = 0.0 * mp_units::one
    ) :
        _groundPoints(build_grid(corner1, corner4, gridType, spacing, weight)),
        _gridType(gridType)
    {
    }

    /**
     * @brief Default destructor for the Grid class.
     */
    virtual ~Grid() = default;

    /**
     * @brief Get the type of grid.
     *
     * @return GridType The type of grid (uniform, equal area, etc.).
     */
    GridType get_grid_type() const { return _gridType; }

    /**
     * @brief Get the number of ground points in the grid.
     *
     * @return std::size_t The number of ground points in the grid.
     */
    std::size_t size() const { return _groundPoints.size(); }

    /**
     * @brief Iterator type for the Grid class.
     */
    using iterator = typename std::vector<Point>::iterator;

    /**
     * @brief Constant iterator type for the Grid class.
     */
    using const_iterator = typename std::vector<Point>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the ground points in the grid.
     *
     * @return An iterator to the first ground point.
     */
    iterator begin() { return _groundPoints.begin(); }

    /**
     * @brief Returns an iterator to the end of the ground points in the grid.
     *
     * @return An iterator to one past the last ground point.
     */
    iterator end() { return _groundPoints.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground points in the grid.
     *
     * @return A constant iterator to the first ground point.
     */
    const_iterator begin() const { return _groundPoints.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground points in the grid.
     *
     * @return A constant iterator to one past the last ground point.
     */
    const_iterator end() const { return _groundPoints.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground points in the grid.
     *
     * @return A constant iterator to the first ground point.
     */
    const_iterator cbegin() const { return _groundPoints.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground points in the grid.
     *
     * @return A constant iterator to one past the last ground point.
     */
    const_iterator cend() const { return _groundPoints.end(); }

    /**
     * @brief Access a ground point in the grid by index.
     *
     * @param index Index of the ground point to access.
     * @return Reference to the Point at the specified index.
     */
    Point& operator[](std::size_t index) { return _groundPoints[index]; }

    /**
     * @brief Access a ground point in the grid by index (constant version).
     *
     * @param index Index of the ground point to access.
     * @return Constant reference to the Point at the specified index.
     */
    const Point& operator[](std::size_t index) const { return _groundPoints[index]; }

  private:
    std::vector<Point> _groundPoints; //!< Vector of ground points in the grid.
    GridType _gridType{};             //!< Type of grid (uniform, equal area, etc.).

    /**
     * @brief Builds a grid of ground points based on the specified parameters.
     *
     * @param corner1  First corner point of the grid (latitude, longitude).
     * @param corner4  Fourth corner point of the grid (latitude, longitude).
     * @param gridType Type of grid to create (uniform, equal area, etc.).
     * @param spacing  Spacing between points in the grid.
     * @param weight   Weighting factor for the grid.
     * @return A vector of Point objects representing the grid.
     */
    std::vector<Point>
        build_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& spacing, const Unitless& weight) const
    {
        switch (gridType) {
            case GridType::UNIFORM: return build_uniform_grid(corner1, corner4, spacing);
            case GridType::EQUAL_AREA: return build_equal_area_grid(corner1, corner4, spacing);
            case GridType::WEIGHTED_NS:
            case GridType::WEIGHTED_EW: return build_weighted_grid(corner1, corner4, gridType, spacing, weight);
            case GridType::MANUAL:
                throw std::runtime_error("Manual grids can only be constructed from a vector of GroundPoints.");
            default: throw std::runtime_error("Unrecognized GridType.");
        }
    }

    /**
     * @brief Builds a uniform grid of ground points.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param spacing Spacing between points in the grid.
     * @return std::vector<Point> A vector of Point objects representing the uniform grid.
     */
    std::vector<Point> build_uniform_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const
    {
        const auto& lat1 = corner1.first;
        const auto& lon1 = corner1.second;
        const auto& lat4 = corner4.first;
        const auto& lon4 = corner4.second;

        std::vector<Angle> lats = create_uniformly_spaced_vector(lat1, lat4, spacing);
        std::vector<Angle> lons = create_uniformly_spaced_vector(lon1, lon4, spacing);

        std::vector<Point> grounds;
        for (const auto& [lat, lon] : std::views::cartesian_product(lats, lons)) {
            grounds.emplace_back(lat, lon);
        }
        return grounds;
    }

    /**
     * @brief Builds an equal area grid of ground points based on the specified corner points and spacing.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param spacing Spacing between points in the grid.
     * @return std::vector<Point> A vector of ground points representing the equal area grid.
     */
    std::vector<Point> build_equal_area_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const
    {
        throw std::runtime_error("Equal area grids have not been implemented yet.");
    }

    /**
     * @brief Builds a weighted grid of ground points.
     *
     * @param corner1       First corner point of the grid (latitude, longitude).
     * @param corner4       Fourth corner point of the grid (latitude, longitude).
     * @param gridType      Type of weighted grid to create (North-South or East-West emphasis).
     * @param initialSpacing Spacing between points in the grid.
     * @param weight        Weighting factor for the grid.
     * @return std::vector<Point> A vector of Point objects representing the weighted grid.
     */
    std::vector<Point>
        build_weighted_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& initialSpacing, const Unitless& weight) const
    {
        throw std::runtime_error("Weighted grids have not been implemented yet.");
    }

    /**
     * @brief Creates a uniformly spaced vector of angles between two points.
     *
     * @param first   First angle in the vector.
     * @param second  Second angle in the vector.
     * @param spacing Spacing between the angles.
     * @return std::vector<Angle> A vector of angles spaced evenly between first and second.
     */
    std::vector<Angle> create_uniformly_spaced_vector(const Angle& first, const Angle& second, const Angle& spacing) const
    {
        const std::size_t nAngles = std::ceil((mp_units::abs(second - first) / spacing).numerical_value_in(mp_units::one)) + 1;
        std::vector<Angle> angles(nAngles);
        std::generate(angles.begin(), angles.end(), [ii = 0, minAngle = std::min(first, second), maxAngle = std::max(first, second), &spacing]() mutable {
            return std::min(minAngle + (ii++) * spacing, maxAngle);
        });
        return angles;
    }
};

} // namespace trace
} // namespace astrea