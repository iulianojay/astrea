#pragma once

#include <iostream>

#include "astro/types/typedefs.hpp"
#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/time/Time.hpp"

class State {

#ifndef SWIG
    friend std::ostream &operator<<(std::ostream& os, const State& state);
#endif

public:

    State() = default;
    State(Time time, OrbitalElements elements): time(time), elements(elements) {}
    State(Time time, element_array elements, ElementSet set): time(time), elements(elements, set) {}

    Time time;
    OrbitalElements elements;

};

bool state_time_comparitor(State s, Time time);


#ifdef SWIG

%template(StateVector) std::vector<State>;

#endif