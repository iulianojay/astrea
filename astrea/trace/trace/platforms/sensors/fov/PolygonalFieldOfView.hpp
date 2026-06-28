/**
 * @file FieldOfView.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Field of View (FoV) classes for representing different types of sensor fields of view.
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

#include <numbers>
#include <vector>

#include <gtl/phmap.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/fov/FieldOfView.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Polygonal field of view implementation.
 *
 * This class represents a polygonal field of view defined by a set of points.
 */
class PolygonalFieldOfView : public FieldOfView {
  public:
    /**
     * @brief Constructor for PolygonalFieldOfView.
     *
     * @param halfConeAngle The half-cone angle defining the field of view.
     * @param nPoints The number of points defining the polygon.
     */
    PolygonalFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad, const int& nPoints = 72);

    /**
     * @brief Constructor for PolygonalFieldOfView with specified half-cone width and height.
     *
     * @param halfConeWidth The half-cone width angle.
     * @param halfConeHeight The half-cone height angle.
     * @param nPoints The number of points defining the polygon.
     */
    PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints = 72);

    /**
     * @brief Constructor for PolygonalFieldOfView with a set of points.
     *
     * @param points A map of angles defining the polygonal field of view.
     */
    PolygonalFieldOfView(const gtl::flat_hash_map<Angle, Angle>& points) :
        _points(points)
    {
        find_min_and_max_angles();
    }

    /**
     * @brief Default destructor for PolygonalFieldOfView.
     */
    ~PolygonalFieldOfView() = default;

    /**
     * @brief Checks if a target is within the polygonal field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the polygonal field of view.
     * @return false If the target is outside the polygonal field of view.
     */
    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const;

    Angle max_half_angle() const override { return _maxHalfAngle; }

  private:
    // TODO: These angle are actually defined w.r.t a frame so we need to figure out what that
    // is and how to define it meaningfully.
    // Probably will be some body-fixed frame aligned with the sensor boresight
    // The key angle is the azimuthal angle around the boresight, and the value angle is the
    // off-boresight angle at that azimuth
    gtl::flat_hash_map<Angle, Angle> _points; //!< Map of angles defining the polygonal field of view
    Angle _minHalfAngle = 0.0 * mp_units::angular::unit_symbols::rad; //!< Minimum off-boresight half angle
    Angle _maxHalfAngle = std::numeric_limits<Angle>::infinity();     //!< Maximum off-boresight half angle

    /**
     * @brief Finds the minimum and maximum off-boresight angles from _points
     */
    void find_min_and_max_angles();

    /**
     * @brief Builds the polygon from the defined points.
     *
     * @return std::vector<std::pair<Unitless, Unitless>> The constructed polygon as a vector of (x, y) pairs.
     */
    std::vector<std::pair<Unitless, Unitless>> build_polygon() const;
};

bool point_in_polygon(const std::pair<Unitless, Unitless>& point, const std::vector<std::pair<Unitless, Unitless>>& polygon);

} // namespace trace
} // namespace astrea