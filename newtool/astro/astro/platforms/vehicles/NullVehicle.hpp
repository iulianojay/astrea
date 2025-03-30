#pragma once

#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>

class NullVehicle {
  public:
    NullVehicle(const State& state = State(), const Date& epoch = J2000, const double& mass = 0.0) :
        _state(state),
        _epoch(epoch),
        _mass(mass)
    {
    }

    void update_state(const State& state) { _state = state; }
    State& get_state() { return _state; }
    Date get_epoch() const { return _epoch; }
    double get_mass() const { return _mass; }

  private:
    State _state;
    Date _epoch;
    double _mass;
};