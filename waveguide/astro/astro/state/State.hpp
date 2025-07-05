#pragma once

#include <iostream>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/types/typedefs.hpp>

namespace astro {

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
        elements.convert<T>(sys);
    }
    template <IsOrbitalElements T>
    State convert(const AstrodynamicsSystem& sys) const
    {
        return { time, elements.in<T>(sys) };
    }

    Time time;
    OrbitalElements elements;
};

bool state_time_comparitor(State s, Time time);

} // namespace astro