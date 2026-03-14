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
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

static const Time PROP_TIME         = months(1.0);
static const Time ACCESS_RESOLUTION = minutes(5.0);
static const bool PRINT_PROGRESS    = true;
static const Angle GRID_SPACING     = 5.0 * deg;


int arcturus_starlink_interference_test();
int iceye_test();

template <typename T, typename U>
AccessArray propagate_and_run_access_analysis(
    astro::Constellation<T>& constellation,
    U& grounds,
    const Date& startDate,
    const AstrodynamicsSystem& sys,
    const Time propTime,
    const Time accessResolution
);

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
    const AccessArray accesses = propagate_and_run_access_analysis(allSats, grid, startDate, sys, PROP_TIME, ACCESS_RESOLUTION);
    const AccessStats stats(accesses);

    // Save
    std::filesystem::path outdir = std::string(_TRACE_ROOT_) + "/trace/drivers/results/";

    save_risesets_to_file(accesses, outdir, allSats, grid);
    save_riseset_metrics_to_file(accesses, outdir, allSats, grid);
    save_receiver_riseset_metrics_to_file(stats, outdir, allSats, grid);
    save_access_metrics_to_file(stats, outdir, allSats, grid);
    save_number_of_folds_to_file(accesses, outdir, allSats, grid, ACCESS_RESOLUTION, PROP_TIME);

    // Call plotter
    std::filesystem::path plotFile = std::string(_TRACE_ROOT_) + "/pytrace/plots.py --outfile " + outdir.string() +
                                     " --target \"Washington DC\" --main \"ARCTURUS\"";
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
    // auto iceyeSats = snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%ICEYE-X61%%")));

    if (iceyeSats.size() == 0) {
        std::cerr << "No ICEYE satellites found in database!" << std::endl;
        return -1;
    }

    // Build constellation
    Constellation<Viewer> iceyeConstel(iceyeSats, sys);

    // Add sensors
    CircularFieldOfView fovLeo(15.0 * deg);
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
    SensorParameters groundCone(&fovLeo, astro::RADIAL_RIC);
    home.attach_payload(groundCone);

    LatLon corner1{ -90.0 * deg, -180.0 * deg };
    LatLon corner4{ 90.0 * deg, 180.0 * deg };
    Grid grid(sys.get_central_body().get(), corner1, corner4, GridType::UNIFORM, GRID_SPACING);

    // Propagate and find access
    const AccessArray accesses = propagate_and_run_access_analysis(iceyeConstel, grid, startDate, sys, PROP_TIME, ACCESS_RESOLUTION);
    const AccessStats stats(accesses);

    // Save
    std::filesystem::path outdir = std::string(_TRACE_ROOT_) + "/trace/drivers/results/iceye";

    save_risesets_to_file(accesses, outdir, iceyeConstel, grid);
    save_riseset_metrics_to_file(accesses, outdir, iceyeConstel, grid);
    save_receiver_riseset_metrics_to_file(stats, outdir, iceyeConstel, grid);
    save_access_metrics_to_file(stats, outdir, iceyeConstel, grid);
    save_number_of_folds_to_file(accesses, outdir, iceyeConstel, grid, ACCESS_RESOLUTION, PROP_TIME);

    // Call plotter
    std::filesystem::path plotFile = std::string(_TRACE_ROOT_) + "/pytrace/tracer.py " + outdir.string();
    const std::string cmd          = "python3 " + plotFile.string();
    std::cout << "Plotting results with command: \n\t" << cmd << std::endl;
    return std::system(cmd.c_str());
}

template <typename T, typename U>
AccessArray propagate_and_run_access_analysis(
    astro::Constellation<T>& constellation,
    U& grounds,
    const Date& startDate,
    const AstrodynamicsSystem& sys,
    const Time propTime,
    const Time accessResolution
)
{
    // Setup integrator
    J2MeanVop eom;
    Integrator integrator;
    integrator.set_timestep(accessResolution);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    const Date endDate = startDate + propTime;
    constellation.propagate(endDate, eom, integrator);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    if (PRINT_PROGRESS) {
        std::cout << std::endl << "Propagation Time: " << diff.count() / 1e9 << " (s)" << std::endl << std::endl;
    }
    start = std::chrono::steady_clock::now();

    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                // Check that state history is populated and has correct time frame
                const auto& stateHistory = sat.get_state_history();
                if (stateHistory.size() == 0) {
                    throw std::runtime_error("Error: State history not populated after propagation.");
                }
                if (stateHistory.first().get_epoch() > startDate) {
                    std::ostringstream oss;
                    oss << "Error: State history starts at the wrong time! Expected: " << startDate
                        << ", Actual: " << stateHistory.first().get_epoch();
                    throw std::runtime_error(oss.str());
                }
                if (stateHistory.last().get_epoch() != endDate) {
                    std::ostringstream oss;
                    oss << "Error: State history ends at the wrong time! Expected: " << endDate
                        << ", Actual: " << stateHistory.last().get_epoch();
                    throw std::runtime_error(oss.str());
                }
            }
        }
    }

    // Find access
    AccessAnalyzer analyzer(accessResolution, startDate, endDate, sys, true);
    const auto accesses = analyzer.find_accesses(constellation, grounds, true);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    if (PRINT_PROGRESS) {
        std::cout << std::endl
                  << std::endl
                  << "Access Analysis Time: " << diff.count() / 1.0e9 << " (s)" << std::endl
                  << std::endl;
    }

    return accesses;
}