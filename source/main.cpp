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

    // Build EoMs
    EquationsOfMotion eom(&sys);
    eom.switch_dynamics("two body");

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-13);
    integrator.set_rel_tol(1.0e-13);

    // Propagate
    Interval propInterval{seconds(0), seconds(86400)};
    integrator.propagate(propInterval, vehicle, eom);

    // Print
    std::cout << "state0 = " << vehicle.get_initial_state() << std::endl;
    std::cout << "statef = " << vehicle.get_final_state() << std::endl;

    return 1;
}