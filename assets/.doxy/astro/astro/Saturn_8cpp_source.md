

# File Saturn.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Saturn**](dir_a10a33e87be611798e598d7dfa84b38d.md) **>** [**Saturn.cpp**](Saturn_8cpp.md)

[Go to the documentation of this file](Saturn_8cpp.md)


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

#include <astro/systems/planetary_bodies/Saturn/Saturn.hpp>

#include <map>

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Saturn/SaturnEphemerisTable.hpp>
#endif // ASTREA_BUILD_SATURN_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionSbFromSsb = get_position_at_impl<SaturnEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionSbFromSsb; // TODO: Add correction for Saturn's position from Saturn barycenter
}

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


