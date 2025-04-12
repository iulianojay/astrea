#pragma once

#include <cmath>
#include <iostream>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/Frame.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

class OrbitalElements : public ElementArray {

    friend std::ostream& operator<<(std::ostream&, OrbitalElements const&);

  public:
    OrbitalElements(const ElementSet& set = ElementSet::CARTESIAN) :
        set(set)
    {
        for (int ii = 0; ii < 6; ++ii) {
            _M_elems[ii] = 0.0;
        }
    }
    OrbitalElements(const ElementArray& elements, const ElementSet& set = ElementSet::CARTESIAN) :
        set(set)
    {
        std::copy(std::begin(elements), std::end(elements), _M_elems);
    }

    void convert(const ElementSet& newSet, const AstrodynamicsSystem& system)
    {
        // Check if conversion is necessary
        if (newSet == set) { return; }

        // Generic conversion
        const auto newElements = conversions::convert((*this), set, newSet, system);
        std::copy(std::begin(newElements), std::end(newElements), _M_elems);
        set = newSet;
    }

    OrbitalElements convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const
    {
        // Check if conversion is necessary
        if (newSet == set) { return OrbitalElements(*this); }

        // Generic conversion
        const auto newElements = conversions::convert((*this), set, newSet, system);
        return OrbitalElements(newElements, newSet);
    }

    const ElementSet& get_set() const { return set; }
    const bool same_set(const OrbitalElements& other) { return other.set == set; }

    // Copy assignment
    OrbitalElements& operator=(const OrbitalElements& other)
    {
        set = other.set;
        for (size_t ii = 0; ii < 6; ii++) {
            (*this)[ii] = other[ii];
        }
        return *this;
    }

    // Addition
    OrbitalElements operator+(const OrbitalElements& other) const
    {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be "
                                     "added.");
        }

        // Sum
        ElementArray sumElements = (*this);
        for (size_t ii = 0; ii < 6; ii++) {
            sumElements[ii] += other[ii];
        }
        return OrbitalElements(sumElements, set);
    }

    OrbitalElements& operator+=(const OrbitalElements& other)
    {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be "
                                     "added.");
        }

        // Sum
        for (size_t ii = 0; ii < 6; ii++) {
            (*this)[ii] += other[ii];
        }

        return (*this);
    }

    // Subtraction
    OrbitalElements operator-(const OrbitalElements& other) const
    {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be "
                                     "subtracted.");
        }

        // Diff
        ElementArray diffElements = (*this);
        for (size_t ii = 0; ii < 6; ii++) {
            diffElements[ii] -= other[ii];
        }
        return OrbitalElements(diffElements, set);
    }

    OrbitalElements& operator-=(const OrbitalElements& other)
    {
        // Check both element sets are the same
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be "
                                     "added.");
        }

        // Sum
        for (size_t ii = 0; ii < 6; ii++) {
            (*this)[ii] -= other[ii];
        }

        return (*this);
    }

    const bool nearly_equal(const OrbitalElements& other, bool ignoreFastVariable = false, const double& tol = 1e-8)
    {
        if (set != other.get_set()) { return false; }
        for (int ii = 0; ii < (ignoreFastVariable ? 5 : 6); ii++) {
            if (std::fabs((_M_elems[ii] - other[ii]) / _M_elems[ii]) > tol) { return false; }
        }
        return true;
    }

  private:
    ElementSet set;
};