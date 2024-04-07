#pragma once

#include "ElementSet.hpp"
#include "GravitationalBody.hpp"
#include "conversions.hpp"
#include "typedefs.hpp"
#include "solar_system.hpp"

class OrbitalElements {
public:

    OrbitalElements(element_array elements, ElementSet set, GravitationalBody centralBody) : 
        elements(elements), set(set), centralBody(centralBody) {}

    element_array convert(ElementSet newSet) {
        // Check if conversion is necessary
        if (newSet == set) {
            return elements;
        }

        // Generic conversion
        elements = conversions::convert(elements, set, newSet, centralBody);
        set = newSet;

        // Return as convenience
        return elements;
    }
    
private:
    element_array elements;
    ElementSet set;
    GravitationalBody centralBody;
};