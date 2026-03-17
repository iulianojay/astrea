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

int trace_analysis(const Time propTime, const Time accessResolution, const bool printProgress, const Angle gridSpacing);

template <typename T, typename U>
AccessArray propagate_and_run_access_analysis(
    astro::Constellation<T>& constellation,
    U& grounds,
    const Date& startDate,
    const AstrodynamicsSystem& sys,
    const Time propTime,
    const Time accessResolution,
    const bool printProgress
);

int main()
{
    const Time propTime         = months(3.0);
    const Time accessResolution = minutes(1.0);
    const bool printProgress    = true;
    const Angle gridSpacing     = 0.25 * deg;

    return trace_analysis(propTime, accessResolution, printProgress, gridSpacing);
}

int trace_analysis(const Time propTime, const Time accessResolution, const bool printProgress, const Angle gridSpacing)
{
    // Setup system
    AstrodynamicsSystem sys;
    Date startDate = Date::now();

    // Query database
    // auto snapshot = get_snapshot();
    // auto iceyeSats = snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%ICEYE%%")));
    // auto iceyeSats = snapshot.get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, "%%ICEYE-X61%%")));
    // if (iceyeSats.size() == 0) {
    //     std::cerr << "No ICEYE satellites found in database!" << std::endl;
    //     return -1;
    // }

    // Build constellation
    const Distance altitude      = 560.0 * km;
    const Distance semimajor     = altitude + sys.get_central_body()->get_equitorial_radius();
    const Angle inclination      = 97.6316 * deg; // roughly sunsync, whatever
    const std::size_t nSats      = 4;
    const std::size_t nPlanes    = 4;
    const Angle anchorRaan       = 20.0 * deg;
    const Angle anchorAnomaly    = 0.0 * deg;
    const Angle crossTrackOffset = 7.39 * deg; // 900 km off track
    const Angle phasing          = 7.39 * deg;
    Shell<Viewer> shell1(sys, startDate, semimajor, inclination, nSats, nPlanes, 1.0, anchorRaan, anchorAnomaly);
    Shell<Viewer> shell2(sys, startDate, semimajor, inclination, nSats, nPlanes, 1.0, anchorRaan + crossTrackOffset, anchorAnomaly - phasing);
    Shell<Viewer> shell3(sys, startDate, semimajor, inclination, nSats, nPlanes, 1.0, anchorRaan, anchorAnomaly - 2.0 * phasing);
    Constellation<Viewer> constellation({ shell1, shell2, shell3 });

    // Add sensors
    CircularFieldOfView fovLeo(30.0 * deg);
    SensorParameters leoCone(&fovLeo);
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            // const auto elements = plane.get_elements();
            // std::cout << "RAAN: " << elements.in_element_set<Keplerian>(sys.get_mu()).get_right_ascension().in(deg) << std::endl;
            for (auto& sat : plane.get_all_spacecraft()) {
                // const auto state = sat.get_state_history().first();
                // std::cout << "\t" << state;
                // const auto rEci = state.in_element_set<Cartesian>().get_position();
                // const auto lla  = Geodetic(rEci, startDate, sys.get_central_body().get());
                // std::cout << "-> Lon: " << lla.get_longitude().in(deg) << std::endl;
                sat.attach_payload(leoCone);
                sat.set_name("Sat " + std::to_string(sat.get_id()) + "(Cluster " + std::to_string(sat.get_id() % 3 + 1) + ")");
            }
        }
    }

    // Build out grounds
    // GroundStation home(sys.get_central_body().get(), 60.1869 * deg, 24.8201 * deg, 0.0 * km, { "ICEYE Oy" });
    // SensorParameters groundCone(&fovLeo, astro::RADIAL_RIC);
    // home.attach_payload(groundCone);

    // Polandish
    LatLon corner1{ 48.0 * deg, 14.0 * deg };
    LatLon corner4{ 55.0 * deg, 25.0 * deg };
    Grid grid(sys.get_central_body().get(), corner1, corner4, GridType::UNIFORM, gridSpacing);

    // Propagate and find access
    const AccessArray accesses =
        propagate_and_run_access_analysis(constellation, grid, startDate, sys, propTime, accessResolution, printProgress);
    const AccessStats stats(accesses);

    // Save
    std::filesystem::path outdir = std::string(_TRACE_ROOT_) + "/trace/drivers/results/poland/4_planes";

    save_risesets_to_file(accesses, outdir, constellation, grid);
    save_riseset_metrics_to_file(accesses, outdir, constellation, grid);
    save_receiver_riseset_metrics_to_file(stats, outdir, constellation, grid);
    save_access_metrics_to_file(stats, outdir, constellation, grid);
    save_number_of_folds_to_file(accesses, outdir, constellation, grid, accessResolution, propTime);

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
    const Time accessResolution,
    const bool printProgress
)
{
    // Setup integrator
    J2MeanVop eom;
    Integrator integrator;
    integrator.switch_fixed_timestep(true, accessResolution);

    // Propagate
    auto start = std::chrono::steady_clock::now();

    const Date endDate = startDate + propTime;
    constellation.propagate(endDate, eom, integrator);

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    if (printProgress) {
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

    if (printProgress) {
        std::cout << std::endl
                  << std::endl
                  << "Access Analysis Time: " << diff.count() / 1.0e9 << " (s)" << std::endl
                  << std::endl;
    }

    return accesses;
}