#pragma once

#include "OrbitalElements.hpp"

class State {
public:

    State(double time, OrbitalElements elements): time(time), elements(elements) {}

    double time;
    OrbitalElements elements;

};

bool state_time_comparitor(State s, double time );