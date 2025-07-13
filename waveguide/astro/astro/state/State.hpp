#pragma once

#include <iostream>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astro {

class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);

  public:
    State() = default;
    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys) :
        _elements(elements),
        _epoch(epoch),
        _system(&sys)
    {
    }

    const OrbitalElements& get_elements() const { return _elements; }
    const Date& get_epoch() const { return _epoch; }
    const AstrodynamicsSystem& get_system() const { return *_system; }

    template <IsOrbitalElements T>
    void convert()
    {
        _elements.convert<T>(get_system());
    }
    template <IsOrbitalElements T>
    State convert() const
    {
        return { _elements.in<T>(get_system()), _epoch, get_system() };
    }

  private:
    Date _epoch;
    OrbitalElements _elements;
    const AstrodynamicsSystem* _system;
    // Frame frame; // TODO: Frames
};

} // namespace astro