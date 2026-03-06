

# File State.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**State.hpp**](State_8hpp.md)

[Go to the documentation of this file](State_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);
    friend class Integrator;
    friend class StateTransitionMatrix;

  public:
    State() = default;

    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys) :
        _elements(elements),
        _epoch(epoch),
        _system(&sys)
    {
    }

    State(const StateHistory& history);

    State(const OrbitalElements&, const Date&, AstrodynamicsSystem&&) = delete;

    bool operator==(const State& other) const;

    const OrbitalElements& get_elements() const { return _elements; }

    const Date& get_epoch() const { return _epoch; }

    const AstrodynamicsSystem& get_system() const { return *_system; }

    template <IsOrbitalElements T>
    void convert_to_set()
    {
        _elements.convert_to_set<T>(get_mu());
    }

    State& convert_to_set(const std::size_t idx)
    {
        _elements.convert_to_set(idx, get_mu());
        return *this;
    }

    State convert_to_set(const std::size_t idx) const
    {
        State newState = *this;
        newState._elements.convert_to_set(idx, get_mu());
        return newState;
    }

    template <IsOrbitalElements T>
    State convert_to_set() const
    {
        return { in_element_set<T>(), _epoch, get_system() };
    }

    template <IsOrbitalElements T>
    T in_element_set() const
    {
        return _elements.in_element_set<T>(get_mu());
    }

    RadiusVector<frames::earth::icrf> get_position() const { return in_element_set<Cartesian>().get_position(); }

    VelocityVector<frames::earth::icrf> get_velocity() const { return in_element_set<Cartesian>().get_velocity(); }

    template <typename Frame_T>
    RadiusVector<Frame_T> get_position_in_frame() const
    {
        return get_position().template in_frame<Frame_T>(_epoch);
    }

    template <IsOrbitalElements T>
    void set_elements(const T& elements, const bool convertToOriginal = false)
    {
        std::size_t originalIndex = _elements.index();
        _elements                 = elements;
        if (convertToOriginal) { _elements.convert_to_set(originalIndex, get_mu()); }
    }

    void set_epoch(const Date& epoch) { _epoch = epoch; }

    void set_system(const AstrodynamicsSystem& sys) { _system = &sys; }

  private:
    OrbitalElements _elements; 
    Date _epoch; 
    const AstrodynamicsSystem* _system; 

    GravParam get_mu() const
    {
        using namespace mp_units;
        return _system ? _system->get_mu() : 0.0 * pow<3>(astrea::detail::distance_unit) / pow<2>(astrea::detail::time_unit);
    }

    std::vector<Unitless> force_to_vector() const { return _elements.force_to_vector(); }


    static State from_vector(const std::vector<Unitless>& vec, const std::size_t idx, const AstrodynamicsSystem& sys);

    State operator+(const State& other) const;

    State& operator+=(const State& other);

    State operator-(const State& other) const;

    State& operator-=(const State& other);

    State operator*(const Unitless& scalar) const;

    State& operator*=(const Unitless& scalar);

    State operator/(const Unitless& scalar) const;

    State& operator/=(const Unitless& scalar);

    StatePartial operator/(const Time& divisor) const;

    void validate_system(const State& other) const;
};

class StatePartial {
  public:
    StatePartial() = default;

    StatePartial(const OrbitalElementPartials& elementPartials, const Date& epoch, const AstrodynamicsSystem& sys) :
        _elementPartials(elementPartials),
        _epoch(epoch),
        _system(&sys)
    {
    }

    State operator*(const Time& time) const;

    const AstrodynamicsSystem& get_system() const;

    const Date& get_epoch() const;

  private:
    OrbitalElementPartials _elementPartials; 
    Date _epoch; 
    const AstrodynamicsSystem* _system; 
};

} // namespace astro
} // namespace astrea
```


