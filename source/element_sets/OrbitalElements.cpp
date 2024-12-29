#include "OrbitalElements.hpp"

// Generic implicit constructor
void OrbitalElements::generic_ctor_impl() {
    _setId = ptr()->get_set_id();
}

// Copy constructor
OrbitalElements::OrbitalElements(const OrbitalElements& other) :
    _ptr(other._ptr->clone()),
    _setId(other._setId)
{}

// Move constructor
OrbitalElements::OrbitalElements(OrbitalElements&& other) noexcept :
    _ptr(std::move(other._ptr)),
    _setId(std::move(other._setId))
{}

// Move assignment operator
OrbitalElements& OrbitalElements::operator=(OrbitalElements&& other) noexcept {
    if (this != &other) {
        _ptr = std::move(other._ptr);
        _setId = std::move(other._setId);
    }
    return *this;
}

// Copy assignment operator
OrbitalElements& OrbitalElements::operator=(const OrbitalElements& other) {
    return *this = OrbitalElements(other);
}


/// Assignment from a user-defined OrbitalElements
template <typename T>
requires(IsGenericallyConstructableOrbitalElements<T>)
OrbitalElements& OrbitalElements::operator=(T&& x) {
    return (*this) = OrbitalElements(std::forward<T>(x));
}

template <typename T>
requires(IsGenericallyConstructableOrbitalElements<T>)
const T *OrbitalElements::extract() const noexcept {
    auto p = static_cast<const detail::OrbitalElementsInner<T> *>(ptr());
    return p == nullptr ? nullptr : &(p->_value);
}

// Utilities
void OrbitalElements::convert(const ElementSet& newSet, const AstrodynamicsSystem& system) {
    if (static_cast<enum_type>(newSet) == _setId) { return; }

    const auto newElements = convert_impl(newSet, system);
    (*this) = newElements;
}
OrbitalElements OrbitalElements::convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const {
    if (static_cast<enum_type>(newSet) == _setId) { return (*this); }

    return convert_impl(newSet, system);
}

Cartesian OrbitalElements::to_cartesian(const AstrodynamicsSystem& system) const {
    return ptr()->to_cartesian(system);
}
Keplerian OrbitalElements::to_keplerian(const AstrodynamicsSystem& system) const {
    return ptr()->to_keplerian(system);
}

const enum_type& OrbitalElements::get_set_id() const {
    return ptr()->get_set_id();
}

const bool OrbitalElements::same_set(const OrbitalElements& other) const {
    return (_setId != other._setId);
}

// Ensure the pointer actually points to something
detail::OrbitalElementsInnerBase const *OrbitalElements::ptr() const {
    assert(_ptr.get() != nullptr);
    return _ptr.get();
}
detail::OrbitalElementsInnerBase *OrbitalElements::ptr() {
    assert(_ptr.get() != nullptr);
    return _ptr.get();
}

OrbitalElements OrbitalElements::convert_impl(const ElementSet& newSet, const AstrodynamicsSystem& system) const {
    switch (newSet) {
        case (ElementSet::CARTESIAN) :
            return OrbitalElements(to_cartesian(system));

        case (ElementSet::KEPLERIAN) :
            return OrbitalElements(to_keplerian(system));

        default:
            throw std::logic_error("This conversion is not directly available from this class.");
    }
}


std::ostream& operator<<(std::ostream& os, OrbitalElements const& elements) {
    os << (*elements.ptr());
    return os;
}