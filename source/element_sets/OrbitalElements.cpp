#include "OrbitalElements.hpp"

#include <cstdio>

std::ostream &operator<<(std::ostream& os, OrbitalElements const& elements) { 
    os << "[" << elements[0];
    for (const auto& x: elements) {
        os << ", " << x;
    } 
    os << "] (" << elements.set.to_char() << ")";
    return os;
}