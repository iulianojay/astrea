/**
 * @file NullVehicle.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null vehicle in the astrea astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/State.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a null vehicle in the astrea astro platform.
 * This class is used as a placeholder for vehicles that do not have a defined state or mass.
 */
class NullVehicle : public FrameReference {

  public:
    /**
     * @brief Constructs a NullVehicle with an initial state and mass.
     *
     * @param state0 The initial state of the vehicle, defaulting to a zero state.
     * @param mass The mass of the vehicle, defaulting to zero kilograms.
     */
    NullVehicle(const State& state0 = State(), const Mass& mass = 0.0 * mp_units::si::unit_symbols::kg);

    /**
     * @brief Clone the NullVehicle object.
     *
     * @return NullVehicle* A pointer to a new NullVehicle object that is a copy of this one.
     */
    NullVehicle* clone() const;

    /**
     * @brief Updates the state of the vehicle.
     *
     * @param state The new state to set for the vehicle.
     */
    void update_state(const State& state);

    /**
     * @brief Gets the current state of the vehicle.
     *
     * @return State& A reference to the current state of the vehicle.
     */
    State& get_state();

    /**
     * @brief Gets the initial state of the vehicle.
     *
     * @return const State& A reference to the initial state of the vehicle.
     */
    const State& get_initial_state() const;

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const;

    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const;

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, EarthCenteredInertial>
     */
    CartesianVector<Distance, EarthCenteredInertial> get_inertial_position(const Date& date) const final;

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return CartesianVector<Velocity, EarthCenteredInertial>
     */
    CartesianVector<Velocity, EarthCenteredInertial> get_inertial_velocity(const Date& date) const final;

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return CartesianVector<Acceleration, EarthCenteredInertial>
     */
    CartesianVector<Acceleration, EarthCenteredInertial> get_inertial_acceleration(const Date& date) const final;

  private:
    State _state0; // Initial state of the vehicle
    State _state;  // Current state of the vehicle
    Mass _mass;    // Mass of the vehicle
};

} // namespace astro
} // namespace astrea