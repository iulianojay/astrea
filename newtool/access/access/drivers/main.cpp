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

#include <iostream>

#include <access/access.hpp>
#include <astro/astro.hpp>

int main()
{

    // Setup system
    AstrodynamicsSystem sys("Earth", { "Earth", "Moon", "Sun", "Jupiter" });

    const OrbitalElements state({ 10000.0, 0.0, 45.0, 0.0, 0.0, 0.0 }, ElementSet::KEPLERIAN);
    // const OrbitalElements cartesianState = conversions::convert(state, ElementSet::KEPLERIAN, ElementSet::CARTESIAN, sys);

    // Build constellation
    const int T    = 1;
    const int P    = 1;
    const double F = 1.0;
    Constellation<Viewer> walkerBall(10000.0, 45.0, T, P, F);

    // Build Force Model
    ForceModel forces;
    forces.add<AtmosphericForce>();
    forces.add<OblatenessForce>(sys, 10, 10);
    forces.add<NBodyForce>();

    // Build EoMs
    std::string propagator = "j2mean";
    J2MeanVop eom(sys);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{ seconds(0), years(1) };
    walkerBall.propagate(eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    Time accessResolution = minutes(5);
    find_accesses(walkerBall, accessResolution, sys);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Access Analysis Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    return 1;
}
