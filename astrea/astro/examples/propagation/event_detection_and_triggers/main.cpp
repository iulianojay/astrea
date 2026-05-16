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

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::unit_symbols::h;
using mp_units::non_si::unit_symbols::min;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::kN;
using mp_units::si::unit_symbols::s;

int main()
{
    // Events are functions that allow users to find zero-crossings during propagation. Astrea uses type-erasure to
    // allow users to define their own events while keeping a static internal interface. Events use two main functions,
    // one to measure the event value and look for zero-crossings, and another to trigger a post-event action by
    // modifying the current vehicle or state.

    // Setup initial state
    const auto mu = get_mu<planets::Earth>();

    const Date epoch; // Defaults to J2000
    const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch);

    // Build the vehicle
    Spacecraft sat;
    ThrusterParameters thrusterParams(1.0e2 * kN);
    sat.attach_payload(thrusterParams);
    Vehicle vehicle(sat);

    // Build EoMs
    TwoBody eoms;
    // ForceModel forces; // We could add forces if we wanted
    // KeplerianVop eoms(forces, false);

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eoms);

    bool store    = true;    // Users can choose to store the state history during propagation, or not
    Time propTime = days(1); // A propagation interval relative to the epoch. Intervals
                             // can also be negative for backwards propagation.

    // Currently, Astrea only defines a few built-in events, but users can easily define their own custom events by
    // implementing a user-defined Event. Here, we use the built-in impulsive burn, and set it to trigger at a specific
    // true anomaly. It can also be set to trigger at a specific mean anomaly, altitude, or epoch.
    ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_true_anomaly(0.0 * deg, UnitVector<frames::dynamic::ric>(0.0, 1.0, 0.0));
    Event burnEvent(burn);
    integrator.add_event(burnEvent);

    // Propagate - An arbitrary number of events can be passed to the integrator. The integrator will check for zero-crossings
    // at each step, and trigger the event action when a zero-crossing is found or stop propagation if specified.
    const StateHistory history = integrator.propagate(state0, propTime, vehicle);

    // Track period as a quasi-measure of the burn effect
    std::cout << "Initial State: " << elements << std::endl;
    std::cout << "Initial Period: "
              << mp_units::quantity<min>(TWO_PI * sqrt(pow<3>(elements.get_semimajor()) / mu) / (isq_angle::cotes_angle))
              << std::endl;
    std::cout << "Total Thrust: " << mp_units::quantity<kN>(thrusterParams.get_thrust()) << std::endl;
    std::cout << "Spacecraft Mass: " << sat.get_mass() << std::endl;
    std::cout << "Thruster Burn Time: " << mp_units::quantity<s>(1.0 * s) << std::endl;
    const Thruster thruster = sat.get_payloads()[0];
    std::cout << "Equivalent Impulsive Delta-V: " << thruster.get_impulsive_delta_v() << std::endl << std::endl;

    // Events are stored in the state history
    const auto eventTimes = history.get_event_times();
    for (const auto& [eventName, dates] : eventTimes) {
        std::cout << eventName << " Trigger Dates: " << std::endl;
        for (const Date& date : dates) {
            std::cout << "\t" << date << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Period After Each Burn:" << std::endl;
    for (const auto& [eventName, dates] : eventTimes) {
        for (const Date& date : dates) {
            const Keplerian elementsAfterBurn = history.get_state_at(date + 60.0 * s).in_element_set<Keplerian>();
            mp_units::quantity<min> orbitalPeriod =
                TWO_PI * sqrt(pow<3>(elementsAfterBurn.get_semimajor()) / mu) / (isq_angle::cotes_angle);
            std::cout << "\t" << orbitalPeriod << std::endl;
        }
    }

    return 0;
}