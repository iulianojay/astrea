

# File Neptune.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Neptune**](dir_218149e19931632c0aa773ce91bba6d7.md) **>** [**Neptune.cpp**](Neptune_8cpp.md)

[Go to the documentation of this file](Neptune_8cpp.md)


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

#include <astro/systems/planetary_bodies/Neptune/Neptune.hpp>

#include <map>

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Neptune/NeptuneEphemerisTable.hpp>
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionNbFromSsb = get_position_at_impl<NeptuneEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionNbFromSsb; // TODO: Add correction for Neptune's position from Neptune barycenter
}

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


