#include <stdio.h>
#include <iostream>
#include <fstream>

#include "astro.hpp"

int main() {
    // Setup system
    AstrodynamicsSystem sys;

    // Build spacecraft
    element_array state0 = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    OrbitalElements elements0(state0, ElementSet::COE);
    Spacecraft vehicle(elements0, "Jan-01-2030 00:00:00.0");

    // Build EoMs
    EquationsOfMotion eom(sys);
    // eom.switch_dynamics(EquationsOfMotion::TWO_BODY);
    eom.switch_dynamics(EquationsOfMotion::COWELLS);
    eom.switch_oblateness(10, 10);
    // eom.switch_drag(true);
    // eom.switch_lift(true);

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

    // Send to file
    std::ofstream outfile;
    outfile.open("./bin/results/cowells_test/main.csv");
    outfile << "time (min),sma (km),ecc,inc (deg),raan (deg),w (deg),theta (deg)\n";
    // outfile << "time (min),x (km),y (km),z (km),vx (km/s),vy (km/s),vz (km/s)\n";
    for (auto& state: vehicle.get_states()) {
        outfile << state.time.count<minutes>() << ",";
        // state.elements.convert(ElementSet::CARTESIAN, &sys);
        for (const auto& x: state.elements) {
            outfile << x << ",";
        }
        outfile << "\n";
    }
    outfile.close();

    return 1;
}