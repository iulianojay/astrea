

# File ImpulsiveBurn.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**events**](dir_ffe0d0558a41319d577ebe8d35f3c9da.md) **>** [**ImpulsiveBurn.cpp**](ImpulsiveBurn_8cpp.md)

[Go to the documentation of this file](ImpulsiveBurn_8cpp.md)


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

#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>

namespace astrea {
namespace astro {

std::string ImpulsiveBurn::get_name() const { return "Impulsive Burn"; }

Unitless ImpulsiveBurn::measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    const Keplerian elements = state.in_element_set<Keplerian>();

    // TODO: Generalize to some scheduler
    const Angle& trueAnomaly = elements.get_true_anomaly();

    // Trigger at perigee
    // We don't track absolute anomaly so just check if it wrapped around
    const Unitless deltaAnomaly = (trueAnomaly - previousAnomaly) / (astrea::detail::angle_unit);
    previousAnomaly             = trueAnomaly;

    if (deltaAnomaly < 0.0 * mp_units::one) { return 0.0 * mp_units::one; } // event
    else {
        return 1.0 * mp_units::one; // No event
    }
}

void ImpulsiveBurn::trigger_action(const Time& time, State& state, Vehicle& vehicle) const
{
    // Pull out state
    Cartesian elements = state.in_element_set<Cartesian>();

    // Just sum up all the thrusters
    const Spacecraft* sat = vehicle.extract<Spacecraft>();
    Velocity deltaV       = 0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s;
    for (const auto& thruster : sat->get_payloads()) {
        deltaV += thruster.get_impulsive_delta_v();
    }

    // Apply burn, assume velocity direction
    // TODO: Should adding vectors like this be generalized to other element sets?
    //  Then we wouldn't need to convert to Cartesian first
    const auto dv = deltaV * elements.get_velocity().unit();
    elements += dv;

    // Correct to original representation
    state.set_elements(elements, true);
}

bool ImpulsiveBurn::is_terminal() const { return false; }

} // namespace astro
} // namespace astrea
```


