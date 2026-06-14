

# File Event.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**Event.hpp**](Event_8hpp.md)

[Go to the documentation of this file](Event_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/types/concepts.hpp>

namespace astrea {
namespace astro {

template <typename T>
concept HasMeasureEvent = requires(const T event, const Time& time, const State& state, const Vehicle& vehicle) {
    { event.measure_event(time, state, vehicle) } -> std::same_as<Unitless>;
};

template <typename T>
concept HasIsTerminal = requires(const T event) {
    { event.is_terminal() } -> std::same_as<bool>;
};

template <typename T>
concept HasTriggerEvent = requires(const T event, const Time& time, State& state, Vehicle& vehicle) {
    { event.trigger_action(time, state, vehicle) } -> std::same_as<void>;
};


template <typename T>
concept IsUserDefinedEvent = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires HasGetName<T>;
    requires HasMeasureEvent<T>;
    requires HasIsTerminal<T>;
};

namespace detail {

struct EventInnerBase {

    virtual ~EventInnerBase() {}

    virtual std::string get_name() const = 0;

    virtual Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const = 0;

    virtual bool is_terminal() const = 0;

    virtual void trigger_action(const Time& time, State& state, Vehicle& vehicle) const = 0;

    virtual std::unique_ptr<EventInnerBase> clone() const = 0;

    virtual const void* get_ptr() const = 0;

    virtual void* get_ptr() = 0;

    virtual const std::type_info& type() const = 0;
};

template <typename T>
struct EventInner final : public EventInnerBase {

    EventInner() = default;

    EventInner(const EventInner&) = delete;

    EventInner(EventInner&&) = delete;

    EventInner& operator=(const EventInner&) = delete;

    EventInner& operator=(EventInner&&) = delete;

    explicit EventInner(const T& x) :
        _value(x)
    {
    }

    explicit EventInner(T&& x) :
        _value(std::move(x))
    {
    }

    std::string get_name() const override final { return _value.get_name(); }

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override final
    {
        return _value.measure_event(time, state, vehicle);
    }

    bool is_terminal() const override final { return _value.is_terminal(); }

    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const override final
    {
        return trigger_action_impl(_value, time, state, vehicle);
    }

    template <typename U>
        requires(HasTriggerEvent<U>)
    void trigger_action_impl(const U& value, const Time& time, State& state, Vehicle& vehicle) const
    {
        value.trigger_action(time, state, vehicle);
    }

    template <typename U>
        requires(!HasTriggerEvent<U>)
    void trigger_action_impl(const U& value, const Time& time, State& state, Vehicle& vehicle) const
    {
    }

    std::unique_ptr<EventInnerBase> clone() const final { return std::make_unique<EventInner>(_value); }

    const void* get_ptr() const final { return &_value; }

    void* get_ptr() final { return &_value; }

    const std::type_info& type() const final { return typeid(T); }

    T _value; 
};

} // namespace detail

class Event; // Forward declaration of the Event class

template <typename T>
concept IsGenericallyConstructableEvent = requires(T) {
    requires !std::is_same<Event, remove_cv_ref<T>>::value;
    requires IsUserDefinedEvent<T>;
};


class Event {

  public:
    Event();

  private:
    void generic_ctor_impl() {}

  public:
    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    explicit Event(T&& x) :
        _ptr(std::make_unique<detail::EventInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    Event(const Event&);

    Event(Event&&) noexcept;

    Event& operator=(Event&&) noexcept;

    Event& operator=(const Event&);

    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    Event& operator=(T&& x)
    {
        return (*this) = Event(std::forward<T>(x));
    }

    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::EventInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    template <IsGenericallyConstructableEvent T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::EventInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return ptr()->measure_event(time, state, vehicle);
    }

    bool is_terminal() const { return ptr()->is_terminal(); }

    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const
    {
        return ptr()->trigger_action(time, state, vehicle);
    }

    std::string get_name() const { return ptr()->get_name(); }

    const void* get_ptr() const;

    void* get_ptr();

  private:
    std::unique_ptr<detail::EventInnerBase> _ptr; 

    detail::EventInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    detail::EventInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace astrea
```


