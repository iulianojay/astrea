#include <stdio.h>
#include <iostream>

#include "Spacecraft.hpp"

int main() {
    // Setup
    Spacecraft sc;
    double state0[6] = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    
    sc.set_abs_tol(1.0e-8);
    sc.set_rel_tol(1.0e-8);

    // Integrate
    double statef[6];
    sc.integrate(0, 86400.0, state0);
    sc.get_final_state(statef);

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