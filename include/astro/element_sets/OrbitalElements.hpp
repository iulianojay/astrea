#pragma once

#ifndef SWIG
    #include <iostream>
    #include <iomanip>
    #include <cmath>
    #include <cassert>
    #include <stdexcept>
#endif

// Astro
#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/Frame.hpp"
#include "astro/utilities/conversions.hpp"

#include "astro/types/detail.hpp"
#include "astro/types/type_traits.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/types/typeid_name_extract.hpp"

#include "fwd/systems/AstrodynamicsSystem.fwd.hpp"

#include "astro/element_sets/orbital_elements/Cartesian.hpp"
#include "astro/element_sets/orbital_elements/Keplerian.hpp"


template <typename T>
concept HasGetSetId = requires(const T elements) {
    { elements.get_set_id() } -> std::same_as<const enum_type&>;
};

template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const AstrodynamicsSystem& sys) {
    { U(elements, sys) };
};

template <typename T>
concept HasDirectCartesianConversion = requires(const T elements, const AstrodynamicsSystem& sys) {
    { elements.to_cartesian(sys) } -> std::same_as<Cartesian>;
};

template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const AstrodynamicsSystem& sys) {
    { elements.to_keplerian(sys) } -> std::same_as<Keplerian>;
};

template <typename T>
concept IsUserDefinedOrbitalElements = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires std::is_same<T, Cartesian>::value || IsConstructableTo<T, Cartesian> || HasDirectCartesianConversion<T>;
    requires std::is_same<T, Keplerian>::value || IsConstructableTo<T, Keplerian> || HasDirectKeplerianConversion<T>;
    requires HasGetSetId<T>;
};

namespace detail {

struct OrbitalElementsInnerBase {

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElementsInnerBase& elements) {
        elements.print(os);
        return os;
    }

    // Virtual destructor
    virtual ~OrbitalElementsInnerBase() {}

    // Required methods
    virtual Cartesian to_cartesian(const AstrodynamicsSystem& sys) const = 0;
    virtual Keplerian to_keplerian(const AstrodynamicsSystem& sys) const = 0;
    virtual const enum_type& get_set_id() const = 0;

    // Optional methods

    // Implementation utilities
    virtual std::unique_ptr<OrbitalElementsInnerBase> clone() const = 0;
    virtual const void *get_ptr() const = 0;
    virtual void *get_ptr() = 0;

private:

    virtual void print(std::ostream&) const = 0;

};

template <typename T>
struct OrbitalElementsInner final : public OrbitalElementsInnerBase {

    // Default constructor
    OrbitalElementsInner() = default;

    // Delete other constructors
    OrbitalElementsInner(const OrbitalElementsInner&) = delete;
    OrbitalElementsInner(OrbitalElementsInner&&) = delete;
    OrbitalElementsInner& operator=(const OrbitalElementsInner&) = delete;
    OrbitalElementsInner& operator=(OrbitalElementsInner&&) = delete;

    // Constructors from T (copy and move variants).
    explicit OrbitalElementsInner(const T &x) : _value(x) {}
    explicit OrbitalElementsInner(T &&x) : _value(std::move(x)) {}

    // Get set
    const enum_type& get_set_id() const {
        return _value.get_set_id();
    }

    // Cartesian conversion
    Cartesian to_cartesian(const AstrodynamicsSystem& system) const {
        return to_cartesian_impl(_value, system);
    }

    template <typename U>
    requires(std::is_same<U, Cartesian>::value)
    Cartesian to_cartesian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return Cartesian(value);
    }
    template <typename U>
    requires(IsConstructableTo<U, Cartesian>)
    Cartesian to_cartesian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return Cartesian(value, system);
    }
    template <typename U>
    requires(!IsConstructableTo<U, Cartesian> && HasDirectCartesianConversion<U>)
    Cartesian to_cartesian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return value.to_cartesian(system);
    }

    // Keplerian conversion
    Keplerian to_keplerian(const AstrodynamicsSystem& system) const {
        return to_keplerian_impl(_value, system);
    }

    template <typename U>
    requires(std::is_same<U, Keplerian>::value)
    Keplerian to_keplerian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return Keplerian(value);
    }
    template <typename U>
    requires(IsConstructableTo<U, Keplerian>)
    Keplerian to_keplerian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return Keplerian(value, system);
    }
    template <typename U>
    requires(!IsConstructableTo<U, Keplerian> && HasDirectKeplerianConversion<U>)
    Keplerian to_keplerian_impl(const U& value, const AstrodynamicsSystem& system) const {
        return value.to_keplerian(system);
    }

    // The clone method, used in the copy constructor of OrbitalElements.
    std::unique_ptr<OrbitalElementsInnerBase> clone() const final {
        return std::make_unique<OrbitalElementsInner>(_value);
    }

    // Raw getters for the internal instance.
    const void* get_ptr() const final {
        return &_value;
    }
    void* get_ptr() final {
        return &_value;
    }

    // OrbitalElements object
    T _value;

private:

    void print(std::ostream& os) const final {
        os << _value;
    }

};

} // namespace detail

class OrbitalElements;

template <typename T>
concept IsGenericallyConstructableOrbitalElements = requires(T) {
    requires IsUserDefinedOrbitalElements<remove_cv_ref<T>>;
    std::negation<std::is_same<OrbitalElements, remove_cv_ref<T>>>::value;
};


class OrbitalElements {

    friend std::ostream& operator<<(std::ostream& os, OrbitalElements const& elements);

public:

    // Default constructor
    OrbitalElements();

private:

    void generic_ctor_impl();

public:

    template <typename T>
    requires(IsGenericallyConstructableOrbitalElements<T>)
    explicit OrbitalElements(T &&x) :
        _ptr( std::make_unique< detail::OrbitalElementsInner<remove_cv_ref<T>> >(std::forward<T>(x)) )
    {
        generic_ctor_impl();
    }

    // Copy constructor
    OrbitalElements(const OrbitalElements&);

    // Move constructor
    OrbitalElements(OrbitalElements&&) noexcept;

    // Move assignment operator
    OrbitalElements& operator=(OrbitalElements&&) noexcept;

    // Copy assignment operator
    OrbitalElements& operator=(const OrbitalElements&);

    /// Assignment from a user-defined OrbitalElements
    template <typename T>
    requires(IsGenericallyConstructableOrbitalElements<T>)
    OrbitalElements& operator=(T&& x);

    template <typename T>
    requires(IsGenericallyConstructableOrbitalElements<T>)
    const T *extract() const noexcept;

    // Utilities
    void convert(const ElementSet& newSet, const AstrodynamicsSystem& system);
    OrbitalElements convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const;

    Cartesian to_cartesian(const AstrodynamicsSystem& system) const;
    Keplerian to_keplerian(const AstrodynamicsSystem& system) const;

    const enum_type& get_set_id() const;
    const bool same_set(const OrbitalElements& other) const;

    // Pointer to user-defined elements
    const void* get_ptr() const;
    void* get_ptr();

private:

    // Pointer to the inner base elements
    std::unique_ptr<detail::OrbitalElementsInnerBase> _ptr;

    // Members
    enum_type _setId;

    // Ensure the pointer actually points to something
    detail::OrbitalElementsInnerBase const *ptr() const;
    detail::OrbitalElementsInnerBase *ptr();

    OrbitalElements convert_impl(const ElementSet& newSet, const AstrodynamicsSystem& system) const;
};
