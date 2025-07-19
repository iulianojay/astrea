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

#include <sqlite3.h>

#include <csv-parser/csv.hpp>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <access/access.hpp>
#include <astro/astro.hpp>
#include <snapshot/snapshot.hpp>

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


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
    using namespace accesslib;
    using namespace snapshot;
    using namespace sqlite_orm;

    // Setup system
    AstrodynamicsSystem sys;
    Date epoch = Date::now();

    // Query database
    auto snapshot   = get_snapshot();
    auto geoGp      = snapshot.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == 62455));
    auto navStarGps = snapshot.get_all<SpaceTrackGP>(where(like(&SpaceTrackGP::OBJECT_NAME, "NAVSTAR%")));

    // Build constellation
    Viewer geo(geoGp[0], sys);
    Constellation<Viewer> allSats(navStarGps, sys);

    // Add sensors
    CircularFieldOfView fov1deg(180.0 * deg);
    CircularFieldOfView fov30deg(30.0 * deg);
    Sensor geoCone(fov1deg);
    Sensor navstarCone(fov30deg);
    // for (auto& viewer : allSats | std::views::join) { // TODO: Figure out how this works
    //     viewer.attach_sensor(simpleCone);
    // }

    geo.attach_sensor(geoCone);
    for (auto& shell : allSats) {
        for (auto& plane : shell) {
            for (auto& sat : plane) {
                const State& state = sat.get_state();
                sat.update_state(State(state.get_elements(), epoch, sys)); // Force inital epoch to match cause it's SLOW right now
                sat.attach_sensor(navstarCone);
            }
        }
    }
    allSats.add_spacecraft(geo);

    // Build out grounds
    GroundStation dc(38.895 * deg, -77.0366 * deg, 0.0 * km, { navstarCone }, "Washington DC");
    GroundArchitecture grounds({ dc });

    // Build EoMs
    TwoBody eom(sys);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{ seconds(0), days(2) };
    allSats.propagate(epoch, eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    // Find access
    Time accessResolution = minutes(1);
    const auto accesses   = find_accesses(allSats, accessResolution, sys);
    // const auto accesses   = find_accesses(allSats, grounds, accessResolution, epoch, sys);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Access Analysis Time: " << diff.count() / 1.0e9 << " (s)" << std::endl;

    // Save
    std::filesystem::path outfile = "/home/jay/projects/waveguide/waveguide/access/access/drivers/results/revisit.csv";
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile); // Can also use ofstream, etc.
    auto writer = csv::make_csv_writer(ss);

    writer << std::vector<std::string>({ "Sender", "Receiver", "Rise - Set Times (s)" });
    for (const auto& [idPair, risesets] : accesses) {
        if (risesets.size() > 0) {

            // Gross
            std::string sender, receiver;
            for (const auto& shell : allSats) {
                for (const auto& plane : shell) {
                    for (const auto& viewer : plane) {
                        if (viewer.get_id() == idPair.sender) {
                            sender = viewer.get_name() + "_" + std::to_string(viewer.get_id());
                        }
                        if (viewer.get_id() == idPair.receiver) {
                            receiver = viewer.get_name() + "_" + std::to_string(viewer.get_id());
                        }
                    }
                }
            }
            for (const auto& ground : grounds) {
                if (ground.get_id() == idPair.sender) { sender = ground.get_name(); }
                if (ground.get_id() == idPair.receiver) { receiver = ground.get_name(); }
            }

            std::vector<std::string> row{ sender, receiver };
            for (const auto& str : risesets.to_string_vector()) {
                row.push_back(str);
            }
            writer << row;
        }
    }
}
