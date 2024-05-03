#pragma once

#include "AstrodynamicsSystem.hpp"
#include "ElementSet.hpp"
#include "GravitationalBody.hpp"
#include "conversions.hpp"
#include "typedefs.hpp"

class OrbitalElements {
public:

    OrbitalElements() : elements{0.0} {}
    OrbitalElements(const element_array elements, const ElementSet set, AstrodynamicsSystem* system) : 
        elements(elements), set(set), system(system) {}

    element_array convert(ElementSet newSet) {
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

    element_array as_array() { return elements; }
    AstrodynamicsSystem* get_system() { return system; }
    
private:
    element_array elements;
    ElementSet set;
    AstrodynamicsSystem* system;
};