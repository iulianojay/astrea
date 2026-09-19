/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/event_detection/events/TurnThrustersOff.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>

using mp_units::si::unit_symbols::km;

namespace astrea {
namespace astro {

TurnThrustersOff::TurnThrustersOff() {}

std::string TurnThrustersOff::get_name() const { return "TurnThrustersOff"; }

Unitless TurnThrustersOff::measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    // This event is only meant to be scheduled
    return 1.0 * mp_units::one;
}

void TurnThrustersOff::trigger_action(const Time& time, State& state, Vehicle& vehicle) const
{
    // WARNING: If you're looking at this as an example, know that this is one of the particularly fragile
    // design points in the library. You need to know which type the vehicle holds for this to work properly
    // (or a type it inherits from). We want to keep the generic, simple interface of the "Vehicle" for users
    // instead of direct subclassing, but that means we have to do some dynamic type checking and extraction
    // to modify the underlying type. You could replace this by replacing the input vehicle with a completely
    // new one but that's a lot of copying.

    // First, we need to extract the vehcile as a thrusting thing
    Spacecraft* spacecraftPtr = vehicle.extract_mutable_reference<Spacecraft>();
    if (spacecraftPtr) {
        for (auto& thruster : spacecraftPtr->get_payloads()) {
            thruster.switch_off();
        }
    }
    else {
        throw std::runtime_error("TurnThrustersOff Event triggered on a Vehicle that is not a Spacecraft.");
    }
}

bool TurnThrustersOff::is_terminal() const { return false; }

} // namespace astro
} // namespace astrea