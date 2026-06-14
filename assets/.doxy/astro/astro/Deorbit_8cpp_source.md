

# File Deorbit.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**events**](dir_ffe0d0558a41319d577ebe8d35f3c9da.md) **>** [**Deorbit.cpp**](Deorbit_8cpp.md)

[Go to the documentation of this file](Deorbit_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/event_detection/events/Deorbit.hpp>

#include <astro/frames/definitions/frame_registry.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>

using mp_units::si::unit_symbols::km;

namespace astrea {
namespace astro {

Deorbit::Deorbit(const Distance& triggerAltitude) :
    _triggerAltitude(triggerAltitude)
{
}

std::string Deorbit::get_name() const { return "Deorbit"; }

Unitless Deorbit::measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    const Cartesian<frames::primary> elements = state.in_element_set<Cartesian<frames::primary>>();

    const Distance altitude = Geodetic<frames::primary.origin>(elements.get_position(), state.get_epoch()).get_altitude();

    if (_triggerAltitude != 0.0 * km) { return (altitude - _triggerAltitude) / (1.0 * km); }
    return (altitude - get_crash_radius<frames::primary.origin>()) / (1.0 * km);
}

bool Deorbit::is_terminal() const { return true; }

} // namespace astro
} // namespace astrea
```


