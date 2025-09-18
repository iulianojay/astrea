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
    const Keplerian elements = vehicle.get_state().in_orbital_set<Keplerian>();

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
    Cartesian elements = state.in_orbital_set<Cartesian>();

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