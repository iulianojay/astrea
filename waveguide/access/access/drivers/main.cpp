#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <stdio.h>

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
    using namespace waveguide;
    using namespace astro;
    using namespace accesslib;
    using namespace snapshot;
    using namespace sqlite_orm;

    // Setup system
    AstrodynamicsSystem sys;
    Date epoch = Date::now();

    // Query database
    auto snapshot = get_snapshot();
    // auto geoGp    = snapshot.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == 62455));
    auto geoGp = snapshot.get_all<SpaceTrackGP>(where(like(&SpaceTrackGP::OBJECT_NAME, "%%ARCTURUS%")));
    // auto everythingElseGps =
    //     snapshot.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::APOAPSIS) <= (geoGp[0].APOAPSIS.value() * 0.9)));
    auto everythingElseGps = snapshot.get_all<SpaceTrackGP>(where(like(&SpaceTrackGP::OBJECT_NAME, "%%STARLINK%")));

    // Build constellation
    Viewer geo(geoGp[0], sys);
    // Constellation<Viewer> allSats(everythingElseGps, sys);
    Constellation<Viewer> allSats(
        { everythingElseGps[0], everythingElseGps[1], everythingElseGps[2], everythingElseGps[3], everythingElseGps[4] }, sys
    );

    // Add sensors
    CircularFieldOfView fovGeo(15.0 * deg);
    CircularFieldOfView fovLeo(90.0 * deg);
    SensorParameters geoCone(&fovGeo);
    SensorParameters leoCone(&fovLeo);

    // for (auto& viewer : allSats | std::views::join) { // TODO: Figure out how this works
    //     viewer.attach(simpleCone);
    // }

    geo.attach(geoCone);
    for (auto& shell : allSats.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                // const State& state = sat.get_state();
                // sat.update_state(State(state.get_elements(), epoch, sys)); // Force inital epoch to match cause it's SLOW right now
                sat.attach(leoCone);
            }
        }
    }
    allSats.add_spacecraft(geo);

    // Build out grounds
    GroundStation dc(sys.get_center().get(), 38.895 * deg, -77.0366 * deg, 0.0 * km, { "Washington DC" });
    SensorParameters groundCone(&fovLeo);
    dc.attach(groundCone);
    GroundArchitecture grounds({ dc });

    LatLon corner1{ -50.0 * deg, -180.0 * deg };
    LatLon corner4{ 50.0 * deg, 180.0 * deg };
    Angle spacing = 10.0 * deg;
    Grid grid(sys.get_center().get(), corner1, corner4, GridType::UNIFORM, spacing);

    // Build EoMs
    TwoBody eom(sys);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Interval propInterval{ seconds(0), hours(24) };
    allSats.propagate(epoch, eom, integrator, propInterval);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << std::endl << std::endl << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    // Find access
    Time accessResolution = minutes(1.0);
    // const auto accesses   = find_accesses(allSats, accessResolution, epoch, sys);
    const auto accesses = find_accesses(allSats, grounds, accessResolution, epoch, sys);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << std::endl << std::endl << "Access Analysis Time: " << diff.count() / 1.0e9 << " (s)" << std::endl;

    // Save
    const std::string root        = std::getenv("WAVEGUIDE_ROOT");
    std::filesystem::path base    = root + "/waveguide/access/";
    std::filesystem::path outfile = base / "access/drivers/results/revisit.csv";
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    writer << std::vector<std::string>({ "Sender", "Receiver", "Rise - Set Times (s)" });
    for (const auto& [idPair, risesets] : accesses) {
        if (risesets.size() > 0) {

            // Gross
            std::string sender, receiver;
            for (const auto& shell : allSats.get_shells()) {
                for (const auto& plane : shell.get_planes()) {
                    for (const auto& viewer : plane.get_all_spacecraft()) {
                        if (viewer.get_id() == idPair.sender) { sender = viewer.get_name(); }
                        if (viewer.get_id() == idPair.receiver) { receiver = viewer.get_name(); }
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

    // Call plotter
    std::filesystem::path plotFile = base / "pyaccess/plots.py";
    const std::string cmd          = "python3 " + plotFile.string();
    int result                     = std::system(cmd.c_str());
}
