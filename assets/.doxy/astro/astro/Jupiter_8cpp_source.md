

# File Jupiter.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md) **>** [**Jupiter.cpp**](Jupiter_8cpp.md)

[Go to the documentation of this file](Jupiter_8cpp.md)


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

#include <astro/systems/planetary_bodies/Jupiter/Jupiter.hpp>

#include <map>

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Jupiter/JupiterEphemerisTable.hpp>
#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionJbFromSsb = get_position_at_impl<JupiterEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionJbFromSsb; // TODO: Add correction for Jupiter's position from Jupiter barycenter
}

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


