#pragma once

#ifndef SWIG
    #include <iostream>
#endif

#include "ElementSet.hpp"
#include "conversions.hpp"
#include "typedefs.hpp"

class AstrodynamicsSystem;

class OrbitalElements : public element_array {

#ifndef SWIG
    friend std::ostream& operator<<(std::ostream&, OrbitalElements const&);
#endif

public:

    OrbitalElements() : set(ElementSet::CARTESIAN) {
        for (int ii = 0; ii < 6; ++ii) {
            _M_elems[ii] = 0.0;
        }
    }
    OrbitalElements(const element_array elements, const ElementSet set = ElementSet::CARTESIAN) : set(set) {
        std::copy(std::begin(elements), std::end(elements), _M_elems);
    }

    void convert(ElementSet newSet, const AstrodynamicsSystem* system) {
        // Check if conversion is necessary
        if (newSet == set) {
            return;
        }

        // Generic conversion
        const auto newElements = conversions::convert((*this), set, newSet, system);
        std::copy(std::begin(newElements), std::end(newElements), _M_elems);
        set = newSet;
    }

    const ElementSet& get_set() const { return set; }
    const bool same_set(const OrbitalElements& other) {
        return other.set == set;
    }

    // Addition
    OrbitalElements operator+(const OrbitalElements& other) {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
        }

        // Sum
        element_array sumElements = (*this);
        for (int ii = 0; ii < 6; ii++) {
            sumElements[ii] += other[ii];
        }
        return OrbitalElements(sumElements, set);
    }

    OrbitalElements& operator+=(const OrbitalElements& rhs) {
        // Check both element sets are the same
        if (rhs.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
        }

        // Sum
        element_array& sumElements = (*this);
        for (int ii = 0; ii < 6; ii++) {
            sumElements[ii] += rhs[ii];
        }

        return (*this);
    }

    // Subtraction
    OrbitalElements operator-(const OrbitalElements& other) {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be subtracted.");
        }

        // Diff
        element_array diffElements = (*this);
        for (int ii = 0; ii < 6; ii++) {
            diffElements[ii] -= other[ii];
        }
        return OrbitalElements(diffElements, set);
    }

    OrbitalElements& operator-=(const OrbitalElements& rhs) {
        // Check both element sets are the same
        if (rhs.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
        }

        // Sum
        element_array& sumElements = (*this);
        for (int ii = 0; ii < 6; ii++) {
            sumElements[ii] -= rhs[ii];
        }

        return (*this);
    }

    static const int size() { return 6; }
    
private:

    ElementSet set;
};