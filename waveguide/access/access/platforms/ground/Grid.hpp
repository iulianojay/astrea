/**
 * @file Grid.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Grid class for managing a grid of ground points.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <access/platforms/ground/GroundPoint.hpp>
#include <access/types/typedefs.hpp>

namespace waveguide {
namespace accesslib {

/**
 * @brief Enumeration for different grid types.
 */
enum class GridType : EnumType {
    UNIFORM,     //<! Uniform grid with equal spacing
    EQUAL_AREA,  //<! Equal area grid with varying spacing
    WEIGHTED_NS, //<! Weighted grid with North-South emphasis
    WEIGHTED_EW, //<! Weighted grid with East-West emphasis
    MANUAL       //<! Manual grid with user-defined points
};

/**
 * @brief Latitude/Longitude coordinate pair.
 *
 * This type is used to represent a geographic location on the Earth's surface.
 */
using LatLon = std::pair<Angle, Angle>;

/**
 * @brief Class representing a grid of ground points.
 *
 * The Grid class manages a collection of ground points, allowing for various grid configurations
 * such as uniform, equal area, and weighted grids. It provides methods to iterate over the ground
 * stations and access their properties.
 */
class Grid {
  public:
    /**
     * @brief Construct a Grid with a vector of ground stations.
     *
     * @param groundStations Vector of GroundPoint objects representing the grid.
     */
    Grid(const std::vector<GroundPoint>& groundStations) :
        _groundStations(groundStations),
        _gridType(GridType::MANUAL)
    {
    }

    /**
     * @brief Construct a Grid with specified corner points and grid type.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param gridType Type of grid to create (uniform, equal area, etc.).
     * @param spacing Spacing between points in the grid (default is 5 degrees).
     * @param weight Weighting factor for the grid (default is 0).
     */
    Grid(
        const LatLon& corner1,
        const LatLon& corner4,
        const GridType& gridType,
        const Angle& spacing   = 5.0 * mp_units::angular::unit_symbols::deg,
        const Unitless& weight = 0.0 * mp_units::one
    ) :
        _groundStations(build_grid(corner1, corner4, gridType, spacing, weight)),
        _gridType(gridType)
    {
    }

    /**
     * @brief Default destructor for the Grid class.
     */
    virtual ~Grid() = default;

    /**
     * @brief Iterator types for the Grid class.
     */
    using iterator = std::vector<GroundPoint>::iterator;

    /**
     * @brief Constant iterator types for the Grid class.
     */
    using const_iterator = std::vector<GroundPoint>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the ground points in the grid.
     *
     * @return An iterator to the first ground point.
     */
    iterator begin() { return _groundStations.begin(); }

    /**
     * @brief Returns an iterator to the end of the ground points in the grid.
     *
     * @return An iterator to one past the last ground point.
     */
    iterator end() { return _groundStations.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground points in the grid.
     *
     * @return A constant iterator to the first ground point.
     */
    const_iterator begin() const { return _groundStations.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground points in the grid.
     *
     * @return A constant iterator to one past the last ground point.
     */
    const_iterator end() const { return _groundStations.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground points in the grid.
     *
     * @return A constant iterator to the first ground point.
     */
    const_iterator cbegin() const { return _groundStations.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground points in the grid.
     *
     * @return A constant iterator to one past the last ground point.
     */
    const_iterator cend() const { return _groundStations.end(); }

  private:
    std::vector<GroundPoint> _groundStations; //!< Vector of ground points in the grid
    GridType _gridType;                       //!< Type of grid (uniform, equal area, etc.)

    /**
     * @brief Builds a grid of ground points based on the specified parameters.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param gridType Type of grid to create (uniform, equal area, etc.).
     * @param spacing Spacing between points in the grid.
     * @param weight Weighting factor for the grid.
     * @return A vector of GroundPoint objects representing the grid.
     */
    std::vector<GroundPoint>
        build_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& spacing, const Unitless& weight) const;

    /**
     * @brief Builds a grid of ground points based on the specified corner points and spacing.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param spacing Spacing between points in the grid.
     * @return std::vector<GroundPoint> A vector of GroundPoint objects representing the grid.
     */
    std::vector<GroundPoint> build_uniform_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const;

    /**
     * @brief Builds an equal area grid of ground points based on the specified corner points and spacing.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param spacing Spacing between points in the grid.
     * @return std::vector<GroundPoint> A vector of GroundPoint objects representing the equal area grid.
     */
    std::vector<GroundPoint> build_equal_area_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const;

    /**
     * @brief Builds a weighted grid of ground points based on the specified corner points, grid type, spacing, and weight.
     *
     * @param corner1 First corner point of the grid (latitude, longitude).
     * @param corner4 Fourth corner point of the grid (latitude, longitude).
     * @param gridType Type of weighted grid to create (North-South or East-West emphasis).
     * @param spacing Spacing between points in the grid.
     * @param weight Weighting factor for the grid.
     * @return std::vector<GroundPoint> A vector of GroundPoint objects representing the weighted grid.
     */
    std::vector<GroundPoint>
        build_weighted_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& initialSpacing, const Unitless& weight) const;

    /**
     * @brief Creates a uniformly spaced vector of angles between two points.
     *
     * @param first First angle in the vector.
     * @param second Second angle in the vector.
     * @param spacing Spacing between the angles.
     * @return std::vector<Angle> A vector of angles spaced evenly between the first and second angles.
     */
    std::vector<Angle> create_uniformly_spaced_vector(const Angle& first, const Angle& second, const Angle& spacing) const;
};

} // namespace accesslib
} // namespace waveguide