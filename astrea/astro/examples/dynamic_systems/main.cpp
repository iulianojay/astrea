#include <chrono>
#include <iostream>

#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::non_si::day;
using mp_units::si::unit_symbols::s;

int main()
{
    // The AstrodynamicsSystem is Astrea's attempt to capture definitions and utilities around celestial bodies in a
    // dynamic system. The intention is that users can define a system with either a given body or a barycenter as the
    // center, and then add arbitrarily many or unique celestial bodies. Currently, the system is limited to only using
    // predefined bodies from the CelestialBody class, and it can only use a single body as the system center. Some parts
    // are incomplete, and the design lacks a complete foray of practical abstractions, utilities, and features, but it's a start.

    // Create a system with Earth as the center body
    AstrodynamicsSystem earthSystem("Earth"); // String were initially used to avoid hard coding CelestialBody
                                              // instances, but this may change for pre-defined celestial bodies
    const auto& earth = earthSystem.get_center();
    std::cout << "Center Body: " << earth->get_name() << std::endl;

    // Systems can also have secondary bodies
    AstrodynamicsSystem earthMoonSystem("Earth", { "Moon" });
    std::cout << "Bodies in Earth-Moon System: ";
    for (const auto& bodyName : earthMoonSystem.all_bodies()) {
        std::cout << bodyName << " ";
    }
    std::cout << std::endl;

    // Bodies can be accessed directly from the system
    const auto& moon = earthMoonSystem.get("Moon");
    std::cout << "Secondary Body: " << moon->get_name() << std::endl;

    return 0;
}