#include <astro/element_sets/OrbitalElements.hpp>

#include <cstdio>

std::ostream& operator<<(std::ostream& os, OrbitalElements const& elements)
{
    os << "[" << elements[0];
    bool skipFirst = true;
    for (const auto& x : elements) {
        if (skipFirst) {
            skipFirst = false;
            continue;
        }
        os << ", " << x;
    }
    os << "] (" << ElementSetToString.at(elements.set) << ")";
    return os;
}