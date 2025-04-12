#pragma once

#include <iostream>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);

  public:
    State() = default;
    State(Time time, OrbitalElements elements) :
        time(time),
        elements(elements)
    {
    }
    State(Time time, ElementArray elements, ElementSet set) :
        time(time),
        elements(elements, set)
    {
    }

    void convert(const ElementSet& set, const AstrodynamicsSystem& sys) { elements.convert(set, sys); }
    State convert(const ElementSet& set, const AstrodynamicsSystem& sys) const
    {
        return { time, elements.convert(set, sys) };
    }

    Time time;
    OrbitalElements elements;
};

bool state_time_comparitor(State s, Time time);
