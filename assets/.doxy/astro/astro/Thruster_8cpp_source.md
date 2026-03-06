

# File Thruster.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**thrusters**](dir_c4651317ac77989e0950f932d02daf86.md) **>** [**Thruster.cpp**](Thruster_8cpp.md)

[Go to the documentation of this file](Thruster_8cpp.md)


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

#include <astro/platforms/thrusters/Thruster.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::s;

std::size_t Thruster::get_id() const { return _id; }

Velocity Thruster::get_impulsive_delta_v() const
{
    return get_parameters().get_thrust() / get_parent()->get_mass() * s;
}

std::size_t Thruster::generate_id() const
{
    static std::size_t idCounter = 0;
    return idCounter++;
}

} // namespace astro
} // namespace astrea
```


