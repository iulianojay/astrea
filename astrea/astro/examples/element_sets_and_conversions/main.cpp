#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea uses strongly typed element sets to allow an easier user interface
    // for conversions, and common operators. Currently, there are 3 supported orbital element sets:
    // - Classical Orbital Elements (Keplerian)
    // - Modified Equinoctial Elements (Equinoctial)
    // - State Vectors (Cartesian)
    // Each element set can be defined independent of a reference system, but a reference system is required
    // for conversions and propagation.

    // For now, the Cartesian element set is defined in the ECI frame, but future releases will support
    // other frames as well.
    Cartesian cartesian{
        7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s,
    };
    std::cout << "Cartesian: " << cartesian << std::endl;

    // Conversions at the instance level are done through constructors
    AstrodynamicsSystem sys; // Default system is Earth
    Keplerian keplerian{ cartesian, sys };
    Equinoctial equinoctial{ keplerian, sys };
    std::cout << "Converted to Keplerian: " << keplerian << std::endl;
    std::cout << "Converted to Equinoctial: " << equinoctial << std::endl;
    std::cout << "Converted back to Cartesian: " << Cartesian(equinoctial, sys) << std::endl << std::endl;

    // Each element set also supports common operators **but only for the same element set**
    Cartesian cartesian2{
        8000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.0 * km / s, 1.0 * km / s,
    };
    std::cout << "Cartesian 2: " << cartesian2 << std::endl;
    std::cout << "Cartesian2 + Cartesian: " << (cartesian2 + cartesian) << std::endl;
    std::cout << "Cartesian2 - Cartesian: " << (cartesian2 - cartesian) << std::endl;

    // Common mathematic abstractions such as scalar multiplication and division are also supported
    const Unitless scale = 2.0 * one;
    std::cout << "Cartesian * 2: " << (cartesian * scale) << std::endl;
    std::cout << "Cartesian / 2: " << (cartesian / scale) << std::endl << std::endl;

    // And each element set also has a corresponding partial derivative element set for use in
    // state transition matrices and integration
    CartesianPartial cartesianPartial = cartesian / (1.0 * s);
    std::cout << "Cartesian Partial (Cartesian / Time): " << cartesianPartial << std::endl << std::endl;

    // Astrea also provides a class for dealing with orbital elements generically. This allows users to
    // write a single interface for dealing with any element set without templating or polymorphism.
    OrbitalElements elements(cartesian);
    std::cout << "OrbitalElements (from Cartesian): " << elements << std::endl;
    elements = keplerian;
    std::cout << "OrbitalElements (from Keplerian): " << elements << std::endl;

    // This class can handle conversions internally
    elements.convert_to_orbital_set<Keplerian>(sys);
    std::cout << "OrbitalElements converted to Keplerian: " << elements << std::endl;
    const OrbitalElements converted = static_cast<const OrbitalElements&>(elements).convert_to_orbital_set<Equinoctial>(sys);
    std::cout << "OrbitalElements converted to Equinoctial: " << converted << std::endl;

    // And it can return the desired element set directly
    const Keplerian keplerian2 = elements.in_orbital_set<Keplerian>(sys);
    std::cout << "Extracted Keplerian conversion: " << keplerian2 << std::endl;
}