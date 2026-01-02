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

#include <trace/platforms/sensors/fov/instances/PolygonalFieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace trace {

using namespace mp_units;
using namespace mp_units::angular;
using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

PolygonalFieldOfView::PolygonalFieldOfView(const Angle& halfConeAngle, const int& nPoints)
{
    for (Angle theta = 0.0 * astrea::detail::angle_unit; theta < TWO_PI; theta += (TWO_PI / nPoints)) {
        _points[theta] = halfConeAngle;
    }
}

PolygonalFieldOfView::PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints)
{

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*
    const Angle sinw = sin(halfConeWidth);
    const Angle sinh = sin(halfConeHeight);

    for (Angle theta = 0.0; theta < TWO_PI; theta += (TWO_PI/nPoints)) {
        points[theta] = 0.0;
    }
    */
}


bool PolygonalFieldOfView::contains(const EciRadiusVec& boresight, const EciRadiusVec& target) const
{
    // Point in polygon for convex polygons
    static const std::vector<std::pair<Unitless, Unitless>> polygon = build_polygon();

    // Check if the target vector is in the trangle formed by the origin and the two vertices
    // NOTE: The second angle calculated here (atan2) is wrong - it should be calculated from the plane normal to
    //  the boresight vector, not to the ECI x-y plane
    const std::pair<Unitless, Unitless>& point = {
        sin(calculate_angle_between_vectors(boresight, target)) * cos(atan2(target[1], target[0])),
        sin(calculate_angle_between_vectors(boresight, target)) * sin(atan2(target[1], target[0]))
    };

    // Run in polygon test
    return point_in_polygon(point, polygon);
}

std::vector<std::pair<Unitless, Unitless>> PolygonalFieldOfView::build_polygon() const
{
    std::vector<std::pair<Unitless, Unitless>> polygon;
    for (auto it = _points.begin(); it != _points.end(); ++it) {
        // Construct x, y from angles
        const Unitless xVertex1 = sin(it->second) * cos(it->first);
        const Unitless yVertex1 = sin(it->second) * sin(it->first);
        polygon.emplace_back(xVertex1, yVertex1);
    }
    return polygon;
}


bool point_in_polygon(const std::pair<Unitless, Unitless>& point, const std::vector<std::pair<Unitless, Unitless>>& polygon)
{
    // Ray-casting algorithm for point in polygon
    bool inside      = false;
    std::size_t n    = polygon.size();
    const Unitless x = point.first;
    const Unitless y = point.second;
    for (std::size_t ii = 0, jj = n - 1; ii < n; jj = ii++) {
        const Unitless xi = polygon[ii].first;
        const Unitless yi = polygon[ii].second;
        const Unitless xj = polygon[jj].first;
        const Unitless yj = polygon[jj].second;

        // TODO: Is this real or hallucinated?
        if (((yi > y) != (yj > y)) && (x < (xj - xi) * (y - yi) / (yj - yi) + xi)) { inside = !inside; }
    }
    return inside;
}

} // namespace trace
} // namespace astrea