#pragma once

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/units/units.hpp>

class NullVehicle {

  public:
    NullVehicle(const State& state = State(), const Date& epoch = J2000, const Mass& mass = 0.0 * mp_units::si::unit_symbols::kg) :
        _state(state),
        _epoch(epoch),
        _mass(mass)
    {
    }

    void update_state(const State& state) { _state = state; }
    State& get_state() { return _state; }
    Date get_epoch() const { return _epoch; }
    Mass get_mass() const { return _mass; }

  private:
    State _state;
    Date _epoch;
    Mass _mass;
};