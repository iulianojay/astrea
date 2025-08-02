/**
 * @file Spacecraft.hpp
 * @author your name (you@domain.com)
 * @brief A class representing a spacecraft in the waveguide astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief A class representing a spacecraft in the waveguide astro platform.
 * This class encapsulates the properties and behaviors of a spacecraft, including its state,
 * mass, dynamic coefficients, and surface areas.
 */
class Spacecraft {

  public:
    /**
     * @brief Default constructor for Spacecraft.
     */
    Spacecraft() = default;

    /**
     * @brief Constructs a Spacecraft with an initial state.
     *
     * @param state0 The initial state of the spacecraft.
     */
    Spacecraft(const State& state0) :
        _state(state0),
        _state0(state0)
    {
        generate_id_hash();
    }

    /**
     * @brief Constructs a Spacecraft with a SpaceTrackGP object and an AstrodynamicsSystem.
     *
     * @param gp The SpaceTrackGP object containing initial parameters.
     * @param sys The AstrodynamicsSystem to which this spacecraft belongs.
     */
    Spacecraft(const snapshot::SpaceTrackGP& gp, const AstrodynamicsSystem& sys);

    /**
     * @brief Virtual destructor for Spacecraft.
     */
    virtual ~Spacecraft() = default;

    /**
     * @brief Updates the state of the spacecraft.
     *
     * @param state The new state to set for the spacecraft.
     */
    void update_state(const State& state);

    /**
     * @brief Gets the current state of the spacecraft.
     *
     * @return State& A reference to the current state of the spacecraft.
     */
    State& get_state();

    /**
     * @brief Gets the initial state of the spacecraft.
     *
     * @return const State& A reference to the initial state of the spacecraft.
     */
    const State& get_initial_state() const;

    /**
     * @brief Stores the state history of the spacecraft.
     *
     * @param history The StateHistory object to store.
     */
    void store_state_history(const StateHistory& history);

    /**
     * @brief Gets the state history of the spacecraft.
     *
     * @return StateHistory& A reference to the state history of the spacecraft.
     */
    StateHistory& get_state_history();

    /**
     * @brief Gets the state history of the spacecraft.
     *
     * @return const StateHistory& A reference to the state history of the spacecraft.
     */
    const StateHistory& get_state_history() const;

    /**
     * @brief Gets the mass of the spacecraft.
     *
     * @return Mass The mass of the spacecraft.
     */
    Mass get_mass() const;

    /**
     * @brief Gets the coefficients of drag, lift, and reflectivity.
     *
     * @return Unitless The coefficient of drag.
     */
    Unitless get_coefficient_of_drag() const;

    /**
     * @brief Gets the coefficient of lift.
     *
     * @return Unitless The coefficient of lift.
     */
    Unitless get_coefficient_of_lift() const;

    /**
     * @brief Gets the coefficient of reflectivity.
     *
     * @return Unitless The coefficient of reflectivity.
     */
    Unitless get_coefficient_of_reflectivity() const;

    /**
     * @brief Gets the surface areas for ram, solar, and lift.
     *
     * @return SurfaceArea The ram area of the spacecraft.
     */
    SurfaceArea get_ram_area() const;

    /**
     * @brief Gets the solar area of the spacecraft.
     *
     * @return SurfaceArea The solar area of the spacecraft.
     */
    SurfaceArea get_solar_area() const;

    /**
     * @brief Gets the lift area of the spacecraft.
     *
     * @return SurfaceArea The lift area of the spacecraft.
     */
    SurfaceArea get_lift_area() const;

    /**
     * @brief Gets the unique identifier of the spacecraft.
     *
     * @return std::size_t The unique identifier of the spacecraft.
     */
    std::size_t get_id() const { return _id; }

    /**
     * @brief Gets the name of the spacecraft.
     *
     * @return std::string The name of the spacecraft.
     */
    std::string get_name() const { return _name; }

    /**
     * @brief Sets the mass of the spacecraft.
     *
     * @param mass The new mass to set for the spacecraft.
     */
    void set_mass(const Mass& mass);

    /**
     * @brief Sets the coefficients of drag.
     *
     * @param cd The coefficient of drag to set.
     */
    void set_coefficient_of_drag(const Unitless& cd);

    /**
     * @brief Sets the coefficient of lift.
     *
     * @param cl The coefficient of lift to set.
     */
    void set_coefficient_of_lift(const Unitless& cl);

    /**
     * @brief Sets the coefficient of reflectivity.
     *
     * @param cr The coefficient of reflectivity to set.
     */
    void set_coefficient_of_reflectivity(const Unitless& cr);

    /**
     * @brief Sets the surface area for ram.
     *
     * @param ramArea The ram area to set.
     */
    void set_ram_area(const SurfaceArea& ramArea);

    /**
     * @brief Sets the solar area of the spacecraft.
     *
     * @param solarArea The solar area to set.
     */
    void set_solar_area(const SurfaceArea& solarArea);

    /**
     * @brief Sets the lift area of the spacecraft.
     *
     * @param liftArea The lift area to set.
     */
    void set_lift_area(const SurfaceArea& liftArea);

    /**
     * @brief Sets the name of the spacecraft.
     *
     * @param name The name to set for the spacecraft.
     */
    void set_name(const std::string& name);

  protected:
    std::size_t _id;   // Unique identifier for the spacecraft, generated from its properties
    std::string _name; // Name of the spacecraft, can be set by the user

    // Spacecraft properties
    Mass _mass                          = 1000.0 * mp_units::si::unit_symbols::kg; // Default mass of the spacecraft
    Unitless _coefficientOfDrag         = 2.2 * mp_units::one;                     // Default coefficient of drag
    Unitless _coefficientOfLift         = 0.9 * mp_units::one;                     // Default coefficient of lift
    Unitless _coefficientOfReflectivity = 1.1 * mp_units::one; // Default coefficient of reflectivity
    SurfaceArea _ramArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m); // Default ram area
    SurfaceArea _sunArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m); // Default solar area
    SurfaceArea _liftArea               = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m); // Default lift area

    // Orbital elements
    State _state0;              // Initial state of the spacecraft
    State _state;               // Current state of the spacecraft
    StateHistory _stateHistory; // History of states for the spacecraft

    /**
     * @brief Generates a unique identifier for the spacecraft based on its properties.
     * This method is called in the constructor to ensure that each spacecraft has a unique ID.
     */
    void generate_id_hash();
};

} // namespace astro
} // namespace waveguide