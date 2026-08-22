

# File State.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**State.hpp**](State_8hpp.md)

[Go to the documentation of this file](State_8hpp.md)


```C++

#pragma once

#include <iosfwd>
#include <optional>

#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/state/attitude/Attitude.hpp>
#include <astro/state/attitude/Quaternion.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/property_getters.hpp>
#include <astro/systems/system_utilities.hpp>
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

    State(const OrbitalElements& elements, const Date& epoch, const std::optional<Attitude>& attitude = std::nullopt) :
        _elements(elements),
        _epoch(epoch),
        _attitude(attitude)
    {
    }

    template <IsOrbitalElements T>
    State(const T& elements, const Date& epoch, const std::optional<Attitude>& attitude = std::nullopt) :
        _elements(elements.template in_frame<frames::primary>(epoch, astrea::astro::get_mu<T::frame.origin>())),
        _epoch(epoch),
        _attitude(attitude)
    {
    }

    State(const StateHistory& history);

    bool operator==(const State& other) const;

    const OrbitalElements& get_elements() const { return _elements; }

    const std::optional<Attitude>& get_attitude() const { return _attitude; }

    const Date& get_epoch() const { return _epoch; }

    GravParam get_mu() const
    {
        return std::visit(
            []<typename ElemT>(const ElemT&) -> GravParam {
                return astrea::astro::get_mu<decltype(ElemT::frame)::origin>();
            },
            _elements.extract()
        );
    }

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
        return { in_element_set<T>(), _epoch };
    }

    template <IsOrbitalElements T>
    T in_element_set() const
    {
        // TODO: How do we do this?
        // if constexpr (std::is_specialization_v<_elements, Cartesian>) {
        //     // cartesian<a> -> cartesian<b> -> set2<b>
        //     return _elements.template in_frame<T::frame>(_epoch, get_mu()).in_element_set<T>(get_mu());
        // }

        // set1<a> -> set2<a> -> cartesian<a> -> cartesian<b> -> set2<b>
        return _elements.in_element_set<T>(get_mu()).template in_frame<T::frame>(_epoch, get_mu());
    }

    RadiusVector<frames::primary> get_position() const
    {
        return in_element_set<Cartesian<frames::primary>>().get_position();
    }

    template <IsFrame auto _frame_>
    State& in_frame()
    {
        _elements = _elements.in_frame<_frame_>(get_epoch(), get_mu());
        return *this;
    }

    template <IsFrame auto _frame_>
    RadiusVector<_frame_> get_position_in_frame() const
    {
        return get_position().template in_frame<_frame_>(get_epoch());
    }

    VelocityVector<frames::primary> get_velocity() const
    {
        return in_element_set<Cartesian<frames::primary>>().get_velocity();
    }

    template <IsFrame auto _frame_>
    VelocityVector<_frame_> get_velocity_in_frame(const Date& date) const
    {
        return get_velocity().template in_frame<_frame_>(date);
    }

    template <IsOrbitalElements T>
    void set_elements(const T& elements, const bool convertToOriginal = false)
    {
        std::size_t originalIndex = _elements.index();
        _elements                 = elements;
        if (convertToOriginal) { _elements.convert_to_set(originalIndex, get_mu()); }
    }

    void set_attitude(const Attitude& attitude) { _attitude = attitude; }

    void set_epoch(const Date& epoch) { _epoch = epoch; }

  private:
    OrbitalElements _elements; 
    Date _epoch; 
    std::optional<Attitude> _attitude; 

    std::vector<double> force_to_double_vector() const
    {
        auto retval = _elements.force_to_double_vector();
        if (_attitude.has_value()) {
            const auto& attitudeVector = _attitude->force_to_double_vector();
            retval.insert(retval.end(), attitudeVector.begin(), attitudeVector.end());
        }
        return retval;
    }

    static State from_double_vector(const std::vector<double>& vec, const std::size_t idx);

    State operator+(const State& other) const;

    State& operator+=(const State& other);

    State operator-(const State& other) const;

    State& operator-=(const State& other);

    State operator*(const Unitless& scalar) const;

    State& operator*=(const Unitless& scalar);

    State operator/(const Unitless& scalar) const;

    State& operator/=(const Unitless& scalar);

    StatePartial operator/(const Time& divisor) const;
};

class StatePartial {

  public:
    StatePartial() = default;

    StatePartial(const Date& epoch, const OrbitalElementPartials& elementPartials, const std::optional<AttitudePartials>& attitudePartial = std::nullopt) :
        _epoch(epoch),
        _elementPartials(elementPartials),
        _attitudePartial(attitudePartial)
    {
    }

    State operator*(const Time& time) const;

    const Date& get_epoch() const;

    std::vector<double> force_to_double_vector() const
    {
        auto retval = _elementPartials.force_to_double_vector();
        if (_attitudePartial.has_value()) {
            const auto& attitudeVector = _attitudePartial->force_to_double_vector();
            retval.insert(retval.end(), attitudeVector.begin(), attitudeVector.end());
        }
        return retval;
    }

  private:
    Date _epoch; 
    OrbitalElementPartials _elementPartials; 
    std::optional<AttitudePartials> _attitudePartial; 
};

} // namespace astro
} // namespace astrea
```


