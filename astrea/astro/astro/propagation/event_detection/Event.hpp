/**
 * @file Event.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing an Event in the astrea astro library.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/types/concepts.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type has a method to detect an event.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasMeasureEvent = requires(const T event, const Time& time, const State& state, const Vehicle& vehicle) {
    { event.measure_event(time, state, vehicle) } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to determine if an event is terminal.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasIsTerminal = requires(const T event) {
    { event.is_terminal() } -> std::same_as<bool>;
};

/**
 * @brief Concept to check if a type has a method to trigger a post-event action.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasTriggerEvent = requires(const T event, const Time& time, State& state, Vehicle& vehicle) {
    { event.trigger_action(time, state, vehicle) } -> std::same_as<void>;
};


/**
 * @brief Concept to check if a type is a user-defined Event.
 *
 * @tparam T The type to check.
 */
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

/**
 * @brief Pure virtual base class for Event inner implementations.
 */
struct EventInnerBase {

    /**
     * @brief Destructor for EventInnerBase.
     */
    virtual ~EventInnerBase() {}

    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    virtual std::string get_name() const = 0;

    /**
     * @brief Detects if the Event is triggered by a Vehicle.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    virtual Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const = 0;

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    virtual bool is_terminal() const = 0;

    /**
     * @brief Triggers the Event for a Vehicle.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to trigger the Event for.
     * @return Vehicle The Vehicle after the Event has been triggered.
     */
    virtual void trigger_action(const Time& time, State& state, Vehicle& vehicle) const = 0;

    /**
     * @brief Clones the Event inner implementation.
     *
     * @return std::unique_ptr<EventInnerBase> A unique pointer to the cloned Event inner implementation.
     */
    virtual std::unique_ptr<EventInnerBase> clone() const = 0;

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return const void* A pointer to the internal Event instance.
     */
    virtual const void* get_ptr() const = 0;

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return void* A pointer to the internal Event instance.
     */
    virtual void* get_ptr() = 0;

    /**
     * @brief Gets the type information of the internal vehicle instance.
     *
     * @return const std::type_info& The type information of the internal vehicle instance.
     */
    virtual const std::type_info& type() const = 0;
};

/**
 * @brief A template class for Event inner implementations.
 *
 * @tparam T The type of the Event implementation.
 */
template <typename T>
struct EventInner final : public EventInnerBase {

    /**
     * @brief Default constructor for EventInner.
     */
    EventInner() = default;

    /**
     * @brief Deleted copy assignment operator.
     */
    EventInner(const EventInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    EventInner(EventInner&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    EventInner& operator=(const EventInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    EventInner& operator=(EventInner&&) = delete;

    /**
     * @brief Constructs a EventInner with a given value.
     *
     * @param x The value to initialize the Event inner implementation.
     */
    explicit EventInner(const T& x) :
        _value(x)
    {
    }

    /**
     * @brief Constructs a EventInner with a given value.
     *
     * @param x The value to initialize the Event inner implementation.
     */
    explicit EventInner(T&& x) :
        _value(std::move(x))
    {
    }

    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const override final { return _value.get_name(); }

    /**
     * @brief Detects if the Event is triggered by a Vehicle.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override final
    {
        return _value.measure_event(time, state, vehicle);
    }

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const override final { return _value.is_terminal(); }

    /**
     * @brief Triggers the Event for a Vehicle.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to trigger the Event for.
     * @return Vehicle The Vehicle after the Event has been triggered.
     */
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const override final
    {
        return trigger_action_impl(_value, time, state, vehicle);
    }

    /**
     * @brief Implementation of the trigger_action function for an Event with a trigger.
     *
     * @tparam U The type of the Event implementation.
     * @param value The Event implementation instance.
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to trigger the Event for.
     * @return Vehicle The Vehicle after the Event has been triggered.
     */
    template <typename U>
        requires(HasTriggerEvent<U>)
    void trigger_action_impl(const U& value, const Time& time, State& state, Vehicle& vehicle) const
    {
        value.trigger_action(time, state, vehicle);
    }

    /**
     * @brief Implementation of the trigger_action function for an Event without a trigger. Does nothing.
     *
     * @tparam U The type of the Event implementation.
     * @param value The Event implementation instance.
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to trigger the Event for.
     * @return Vehicle The Vehicle after the Event has been triggered.
     */
    template <typename U>
        requires(!HasTriggerEvent<U>)
    void trigger_action_impl(const U& value, const Time& time, State& state, Vehicle& vehicle) const
    {
    }

    /**
     * @brief Clones the Event inner implementation.
     *
     * @return std::unique_ptr<EventInnerBase> A unique pointer to the cloned Event inner implementation.
     */
    std::unique_ptr<EventInnerBase> clone() const final { return std::make_unique<EventInner>(_value); }

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return const void* A pointer to the internal Event instance.
     */
    const void* get_ptr() const final { return &_value; }

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return void* A pointer to the internal Event instance.
     */
    void* get_ptr() final { return &_value; }

    /**
     * @brief Gets the type information of the internal vehicle instance.
     *
     * @return const std::type_info& The type information of the internal vehicle instance.
     */
    const std::type_info& type() const final { return typeid(T); }

    T _value; //!< The value of the Event inner implementation, which is the user-defined Event type.
};

} // namespace detail

class Event; // Forward declaration of the Event class

/**
 * @brief Concept to check if a type can be generically constructed as a Event.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsGenericallyConstructableEvent = requires(T) {
    requires !std::is_same<Event, remove_cv_ref<T>>::value;
    requires IsUserDefinedEvent<T>;
};


/**
 * @brief A class representing a Event in the astrea astro platform.
 * This class serves as a base for user-defined Events and provides a common interface.
 */
class Event {

  public:
    /**
     * @brief Default constructor for Event.
     */
    Event();

  private:
    /**
     * @brief Generic implicit constructor for Event.
     */
    void generic_ctor_impl() {}

  public:
    /**
     * @brief Constructs a Event with a user-defined type.
     *
     * @tparam T The type of the user-defined Event.
     * @param x The user-defined Event instance to initialize the Event.
     */
    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    explicit Event(T&& x) :
        _ptr(std::make_unique<detail::EventInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    /**
     * @brief Copy constructor for Event.
     *
     * @param other The Event instance to copy from.
     */
    Event(const Event&);

    /**
     * @brief Move constructor for Event.
     *
     * @param other The Event instance to move from.
     */
    Event(Event&&) noexcept;

    /**
     * @brief Copy assignment operator for Event.
     *
     * @return Event& A reference to the current Event instance.
     */
    Event& operator=(Event&&) noexcept;

    /**
     * @brief Move assignment operator for Event.
     *
     * @param other The Event instance to move from.
     * @return Event& A reference to the current Event instance.
     */
    Event& operator=(const Event&);

    /**
     * @brief Generic assignment operator for Event.
     *
     * @tparam T The type of the user-defined Event.
     * @param x The user-defined Event instance to assign to the Event.
     * @return Event& A reference to the current Event instance.
     */
    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    Event& operator=(T&& x)
    {
        return (*this) = Event(std::forward<T>(x));
    }

    /**
     * @brief Extracts the user-defined Event from the Event instance.
     *
     * @tparam T The type of the user-defined Event to extract.
     * @return const T* A pointer to the user-defined Event if it matches the type, otherwise nullptr.
     */
    template <typename T>
        requires(IsGenericallyConstructableEvent<T>)
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::EventInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Extracts the user-defined Event from the Event instance.
     *
     * @tparam T The type of the user-defined Event to extract.
     * @return T* A pointer to the user-defined Event if it matches the type, otherwise nullptr.
     */
    template <IsGenericallyConstructableEvent T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::EventInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Detects if the Event is triggered by a Vehicle.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return ptr()->measure_event(time, state, vehicle);
    }

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const { return ptr()->is_terminal(); }

    /**
     * @brief Triggers the Event for a Vehicle.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle.
     * @param vehicle The Vehicle to trigger the Event for.
     * @return Vehicle The Vehicle after the Event has been triggered.
     */
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const
    {
        return ptr()->trigger_action(time, state, vehicle);
    }

    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const { return ptr()->get_name(); }

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return const void* A pointer to the internal Event instance.
     */
    const void* get_ptr() const;

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return void* A pointer to the internal Event instance.
     */
    void* get_ptr();

  private:
    std::unique_ptr<detail::EventInnerBase> _ptr; //!< Pointer to the internal Event implementation, which can be a user-defined type

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return detail::EventInnerBase* A pointer to the internal Event instance.
     */
    detail::EventInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    /**
     * @brief Gets a pointer to the internal Event instance.
     *
     * @return detail::EventInnerBase* A pointer to the internal Event instance.
     */
    detail::EventInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace astrea