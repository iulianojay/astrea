#pragma once

#include <cmath>
#include <iostream>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <iomanip>
#include <iostream>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/Frame.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

class OrbitalElements : public ElementArray {

#include "astro/element_sets/orbital_elements/Cartesian.hpp"


    // template <typename T>
    // concept has_cartesian_constructor = requires(Cartesian elements) {
    //     { T(elements) };
    // };

    // template <typename T>
    // concept IsUserDefinedOrbitalElements = requires(T) {
    //     std::is_same<T, remove_cv_ref<T>>::value;
    //     std::is_default_constructible<T>::value;
    //     std::is_copy_constructible<T>::value;
    //     std::is_move_constructible<T>::value;
    //     std::is_destructible<T>::value;
    //     requires has_update_state<T>;
    //     requires has_get_state<T>;
    // };

    // namespace detail {

    // struct OrbitalElementsInnerBase {
    //     // Virtual destructor
    //     virtual ~OrbitalElementsInnerBase() {}

    //     // Required methods
    //     virtual void update_state(const State& state) = 0;
    //     virtual State& get_state() = 0;

    //     // Optional methods
    //     virtual double get_ram_area() const = 0;

    //     // Implementation utilities
    //     virtual std::unique_ptr<OrbitalElementsInnerBase> clone() const = 0;
    //     virtual const void *get_ptr() const = 0;
    //     virtual void *get_ptr() = 0;
    // };

    // template <typename T>
    // struct OrbitalElementsInner final : public OrbitalElementsInnerBase {

    //     // Default constructor
    //     OrbitalElementsInner() = default;

    //     // Delete other constructors
    //     OrbitalElementsInner(const OrbitalElementsInner&) = delete;
    //     OrbitalElementsInner(OrbitalElementsInner&&) = delete;
    //     OrbitalElementsInner& operator=(const OrbitalElementsInner&) = delete;
    //     OrbitalElementsInner& operator=(OrbitalElementsInner&&) = delete;

    //     // Constructors from T (copy and move variants).
    //     explicit OrbitalElementsInner(const T &x) : _value(x) {}
    //     explicit OrbitalElementsInner(T &&x) : _value(std::move(x)) {}

    //     // Invoke required methods directly
    //     void update_state(const State& state) final {
    //         _value.update_state(state);
    //     }
    //     State& get_state() final {
    //         return _value.get_state();
    //     }

    //     // Invoke implicit implementations for optional methods
    //     double get_ram_area() const final {
    //         return get_ram_area_impl(_value);
    //     }

    //     // Use templates to switch between defined or default implementations
    //     template <typename U>
    //     requires(!has_get_ram_area<U>)
    //     static double get_ram_area_impl(const U&) {
    //         return 0.0;
    //     }
    //     template <typename U>
    //     requires(has_get_ram_area<U>)
    //     static double get_ram_area_impl(const U& value) {
    //         return value.get_ram_area();
    //     }

    //     // The clone method, used in the copy constructor of OrbitalElements.
    //     std::unique_ptr<OrbitalElementsInnerBase> clone() const final {
    //         return std::make_unique<OrbitalElementsInner>(_value);
    //     }

    //     // Raw getters for the internal instance.
    //     const void* get_ptr() const final {
    //         return &_value;
    //     }
    //     void* get_ptr() final {
    //         return &_value;
    //     }

    //     // OrbitalElements object
    //     T _value;
    // };

    // } // namespace detail

    // class OrbitalElements;

    // template <typename T>
    // concept IsGenericallyConstructableOrbitalElements = requires(T) {
    //     requires IsUserDefinedOrbitalElements<T>;
    //     std::negation<std::is_same<OrbitalElements, remove_cv_ref<T>>>::value;
    // };


    // class OrbitalElements {
    // public:

    //     // Default constructor
    //     OrbitalElements();

    // private:

    //     void generic_ctor_impl();

    // public:

    //     template <typename T>
    //     requires(IsGenericallyConstructableOrbitalElements<T>)
    //     explicit OrbitalElements(T &&x)
    //         : _ptr( std::make_unique< detail::OrbitalElementsInner<remove_cv_ref<T>> >(std::forward<T>(x)) )
    //     {
    //         generic_ctor_impl();
    //     }

    //     // Copy constructor
    //     OrbitalElements(const OrbitalElements&);

    //     // Move constructor
    //     OrbitalElements(OrbitalElements&&) noexcept;

    //     // Move assignment operator
    //     OrbitalElements& operator=(OrbitalElements&&) noexcept;

    //     // Copy assignment operator
    //     OrbitalElements& operator=(const OrbitalElements&);

    //     /// Assignment from a user-defined OrbitalElements
    //     template <typename T>
    //     requires(IsGenericallyConstructableOrbitalElements<T>)
    //     OrbitalElements& operator=(T&& x) {
    //         return (*this) = OrbitalElements(std::forward<T>(x));
    //     }

    //     template <typename T>
    //     requires(IsGenericallyConstructableOrbitalElements<T>)
    //     const T *extract() const noexcept {
    //         auto p = static_cast<const detail::OrbitalElementsInner<T> *>(ptr());
    //         return p == nullptr ? nullptr : &(p->_value);
    //     }

    //     // Update state
    //     void update_state(const State& state) {
    //         return _ptr->update_state(state);
    //     }

    //     // Get state
    //     State& get_state() {
    //         return _ptr->get_state();
    //     }

    //     // Pointer to user-defined elements
    //     const void* get_ptr() const;
    //     void* get_ptr();

    // private:

    //     // Pointer to the inner base elements
    //     std::unique_ptr<detail::OrbitalElementsInnerBase> _ptr;

    //     // Members
    //     State _state;

    //     // Ensure the pointer actually points to something
    //     detail::OrbitalElementsInnerBase const *ptr() const {
    //         assert(_ptr.get() != nullptr);
    //         return _ptr.get();
    //     }
    //     detail::OrbitalElementsInnerBase *ptr() {
    //         assert(_ptr.get() != nullptr);
    //         return _ptr.get();
    //     }
    // };

    class OrbitalElements : public element_array {

        friend std::ostream& operator<<(std::ostream&, OrbitalElements const&);

      public:
        // Constructors
        OrbitalElements(const ElementSet& set = ElementSet::CARTESIAN);
        OrbitalElements(const element_array& elements, const ElementSet& set = ElementSet::CARTESIAN);
        ~OrbitalElements() = default;

        // Copy assignment
        OrbitalElements& operator=(const OrbitalElements& other);

        // Addition
        OrbitalElements operator+(const OrbitalElements& other) const;
        OrbitalElements& operator+=(const OrbitalElements& other);

        // Subtraction
        OrbitalElements operator-(const OrbitalElements& other) const;
        OrbitalElements& operator-=(const OrbitalElements& other);

        // Utilities
        void convert(const ElementSet& newSet, const AstrodynamicsSystem& system);
        OrbitalElements convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const;

        const ElementSet& get_set() const;
        const bool same_set(const OrbitalElements& other);

        const bool nearly_equal(const OrbitalElements& other, bool ignoreFastVariable = false, const double& tol = 1e-8);

      private:
        ElementSet set;
    };