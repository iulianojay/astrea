#pragma once

#include "ElementSet.hpp"
#include "conversions.hpp"
#include "typedefs.hpp"

class AstrodynamicsSystem;

class OrbitalElements {
public:

    OrbitalElements() : elements{0.0} {}
    OrbitalElements(const double elementsIn[6], const ElementSet set) : set(set) {
        for (int ii = 0; ii < 6; ii++) {
            elements[ii] = elementsIn[ii];
        }
    }
    OrbitalElements(const element_array elements, const ElementSet set) : elements(elements), set(set) {}

    element_array convert(ElementSet newSet, AstrodynamicsSystem* system) {
        // Check if conversion is necessary
        if (newSet == set) {
            return elements;
        }

        // Generic conversion
        elements = conversions::convert(elements, set, newSet, system);
        set = newSet;

        // Return as convenience
        return elements;
    }

    // Addition
    OrbitalElements operator+(const OrbitalElements& other) {
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be added.");
        }
        element_array sumElements = elements;
        for (int ii = 0; ii < 6; ii++) {
            sumElements[ii] += other.elements[ii];
        }
        return OrbitalElements(sumElements, set);
    }

    // Subtraction
    OrbitalElements operator-(const OrbitalElements& other) {
        if (other.set != set) {
            throw std::runtime_error("Orbital elements must be converted to the same Element Set before they can be subtracted.");
        }
        element_array diffElements = elements;
        for (int ii = 0; ii < 6; ii++) {
            diffElements[ii] -= other.elements[ii];
        }
        return OrbitalElements(diffElements, set);
    }
    
    // Utilities
    element_array as_array() { return elements; }
    
private:
    element_array elements;
    ElementSet set;
};