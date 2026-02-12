/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <set>
#include <stdio.h>

#include <sqlite3.h>

#include <csv.hpp>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>
#include <snapshot/snapshot.hpp>

#include <trace/trace.hpp>
#include <trace/trace.macros.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;
using namespace snapshot;
using namespace sqlite_orm;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;

int arcturus_starlink_interference_test();
int iceye_test();


template <typename T, typename U>
AccessArray
    propagate_and_run_AccessAnalyzer(astro::Constellation<T>& constellation, U& grounds, const Date& startDate, const AstrodynamicsSystem& sys);

int main()
{
    // return arcturus_starlink_interference_test();
    return iceye_test();
}

int arcturus_starlink_interference_test()
{

    // Setup system
    AstrodynamicsSystem sys;
    Date startDate = Date::now();

    // Query database
    auto snapshot = get_snapshot();
    auto geoGp = snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%ARCTURUS%")));
    auto everythingElseGps =
        snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%STARLINK%")));


    if (geoGp.size() == 0 || everythingElseGps.size() == 0) {
        throw std::runtime_error("Error: Nothing pulled from database. Are you sure you filled it?");
    }

    // Build constellation
    Viewer geo(geoGp[0], sys);
    Constellation<Viewer> allSats(everythingElseGps, sys);

    // Add sensors
    CircularFieldOfView fovGeo(15.0 * deg);
    CircularFieldOfView fovLeo(90.0 * deg);
    SensorParameters geoCone(&fovGeo);
    SensorParameters leoCone(&fovLeo);

    // for (auto& viewer : allSats | std::views::join) { // TODO: Figure out how this works
    //     viewer.attach_payload(simpleCone);
    // }

    geo.attach_payload(geoCone);
    for (auto& shell : allSats.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(leoCone);
            }
        }
    }
    allSats.add_spacecraft(geo);

    // Build out grounds
    GroundStation dc(sys.get_central_body().get(), 38.895 * deg, -77.0366 * deg, 0.0 * km, { "Washington DC" });
    SensorParameters groundCone(
        &fovLeo,
        { 1.0 * m, // Anti-Nadir, units don't matter
          0.0 * m,
          0.0 * m }
    );
    dc.attach_payload(groundCone);

    LatLon corner1{ -50.0 * deg, -180.0 * deg };
    LatLon corner4{ 50.0 * deg, 180.0 * deg };
    Angle spacing = 10.0 * deg;
    Grid grid(sys.get_central_body().get(), corner1, corner4, GridType::UNIFORM, spacing);

    GroundArchitecture grounds({ dc });

    // Propagate and find access
    const AccessArray accesses = propagate_and_run_AccessAnalyzer(allSats, grounds, startDate, sys);

    // Save
    std::filesystem::path base           = std::string(_TRACE_ROOT_) + "/trace/drivers/results/";
    std::filesystem::path accessOutfile  = base / "revisit.csv";
    std::filesystem::path metricsOutfile = base / "metrics.csv";

    save_accesses_to_file(accesses, accessOutfile, allSats, grounds);
    save_access_metrics_to_file(accesses, metricsOutfile, allSats, grounds);

    // Call plotter
    std::filesystem::path plotFile = std::string(_TRACE_ROOT_) + "/pytrace/plots.py --outfile " +
                                     accessOutfile.string() + " --target \"Washington DC\" --main \"ARCTURUS\"";
    const std::string cmd = "python3 " + plotFile.string();

    std::cout << "Plotting results with command: " << cmd << std::endl;
    return std::system(cmd.c_str());
}


int iceye_test()
{
    // Setup system
    AstrodynamicsSystem sys;
    Date startDate = Date::now();

    // Query database
    auto snapshot = get_snapshot();
    auto iceyeSats = snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%ICEYE%%")));

    if (iceyeSats.size() == 0) {
        std::cerr << "No ICEYE satellites found in database!" << std::endl;
        return -1;
    }

    // Build constellation
    Constellation<Viewer> iceyeConstel(iceyeSats, sys);

    // Add sensors
    CircularFieldOfView fovLeo(30.0 * deg);
    SensorParameters leoCone(&fovLeo);

    for (auto& shell : iceyeConstel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(leoCone);
                // std::cout << sat.get_name() << " : " << sat.get_initial_state() << std::endl;
            }
        }
    }

    // Build out grounds
    GroundStation home(sys.get_central_body().get(), 60.1869 * deg, 24.8201 * deg, 0.0 * km, { "ICEYE Oy" });
    SensorParameters groundCone(
        &fovLeo,
        { 1.0 * m, // Anti-Nadir, units don't matter
          0.0 * m,
          0.0 * m }
    );
    home.attach_payload(groundCone);

    LatLon corner1{ -90.0 * deg, -180.0 * deg };
    LatLon corner4{ 90.0 * deg, 180.0 * deg };
    Angle spacing = 5.0 * deg;
    Grid grid(sys.get_central_body().get(), corner1, corner4, GridType::UNIFORM, spacing);

    // Propagate and find access
    const AccessArray accesses = propagate_and_run_AccessAnalyzer(iceyeConstel, grid, startDate, sys);

    // Save
    std::filesystem::path base           = std::string(_TRACE_ROOT_) + "/trace/drivers/results/iceye";
    std::filesystem::path accessOutfile  = base / "revisit.csv";
    std::filesystem::path metricsOutfile = base / "metrics.csv";

    save_accesses_to_file(accesses, accessOutfile, iceyeConstel, grid);
    save_access_metrics_to_file(accesses, metricsOutfile, iceyeConstel, grid);

    // Call plotter
    // std::filesystem::path plotFile = std::string(_TRACE_ROOT_) + "/pytrace/plots.py --outfile " +
    //                                  accessOutfile.string() + " --target \"ICEYE Oy\" --main \"ICEYE-X48\"";
    // const std::string cmd = "python3 " + plotFile.string();

    // std::cout << "Plotting results with command: " << cmd << std::endl;
    // return std::system(cmd.c_str());

    return 0;
}

template <typename T, typename U>
AccessArray propagate_and_run_AccessAnalyzer(astro::Constellation<T>& constellation, U& grounds, const Date& startDate, const AstrodynamicsSystem& sys)
{
    // Build EoMs
    J2MeanVop eom;

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    Time accessResolution = seconds(60.0);
    integrator.set_timestep(accessResolution);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    Time propTime = days(30.0);
    Date endDate  = startDate + propTime;
    constellation.propagate(endDate, eom, integrator);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << std::endl << std::endl << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl;

    start = std::chrono::steady_clock::now();

    // Find access
    AccessAnalyzer analyzer(accessResolution, startDate, endDate, sys);
    const auto accesses = analyzer.find_accesses(constellation, grounds, true);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << std::endl << std::endl << "Access Analysis Time: " << diff.count() / 1.0e9 << " (s)" << std::endl;

    return accesses;
}