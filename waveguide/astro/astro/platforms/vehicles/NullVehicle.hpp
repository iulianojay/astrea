/**
 * @file NullVehicle.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null vehicle in the waveguide astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief A class representing a null vehicle in the waveguide astro platform.
 * This class is used as a placeholder for vehicles that do not have a defined state or mass.
 */
class NullVehicle {

  public:
    /**
     * @brief Constructs a NullVehicle with an initial state and mass.
     *
     * @param state0 The initial state of the vehicle, defaulting to a zero state.
     * @param mass The mass of the vehicle, defaulting to zero kilograms.
     */
    NullVehicle(const State& state0 = State(), const Mass& mass = 0.0 * mp_units::si::unit_symbols::kg) :
        _state0(state0),
        _state(state0),
        _mass(mass)
    {
    }

    /**
     * @brief Updates the state of the vehicle.
     *
     * @param state The new state to set for the vehicle.
     */
    void update_state(const State& state) { _state = state; }

    /**
     * @brief Gets the current state of the vehicle.
     *
     * @return State& A reference to the current state of the vehicle.
     */
    State& get_state() { return _state; }

    /**
     * @brief Gets the initial state of the vehicle.
     *
     * @return const State& A reference to the initial state of the vehicle.
     */
    const State& get_initial_state() const { return _state0; }

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const { return _mass; }

  private:
    State _state0; // Initial state of the vehicle
    State _state;  // Current state of the vehicle
    Mass _mass;    // Mass of the vehicle
};

} // namespace astro
} // namespace waveguide