

# File CircularFieldOfView.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**fov**](dir_303a66b90134ad3dff734d202c421315.md) **>** [**CircularFieldOfView.cpp**](CircularFieldOfView_8cpp.md)

[Go to the documentation of this file](CircularFieldOfView_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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
```


