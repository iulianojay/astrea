#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
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
    if (trueAnomaly < previousAnomaly) {
        previousAnomaly = trueAnomaly;
        return 0.0 * astrea::detail::unitless; // Triggered
    }
    else {
        previousAnomaly = trueAnomaly;
        return 1.0 * astrea::detail::unitless; // Not triggered
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
    elements += deltaV * elements.get_velocity().unit();

    // Correct to original representation
    state.set_elements(elements, true);
}

bool ImpulsiveBurn::is_terminal() const { return false; }

} // namespace astro
} // namespace astrea