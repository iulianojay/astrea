#pragma once

#include <iostream>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);

  public:
    State() = default;

    State(const Time& time, const OrbitalElements& elements) :
        time(time),
        elements(elements)
    {
    }

    template <IsOrbitalElements T>
    void convert(const AstrodynamicsSystem& sys)
    {
        elements = T(elements, sys);
    }
    template <IsOrbitalElements T>
    State convert(const AstrodynamicsSystem& sys) const
    {
        return { time, T(elements, sys) };
    }

    Time time;
    OrbitalElements elements;
};

bool state_time_comparitor(State s, Time time);
