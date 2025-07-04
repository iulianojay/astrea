#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stdio.h>

// #include <arrow/api.h>
// #include <arrow/csv/api.h>
// #include <arrow/io/api.h>
// #include <arrow/ipc/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>

#include <csv-parser/csv.hpp>
#include <nlohmann/json.hpp>

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

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;

using namespace astro;
using namespace accesslib;

void access_test();
void link_budget_test();

int main()
{
    access_test();
    return 1;
}


void access_test()
{
    using namespace astro;

    // Setup system
    AstrodynamicsSystem sys("Earth", { "Earth", "Moon", "Sun", "Jupiter" });

    const OrbitalElements state(Keplerian{ 10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg });
    // const OrbitalElements cartesianState = conversions::convert(state, ElementSet::KEPLERIAN, ElementSet::CARTESIAN, sys);

    // Build constellation
    const int T    = 100;
    const int P    = 10;
    const double F = 1.0;
    Constellation<Viewer> walkerBall(10000.0 * km, 45.0 * deg, T, P, F);

    // Add sensors
    CircularFieldOfView fov;
    Sensor simpleCone(fov);
    // for (auto& viewer : walkerBall | std::views::join) { // TODO: Figure out how this works
    //     viewer.attach_sensor(simpleCone);
    // }
    for (auto& shell : walkerBall) {
        for (auto& plane : shell) {
            for (auto& sat : plane) {
                sat.attach_sensor(simpleCone);
            }
        }
    }

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

    Interval propInterval{ seconds(0), days(1) };
    walkerBall.propagate(eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    // Find access
    Time accessResolution              = minutes(1);
    std::vector<Viewer> updatedViewers = find_accesses(walkerBall, accessResolution, sys);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Access Analysis Time: " << diff.count() / 1e9 / 60.0 << " (min)" << std::endl;

    // Save
    std::filesystem::path outfile = "/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.csv";
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile); // Can also use ofstream, etc.
    auto writer = csv::make_csv_writer(ss);

    writer << std::vector<std::string>({ "Sender ID", "Receiver ID", "Rise - Set Times (s)" });
    for (const auto& viewer : updatedViewers) {
        for (const auto& [idPair, risesets] : viewer.get_accesses()) {
            if (risesets.size() > 0) {
                std::vector<std::string> row{ std::to_string(idPair.sender), std::to_string(idPair.receiver) };
                for (const auto& str : risesets.to_string_vector()) {
                    row.push_back(str);
                }
                writer << row;
            }
        }
    }
}
