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

#include <trace/platforms/sensors/fov/CircularFieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>

namespace astrea {
namespace trace {

using namespace mp_units;
using namespace mp_units::si;
using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

CircularFieldOfView::CircularFieldOfView(const Angle& halfConeAngle) :
    _halfConeAngle(halfConeAngle),
    _cosHalfConeAngle(cos(halfConeAngle))
{
}

bool CircularFieldOfView::contains(const EciRadiusVec& boresight, const EciRadiusVec& target) const
{
    // Replace acos(dot/(|b||t|)) <= θ with the equivalent dot(b̂,t̂) >= cos(θ),
    // using the pre-computed _cosHalfConeAngle to eliminate the inverse-trig call.
    const Distance bMag = boresight.norm();
    const Distance tMag = target.norm();
    const auto ratio    = boresight.dot(target) / (bMag * tMag);
    return ratio >= _cosHalfConeAngle;
}

} // namespace trace
} // namespace astrea