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

#include <trace/analysis/analysis.hpp>

#include <chrono>
#include <iostream>
#include <sstream>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

#include <trace/analysis/AccessAnalyzer.hpp>
#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/io/output.hpp>
#include <trace/platforms/ground/Grid.hpp>
#include <trace/platforms/sensors/fov/CircularFieldOfView.hpp>
#include <trace/platforms/vehicles/Viewer.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/trace.macros.hpp>
#include <trace/types/typedefs.hpp>

using namespace astrea;
using namespace astro;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;
using std::chrono::nanoseconds;

namespace astrea {
namespace trace {

template <typename T, typename U>
static AccessArray propagate_and_run_access_analysis(
    astro::Constellation<T>& constellation,
    U& grounds,
    const Date& startDate,
    const Time propTime,
    const Time accessResolution,
    const bool printProgress
)
{
    // Setup integrator
    J2MeanVop eom;
    Integrator integrator;
    integrator.set_equations_of_motion(eom);
    integrator.switch_fixed_timestep(true, accessResolution);

    // Propagate
    auto start         = std::chrono::steady_clock::now();
    const Date endDate = startDate + propTime;
    constellation.propagate(endDate, integrator);
    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    if (printProgress) { std::cout << "\nPropagation Time: " << diff.count() / 1e9 << " (s)\n\n"; }
    start = std::chrono::steady_clock::now();

    // Validate state histories
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                auto& stateHistory = sat.get_state_history();
                stateHistory.template convert_to_set<Cartesian<frames::primary>>();
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
    AccessAnalyzer analyzer(accessResolution, startDate, endDate, true);
    const AccessArray accesses = analyzer.find_accesses(constellation, grounds, true);

    end  = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<nanoseconds>(end - start);

    if (printProgress) { std::cout << "\nAccess Analysis Time: " << diff.count() / 1.0e9 << " (s)\n\n"; }

    return accesses;
}

AnalysisResult run_trace_analysis(const TraceConfig& config)
{
    const Date startDate = Date::now();

    // Build 3-shell Walker constellation
    const Distance altitude   = config.altitudeKm * km;
    const Distance semimajor  = altitude + get_equitorial_radius<planets::Earth>();
    const Angle inclination   = config.inclinationDeg * deg;
    const Angle anchorRaan    = config.anchorRaanDeg * deg;
    const Angle anchorAnomaly = 0.0 * deg;
    const Angle crossTrack    = config.crossTrackOffsetDeg * deg;
    const Angle phasing       = config.phasingDeg * deg;

    // Shell<Viewer> shell1(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan, anchorAnomaly);
    // Shell<Viewer> shell2(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan + crossTrack, anchorAnomaly - phasing);
    // Shell<Viewer> shell3(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan, anchorAnomaly - 2.0 * phasing);
    Constellation<Viewer> constellation(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan, anchorAnomaly);

    // Attach sensors
    CircularFieldOfView fovShape(config.fovHalfAngleDeg * deg);
    SensorParameters sensor(&fovShape);
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(sensor);
            }
        }
    }

    // Build grid — LatLon is (latitude, longitude)
    LatLon corner1{ config.llLat * deg, config.llLon * deg };
    LatLon corner4{ config.urLat * deg, config.urLon * deg };
    Grid<astro::planets::Earth> grid(corner1, corner4, GridType::UNIFORM, config.gridSpacingDeg * deg);

    // Propagate + access analysis
    const Time propTime         = days(config.simTimeDays);
    const Time accessResolution = minutes(config.resolutionMin);

    const AccessArray accesses =
        propagate_and_run_access_analysis(constellation, grid, startDate, propTime, accessResolution, config.printProgress);

    const AnalysisResult results{ accesses, AccessStats(accesses), FoldsOfCoverage(accesses, accessResolution, propTime) };

    // Save results
    if (!config.saveResults) { return results; }

    const std::filesystem::path outdir =
        config.outdir.empty() ? std::filesystem::path(std::string(_TRACE_ROOT_) + "/trace/drivers/results/global") :
                                std::filesystem::path(config.outdir);
    std::filesystem::create_directories(outdir);
    const std::filesystem::path dbPath = outdir / config.dbName;

    if (config.printProgress) { std::cout << "Saving results to: " << dbPath << std::endl; }
    DatabaseOutputManager manager(dbPath, true);
    manager.save_results(results.folds, results.stats, results.accesses, constellation, grid);
    manager.save_ground_track(constellation, startDate, startDate + propTime, accessResolution);

    // Call plotter
    if (config.runPlotter) {
        const std::string cmd = "python3 " + std::string(_TRACE_ROOT_) + "/pytrace/tracer.py " + outdir.string();
        if (config.printProgress) { std::cout << "Plotting: " << cmd << std::endl; }
        const auto exitCode = std::system(cmd.c_str());
        if (exitCode != 0) { std::cerr << "Error: Plotter exited with code " << exitCode << std::endl; }
    }

    return results;
}

} // namespace trace
} // namespace astrea