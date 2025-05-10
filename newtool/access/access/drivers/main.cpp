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

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <access/access.hpp>
#include <astro/astro.hpp>

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astro;
using namespace accesslib;

int main()
{

    // Setup system
    AstrodynamicsSystem sys("Earth", { "Earth", "Moon", "Sun", "Jupiter" });

    const OrbitalElements state(Keplerian{ 10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg });
    // const OrbitalElements cartesianState = conversions::convert(state, ElementSet::KEPLERIAN, ElementSet::CARTESIAN, sys);

    // Build constellation
    const int T    = 1;
    const int P    = 1;
    const double F = 1.0;
    Constellation<Viewer> walkerBall(10000.0 * km, 45.0 * deg, T, P, F);

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

    Interval propInterval{ std::chrono::seconds(0), std::chrono::years(1) };
    walkerBall.propagate(eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    Time accessResolution = std::chrono::minutes(5);
    find_accesses(walkerBall, accessResolution, sys);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Access Analysis Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    return 1;
}
