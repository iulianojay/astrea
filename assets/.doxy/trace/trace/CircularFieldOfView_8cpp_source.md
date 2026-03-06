

# File CircularFieldOfView.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**fov**](dir_303a66b90134ad3dff734d202c421315.md) **>** [**instances**](dir_16a2422c641898ec244ea09da3a664c2.md) **>** [**CircularFieldOfView.cpp**](CircularFieldOfView_8cpp.md)

[Go to the documentation of this file](CircularFieldOfView_8cpp.md)


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

#include <trace/platforms/sensors/fov/instances/CircularFieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace trace {

using namespace mp_units;
using namespace mp_units::angular;
using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

bool CircularFieldOfView::contains(const EciRadiusVec& boresight, const EciRadiusVec& target) const
{
    return (calculate_angle_between_vectors(boresight, target) <= _halfConeAngle);
}

} // namespace trace
} // namespace astrea
```


