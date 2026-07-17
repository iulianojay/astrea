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

#include <mp-units/systems/angular.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

std::string ImpulsiveBurn::get_name() const { return "Impulsive Burn"; }

Unitless ImpulsiveBurn::measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    switch (_trigger) {
        case BurnTrigger::TRUE_ANOMALY:
        case BurnTrigger::MEAN_ANOMALY: return measure_anomaly_event(time, state, vehicle);
        case BurnTrigger::ALTITUDE: return measure_altitude_event(time, state, vehicle);
        case BurnTrigger::SCHEDULED: return measure_epoch_event(time, state, vehicle);
        default: throw std::runtime_error("Invalid burn trigger type");
    }
}


Unitless ImpulsiveBurn::measure_anomaly_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    const Keplerian<frames::earth::icrf> elements = state.in_element_set<Keplerian<frames::earth::icrf>>();

    const Angle anomaly = (_trigger == BurnTrigger::TRUE_ANOMALY) ? elements.get_true_anomaly() - _triggerAnomaly :
                                                                    elements.get_mean_anomaly() - _triggerAnomaly;

    // Avoid triggering when the angles wrap around 2π
    static Angle previousAnomaly = 0.0 * rad;
    const Unitless deltaAnomaly  = (anomaly - previousAnomaly) / (1.0 * rad);
    previousAnomaly              = anomaly;

    if (deltaAnomaly < 0.0 * mp_units::one) { return 0.0 * mp_units::one; } // event
    else {
        return 1.0 * mp_units::one; // No event
    }
}


Unitless ImpulsiveBurn::measure_altitude_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    const Cartesian<frames::earth::icrf> elements = state.in_element_set<Cartesian<frames::earth::icrf>>();

    const Distance altitude = Geodetic<frames::earth::icrf.origin>(elements.get_position(), state.get_epoch()).get_altitude();

    return (altitude - _triggerAltitude) / (1.0 * km);
}


Unitless ImpulsiveBurn::measure_epoch_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    return (state.get_epoch() - _triggerEpoch) / (1.0 * s);
}


void ImpulsiveBurn::trigger_action(const Time& time, State& state, Vehicle& vehicle) const
{
    // Event is disabled after reaching max triggers, unless max triggers is set to zero (infinite triggers)
    if (_nMaxTriggers > 0) {
        static unsigned nTriggers = 0;
        if (nTriggers >= _nMaxTriggers) { return; }
        ++nTriggers;
    }

    // Pull out state
    Cartesian<frames::earth::icrf> elements = state.in_element_set<Cartesian<frames::earth::icrf>>();

    // Just sum up all the thrusters
    const Spacecraft* sat = vehicle.extract<Spacecraft>();
    Velocity deltaV       = 0.0 * km / s;
    for (const auto& thruster : sat->get_payloads()) {
        deltaV += thruster.get_impulsive_delta_v();
    }

    // Rotate out of RIC
    const auto ricFrame = frames::dynamic::ric.instantaneous(elements.get_position(), elements.get_velocity());
    const Direction<frames::earth::icrf> burnDirection = ricFrame.rotate_out_of_this_frame(_burnDirection, state.get_epoch());

    const auto dv = deltaV * burnDirection;
    elements += dv;

    // Correct to original representation
    state.set_elements(elements, true);
}

bool ImpulsiveBurn::is_terminal() const { return false; }

} // namespace astro
} // namespace astrea