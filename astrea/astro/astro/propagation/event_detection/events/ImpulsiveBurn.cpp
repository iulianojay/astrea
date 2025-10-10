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
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/orbital_elements.hpp>

namespace astrea {
namespace astro {

std::string ImpulsiveBurn::get_name() const { return "Impulsive Burn"; }

Unitless ImpulsiveBurn::measure_event(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{
    const Keplerian elements = vehicle.get_state().in_element_set<Keplerian>();

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

void ImpulsiveBurn::trigger_action(Vehicle& vehicle) const
{
    // Pull out state
    State& state       = vehicle.get_state();
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