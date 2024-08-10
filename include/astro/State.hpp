#pragma once

#include "OrbitalElements.hpp"
#include "Time.hpp"

class State {
public:

    State(Time time, OrbitalElements elements): time(time), elements(elements) {}
    State(Time time, double elements[6], ElementSet set): time(time), elements(elements, set) {}
    State(Time time, element_array elements, ElementSet set): time(time), elements(elements, set) {}

    Time time;
    OrbitalElements elements;

};

bool state_time_comparitor(State s, Time time);