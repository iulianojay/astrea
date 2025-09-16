#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::h;
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
    AstrodynamicsSystem sys; // Defaults to Earth-Moon
    const Date epoch;
    const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch, sys);

    // Build the vehicle
    Spacecraft sat(state0);
    ThrusterParameters thrusterParams(1.0e1 * kN);
    sat.attach_payload(thrusterParams);
    Vehicle vehicle(sat);

    // Build EoMs
    ForceModel forces;
    TwoBody eoms(sys);
    // KeplerianVop eoms(sys, forces, false);

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);
    integrator.switch_fixed_timestep(true, 60.0 * s);

    bool store = true; // Users can choose to store the state history during propagation, or not
    Interval propInterval{ seconds(0), days(1) };

    // Currently, Astrea only defines a single event, an ImpulsiveBurn which triggers at perigee crossing and always
    // burns in the velocity direction. The impulsive burn event uses the thrust of all attached thrusters in a simple
    // instantaneous impulse. Future releases will support direct event scheduling, and more event types.
    ImpulsiveBurn burn;
    Event burnEvent(burn);

    // Propagate - An arbitrary number of events can be passed to the integrator. The integrator will check for zero-crossings
    // at each step, and trigger the event action when a zero-crossing is found or stop propagation if specified.
    const StateHistory history = integrator.propagate(epoch, propInterval, eoms, vehicle, store, { burnEvent });

    // Track period as a quasi-measure of the burn effect
    std::cout << "Initial State: " << elements << std::endl;
    std::cout
        << "Initial Period: "
        << mp_units::quantity<h>(TWO_PI * sqrt(pow<3>(elements.get_semimajor()) / sys.get_center()->get_mu()) / (isq_angle::cotes_angle))
        << std::endl;
    std::cout << "Total Thrust: " << mp_units::quantity<kN>(thrusterParams.get_thrust()) << std::endl;
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
            mp_units::quantity<h> orbitalPeriod =
                TWO_PI * sqrt(pow<3>(elementsAfterBurn.get_semimajor()) / sys.get_center()->get_mu()) / (isq_angle::cotes_angle);
            std::cout << "\t" << orbitalPeriod << std::endl;
        }
    }

    return 0;
}