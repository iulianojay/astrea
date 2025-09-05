/**
 * @file ImpulsiveBurn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null Event in the astrea astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <mp-units/core.h>

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a null Event in the astrea astro platform.
 * This class is used as a placeholder for Events that do not have a defined state or mass.
 */
class ImpulsiveBurn {

  public:
    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const { return "Impulsive Burn"; }

    /**
     * @brief Measures the anomaly as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
    {
        const auto& sys          = vehicle.get_state().get_system(); // This way of getting the system is stupid
        const Keplerian elements = state.in_element_set<Keplerian>(sys);

        // TODO: Generalize to some scheduler
        const Angle& trueAnomaly = elements.get_true_anomaly();

        // Trigger at perigee
        if (trueAnomaly < previousAnomaly) {
            previousAnomaly = trueAnomaly;
            return 0.0 * detail::unitless; // Triggered
        }
        else {
            previousAnomaly = trueAnomaly;
            return 1.0 * detail::unitless; // Not triggered
        }
    }

    /**
     * @brief Triggers the impulsive burn.
     *
     * @param vehicle The Vehicle to trigger the action on.
     */
    void trigger_action(Vehicle& vehicle) const
    {
        State& state       = vehicle.get_state();
        const auto& sys    = state.get_system();
        Cartesian elements = state.in_element_set<Cartesian>(sys);

        // Just sum up all thrust
        Velocity deltaV = 0.0 * mp_units::si::unit_symbols::N;
        for (const auto& thruster : vehicle.get_payloads<Thruster>()) {
            deltaV += thruster->get_impulsive_delta_v();
        }

        // Apply burn- assume velocity direction
        elements += deltaV * elements.get_velocity().unit(); // TODO: Should adding vectors like this be generalized to other element sets?

        // Correct to original representation
        state.set_elements(elements, true);
    }

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const { return false; }

  private:
    mutable Angle previousAnomaly;
};

} // namespace astro
} // namespace astrea