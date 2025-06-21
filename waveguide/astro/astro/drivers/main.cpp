#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>

// #include <arrow/api.h>
// #include <arrow/csv/api.h>
// #include <arrow/io/api.h>
// #include <arrow/ipc/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <iomanip>
#include <iostream>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

using namespace astro;

int main()
{

    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    // Setup system
    AstrodynamicsSystem sys; // Defaults to Earth-Moon
    // AstrodynamicsSystem sys("Earth", { "Earth", "Moon", "Sun", "Jupiter" });

    // const double R   = 10000;
    // const double V   = sqrt(398600.0 / 10000.0);
    // RadiusVector r   = { R * km, 0.0 * km, 0.0 * km };
    // VelocityVector v = { 0.0 * km / s, V * km / s, 0.0 * km / s };

    // Cartesian cart(r, v);
    // Keplerian kepl(cart, sys);
    // Cartesian cart2(kepl, sys);

    // OrbitalElements comp(cart);

    // comp.convert<Keplerian>(sys);

    const Keplerian state(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);

    // Build constellation
    const int T    = 100;
    const int P    = 10;
    const double F = 1.0;
    Constellation walkerBall(10000.0 * km, 45.0 * deg, T, P, F);

    // int count = 0; //TODO: Fix this. Comparitor doesn't work and iterates past end, for some reason
    // for (auto satIter = walkerBall.sat_begin(); satIter < walkerBall.sat_end(); ++satIter) {
    //     if (count == 100) {
    //         std::cout << "stop";
    //     }
    //     std::cout << "sat(" << count << ") id = " << (*satIter).get_id() << std::endl;
    //     ++count;
    // }

    // Build Force Model
    ForceModel forces;
    forces.add<AtmosphericForce>();
    forces.add<OblatenessForce>(sys, 10, 10);

    // Build EoMs
    // std::string propagator = "two_body";
    // TwoBody eom(sys);
    std::string propagator = "j2mean";
    J2MeanVop eom(sys);
    // std::string propagator = "cowells";
    // CowellsMethod eom(sys, forces);
    // std::string propagator = "coes";
    // KeplerianVop eom(sys, forces, false);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{ seconds(0), months(1) };
    walkerBall.propagate(eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

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
    std::filesystem::create_directories("./bin/results/" + propagator + "/");
    outfile.open("./bin/results/" + propagator + "/main.csv");
    outfile << "time (min),sma (km),ecc,inc (rad),raan (rad),w (rad),theta (rad)\n";
    auto vehicle = walkerBall.get_all_spacecraft()[0];
    for (auto& state : vehicle.get_states()) {
        outfile << state.time << ",";
        state.elements.convert<Keplerian>(sys);
        outfile << state.elements << "\n";
    }
    outfile.close();

    return 1;
}