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

#include <trace/platforms/sensors/fov/FieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>

namespace astrea {
namespace trace {

using namespace mp_units;
using namespace mp_units::angular;
using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

Angle calculate_angle_between_vectors(const EciRadiusVec& vector1, const EciRadiusVec& vector2)
{
    const Distance v1Mag = vector1.norm();
    const Distance v2Mag = vector2.norm();
    const auto v1DotV2   = vector1.dot(vector2);
    const auto ratio     = v1DotV2 / (v1Mag * v2Mag);
    if (ratio > 1.0 * one) {
        return 0.0 * astrea::detail::angle_unit;
    } // catch rounding errors - TODO: Make this more intelligent
    return acos(ratio);
}

} // namespace trace
} // namespace astrea