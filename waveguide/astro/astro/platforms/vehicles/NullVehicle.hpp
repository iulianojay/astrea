#pragma once

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/units/units.hpp>

namespace astro {

class NullVehicle {

  public:
    NullVehicle(const State& state0 = State(), const Mass& mass = 0.0 * mp_units::si::unit_symbols::kg) :
        _state0(state0),
        _state(state0),
        _mass(mass)
    {
    }

    void update_state(const State& state) { _state = state; }
    State& get_state() { return _state; }
    const State& get_initial_state() const { return _state0; }
    Mass get_mass() const { return _mass; }

  private:
    State _state0;
    State _state;
    Mass _mass;
};

} // namespace astro