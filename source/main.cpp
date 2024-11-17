#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

// #include <arrow/api.h>
// #include <arrow/csv/api.h>
// #include <arrow/io/api.h>
// #include <arrow/ipc/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>

#include <iostream>

#include "astro.hpp"

int main() {

    // Setup system
    AstrodynamicsSystem sys;

    // Build constellation
    const int T = 1;
    const int P = 1;
    const double F = 1.0;
    Constellation walkerBall(10000.0, 45.0, T, P, F);

    // Print to ensure proper build
    // std::cout << "Walker: [" << T << ", " << P << ", " << F << "]" << std::endl;
    // for (auto& shell : walkerBall) {
    //     std::cout << "Shell: " << shell.get_id() << std::endl;
    //     for (auto& plane : shell) {
    //         std::cout << "\tPlane: " << plane.get_id() << std::endl;
    //         for (auto& sat : plane) {
    //             std::cout << "\t\tSat: " << sat.get_id() << std::endl;
    //         }
    //     }
    // }
    // std::cout << std::endl;

    // int count = 0; //TODO: Fix this. Comparitor doesn't work and iterates past end, for some reason
    // for (auto satIter = walkerBall.sat_begin(); satIter < walkerBall.sat_end(); ++satIter) {
    //     if (count == 100) {
    //         std::cout << "stop";
    //     }
    //     std::cout << "sat(" << count << ") id = " << (*satIter).get_id() << std::endl;
    //     ++count;
    // }

    // Build EoMs
    EquationsOfMotion eom(sys);
    eom.switch_dynamics(EquationsOfMotion::J2_MEAN);
    // eom.switch_oblateness(10, 10);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-13);
    integrator.set_rel_tol(1.0e-13);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{seconds(0), years(1)};
    walkerBall.propagate(eom, integrator, propInterval);

    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Propagation Time: " << diff.count()/1e9 << " (s)" << std::endl;

    // Access
    // start = std::chrono::steady_clock::now();

    // Time accessResolution = minutes(5);
    // find_accesses(walkerBall, accessResolution, &sys);

    // end = std::chrono::steady_clock::now();
    // diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // std::cout << "Access Analysis Time: " << diff.count()/1e9 << " (s)" << std::endl;

    // Check propagation
    // std::cout << "\n\n" << "Walker: [" << T << ", " << P << ", " << F << "]" << std::endl;
    // for (auto& shell : walkerBall) {
    //     std::cout << "Shell: " << shell.get_id() << std::endl;
    //     for (auto& plane : shell) {
    //         std::cout << "\tPlane: " << plane.get_id() << std::endl;
    //         for (auto& sat : plane) {
    //             std::cout << "\t\tSat: " << sat.get_id() << std::endl;
    //             std::cout << "\t\tstate0 = " << sat.get_initial_state() << std::endl;
    //             std::cout << "\t\tstatef = " << sat.get_final_state() << std::endl << std::endl;
    //         }
    //     }
    // }

    // Send to file
    std::ofstream outfile;
    std::filesystem::create_directories("./bin/results/cowells/");
    outfile.open("./bin/results/cowells/main.csv");
    outfile << "time (min),sma (km),ecc,inc (deg),raan (deg),w (deg),theta (deg)\n";
    // outfile << "time (min),x (km),y (km),z (km),vx (km/s),vy (km/s),vz (km/s)\n";
    auto vehicle = walkerBall.get_all_spacecraft()[0];
    for (auto& state: vehicle.get_states()) {
        outfile << state.time.count<minutes>() << ",";
        state.elements.convert(ElementSet::COE, sys);
        for (const auto& x: state.elements) {
            outfile << x << ",";
        }
        outfile << "\n";
    }
    outfile.close();

    return 1;
}
