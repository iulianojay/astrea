#include "OrbitalElements.hpp"


std::ostream &operator<<(std::ostream& os, OrbitalElements const& elements) { 
    os << "(" << elements.set << ") [" << elements[0];
    for (const auto& x: elements) {
        os << ", " << x;
    } 
    os << "]";
    return os;
}