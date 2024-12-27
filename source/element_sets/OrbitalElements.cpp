#include "OrbitalElements.hpp"

#include <cstdio>


OrbitalElements::OrbitalElements(const ElementSet& set) : set(set) {
    for (int ii = 0; ii < 6; ++ii) {
        _M_elems[ii] = 0.0;
    }
}


OrbitalElements::OrbitalElements(const element_array& elements, const ElementSet& set) : set(set) {
    std::copy(std::begin(elements), std::end(elements), _M_elems);
}


void OrbitalElements::convert(const ElementSet& newSet, const AstrodynamicsSystem& system) {
    // Check if conversion is necessary
    if (newSet == set) {
        return;
    }

    // Generic conversion
    const auto newElements = conversions::convert((*this), set, newSet, system);
    std::copy(std::begin(newElements), std::end(newElements), _M_elems);
    set = newSet;
}


OrbitalElements OrbitalElements::convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const {
    // Check if conversion is necessary
    if (newSet == set) {
        return OrbitalElements(*this);
    }

    // Generic conversion
    const auto newElements = conversions::convert((*this), set, newSet, system);
    return OrbitalElements(newElements, newSet);
}


const ElementSet& OrbitalElements::get_set() const {
    return set;
}


const bool OrbitalElements::same_set(const OrbitalElements& other) {
    return other.set == set;
}


// Copy assignment
OrbitalElements& OrbitalElements::operator=(const OrbitalElements& other) {
    set = other.set;
    for (size_t ii = 0; ii < 6; ii++) {
        (*this)[ii] = other[ii];
    }
    return *this;
}


// Addition
OrbitalElements OrbitalElements::operator+(const OrbitalElements& other) const {
    // Check both element sets are the same
    if (other.set != set) {
        throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
    }

    // Sum
    element_array sumElements = (*this);
    for (size_t ii = 0; ii < 6; ii++) {
        sumElements[ii] += other[ii];
    }
    return OrbitalElements(sumElements, set);
}


OrbitalElements& OrbitalElements::operator+=(const OrbitalElements& other) {
    // Check both element sets are the same
    if (other.set != set) {
        throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
    }

    // Sum
    for (size_t ii = 0; ii < 6; ii++) {
        (*this)[ii] += other[ii];
    }

    return (*this);
}

// Subtraction
OrbitalElements OrbitalElements::operator-(const OrbitalElements& other) const {
    // Check both element sets are the same
    if (other.set != set) {
        throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be subtracted.");
    }

    // Diff
    element_array diffElements = (*this);
    for (size_t ii = 0; ii < 6; ii++) {
        diffElements[ii] -= other[ii];
    }
    return OrbitalElements(diffElements, set);
}


OrbitalElements& OrbitalElements::operator-=(const OrbitalElements& other) {
    // Check both element sets are the same
    if (other.set != set) {
        throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
    }

    // Sum
    for (size_t ii = 0; ii < 6; ii++) {
        (*this)[ii] -= other[ii];
    }

    return (*this);
}


const bool OrbitalElements::nearly_equal(const OrbitalElements& other, bool ignoreFastVariable, const double& tol) {
    if (set != other.get_set()) {
        return false;
    }
    for (int ii = 0; ii < (ignoreFastVariable ? 5 : 6); ii++) {
        if (std::fabs((_M_elems[ii] - other[ii])/_M_elems[ii]) > tol) {
            return false;
        }
    }
    return true;
}


std::ostream &operator<<(std::ostream& os, OrbitalElements const& elements) {
    os << "[" << elements[0];
    bool skipFirst = true;
    for (const auto& x: elements) {
        if (skipFirst) { skipFirst = false; continue; }
        os << ", " << x;
    }
    os << "] (" << ElementSetToString.at(elements.set) << ")";
    return os;
}


// Copy constructor
NewOrbitalElements::NewOrbitalElements(const NewOrbitalElements& other) :
    _ptr(other._ptr->clone()),
    _set(other._set)
{}

// Move constructor
NewOrbitalElements::NewOrbitalElements(NewOrbitalElements&& other) noexcept :
    _ptr(std::move(other._ptr)),
    _set(std::move(other._set))
{}

// Move assignment operator
NewOrbitalElements& NewOrbitalElements::operator=(NewOrbitalElements&& other) noexcept {
    if (this != &other) {
        _ptr = std::move(other._ptr);
        _set = std::move(other._set);
    }
    return *this;
}

// Copy assignment operator
NewOrbitalElements& NewOrbitalElements::operator=(const NewOrbitalElements& other) {
    return *this = NewOrbitalElements(other);
}