#pragma once

#include <string>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

#include <snapshot/snapshot.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class Spacecraft {

  public:
    // Constructor
    Spacecraft() = default;
    Spacecraft(const State& state0) :
        _state(state0),
        _state0(state0)
    {
        generate_id_hash();
    }
    Spacecraft(const snapshot::SpaceTrackGP& gp, const AstrodynamicsSystem& sys);

    // Destructor
    virtual ~Spacecraft() = default;

    void update_state(const State& state);
    State& get_state();

    const State& get_initial_state() const;
    void store_state_history(const StateHistory& history);
    StateHistory& get_state_history();
    const StateHistory& get_state_history() const;

    Mass get_mass() const;

    Unitless get_coefficient_of_drag() const;
    Unitless get_coefficient_of_lift() const;
    Unitless get_coefficient_of_reflectivity() const;

    SurfaceArea get_ram_area() const;
    SurfaceArea get_solar_area() const;
    SurfaceArea get_lift_area() const;

    std::size_t get_id() const { return _id; }
    std::string get_name() const { return _name; }

  protected:
    std::size_t _id;
    std::string _name;

    // Spacecraft properties
    Mass _mass                          = 1000.0 * mp_units::si::unit_symbols::kg;
    Unitless _coefficientOfDrag         = 2.2 * mp_units::one;
    Unitless _coefficientOfLift         = 0.9 * mp_units::one;
    Unitless _coefficientOfReflectivity = 1.1 * mp_units::one;
    SurfaceArea _ramArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    SurfaceArea _sunArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    SurfaceArea _liftArea               = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);

    // Orbital elements
    State _state0;
    State _state;
    StateHistory _stateHistory;

    void generate_id_hash();
};

} // namespace astro