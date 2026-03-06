

# File Mercury.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Mercury**](dir_b1a5af1521642f4d9f72715b19091401.md) **>** [**Mercury.cpp**](Mercury_8cpp.md)

[Go to the documentation of this file](Mercury_8cpp.md)


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

#include <astro/systems/planetary_bodies/Mercury/Mercury.hpp>

#include <map>

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Mercury/MercuryEphemerisTable.hpp>
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionMbFromSsb = get_position_at_impl<MercuryEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionMbFromSsb; // TODO: Add correction for Mercury's position from Mercury barycenter
}

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


