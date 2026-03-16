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

#include <astro/propagation/event_detection/events/TurnThrustersOff.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>

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
    // First, we need to extract the vehcile as a thrusting thing
    std::shared_ptr<Spacecraft> spacecraftPtr = vehicle.extract_shared_reference<Spacecraft>();
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