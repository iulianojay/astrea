#pragma once

#include "OrbitalElements.hpp"
#include "Time.hpp"

class State {

    friend std::ostream &operator<<(std::ostream& os, const State& state);

public:

    State(Time time, OrbitalElements elements): time(time), elements(elements) {}
    State(Time time, element_array elements, ElementSet set): time(time), elements(elements, set) {}

    Time time;
    OrbitalElements elements;

};

bool state_time_comparitor(State s, Time time);