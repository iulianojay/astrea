#include <stdio.h>
#include <iostream>

#include "astro.hpp"

int main() {
    // Setup system
    AstrodynamicsSystem sys;

    // Build spacecraft
    element_array state0 = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    OrbitalElements elements0(state0, ElementSet::COE);
    Spacecraft vehicle(elements0, "Jan-01-2030 00:00:00.0");

    // Build Integrator
    Integrator integrator;

    // Build EoMs
    EquationsOfMotion eom(&sys);
    eom.switch_dynamics("two body");

    // Integrate
    integrator.propagate({0, 86400.0}, vehicle, eom);

    // Print
    std::cout << "state0 = " << vehicle.get_initial_state() << std::endl;
    std::cout << "statef = " << vehicle.get_final_state() << std::endl;

    return 1;
}