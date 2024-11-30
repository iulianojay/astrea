#pragma once

#include "astro/platforms/Vehicle.hpp"

class NullVehicle {
public:

    NullVehicle(const State& state = State(), const double& mass = 0.0) :
        _state(state), _mass(mass)
    {}

    void update_state(const State& state) { _state = state; }
    State get_state() const { return _state; }
    double get_mass() const { return _mass; }

private:
    State _state;
    double _mass;
};