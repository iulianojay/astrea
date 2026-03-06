

# File FrameReference.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**FrameReference.cpp**](FrameReference_8cpp.md)

[Go to the documentation of this file](FrameReference_8cpp.md)


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

#include <astro/frames/FrameReference.hpp>

#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <astro/frames/CartesianVector.hpp>


namespace astrea {
namespace astro {


AccelerationVector<frames::earth::icrf> FrameReference::get_inertial_acceleration(const Date& date) const
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;
    return AccelerationVector<frames::earth::icrf>{ 0.0 * km / s / s, 0.0 * km / s / s, 0.0 * km / s / s };
};


} // namespace astro
} // namespace astrea
```


