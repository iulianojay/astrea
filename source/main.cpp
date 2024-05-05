#include <stdio.h>
#include <iostream>

#include "astro.hpp"

int main() {
    // Setup system
    AstrodynamicsSystem sys;

    // Build spacecraft
    element_array state0 = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    OrbitalElements elements0(state0, ElementSet::COE, &sys);
    Spacecraft vehicle(elements0, "Jan-01-2030 00:00:00.0");

    // Build Integrator
    Integrator integrator;
    LambertSolver lambertSolver;
    
    integrator.set_abs_tol(1.0e-8);
    integrator.set_rel_tol(1.0e-8);

    // Build EoMs
    EquationsOfMotion eom;
    eom.switch_dynamics("two body");

    // Integrate
    double statef[6];
    integrator.propagate(0, 86400.0, vehicle, eom);

    // Print
    std::cout << "state0 = [" << state0[0];
    for (int ii = 1; ii < 6; ii++) {
        std::cout << ", " << state0[ii];
    }
    std::cout << "]\n";

    std::cout << "statef = [" << statef[0];
    for (int ii = 1; ii < 6; ii++) {
        std::cout << ", " << statef[ii];
    }
    std::cout << "]\n";
}