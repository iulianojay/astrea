

# File Sensor.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**Sensor.cpp**](Sensor_8cpp.md)

[Go to the documentation of this file](Sensor_8cpp.md)


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

#include <trace/platforms/sensors/Sensor.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace trace {

bool Sensor::contains(const astro::RadiusVector<astro::frames::earth::icrf>& sensor2target, const astro::Date& date) const
{
    if (!_parameters.get_fov()) { return false; }                        // No FOV means no access
    const astro::frames::dynamic::ric frame(_parent);                    // Convert to RIC frame of parent object
    const astro::RadiusVector<astro::frames::earth::icrf> boresightEci = // Rotate boresight from RIC to ECI frame
        frame.rotate_out_of_this_frame(_parameters.get_boresight(), date); // Don't convert to avoid re-centering of boresight
    return _parameters.get_fov()->contains(boresightEci, sensor2target); // Check if the target is within the FOV
}

} // namespace trace
} // namespace astrea
```


