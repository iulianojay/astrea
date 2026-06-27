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
#include <utilities/StopWatch.hpp>

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
static AccessArray
    propagate_and_run_access_analysis(astro::Constellation<T>& constellation, U& grounds, const Date& epoch, const Time propTime, const Time accessResolution, const bool printProgress)
{
    // Setup integrator
    J2MeanVop eom;
    Integrator integrator;
    integrator.set_equations_of_motion(eom);
    integrator.switch_fixed_timestep(true, accessResolution);

    // Propagate
    if (printProgress) { std::cout << std::endl << "[trace] Propagating..." << std::endl; }

    utilities::StopWatch watch;
    const Date endDate = epoch + propTime;
    constellation.propagate(endDate, integrator);

    if (printProgress) { std::cout << "[trace] Propagation Time: " << watch.measure() << std::endl; }

    // Validate state histories
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                auto& stateHistory = sat.get_state_history();
                stateHistory.template convert_to_set<Cartesian<frames::primary>>();
                if (stateHistory.size() == 0) {
                    throw std::runtime_error("[trace] Error: State history not populated after propagation.");
                }
                if (stateHistory.first().get_epoch() > epoch) {
                    std::ostringstream oss;
                    oss << "[trace] Error: State history starts at the wrong time! Expected: " << epoch
                        << ", Actual: " << stateHistory.first().get_epoch();
                    throw std::runtime_error(oss.str());
                }
                if (stateHistory.last().get_epoch() != endDate) {
                    std::ostringstream oss;
                    oss << "[trace] Error: State history ends at the wrong time! Expected: " << endDate
                        << ", Actual: " << stateHistory.last().get_epoch();
                    throw std::runtime_error(oss.str());
                }
            }
        }
    }

    // Find access
    if (printProgress) { std::cout << "[trace] Running Access Analysis..." << std::endl; }

    watch.reset();
    AccessAnalyzer analyzer(accessResolution, epoch, endDate, true);
    const AccessArray accesses = analyzer.find_accesses(constellation, grounds, true);

    if (printProgress) { std::cout << "[trace] Access Analysis Time: " << watch.measure() << std::endl; }

    return accesses;
}

AnalysisResult run_trace_analysis(const TraceConfig& config)
{
    // Unpack settings
    const auto analysisSettings      = config.analysisSettings;
    const auto constellationSettings = config.constellationSettings;
    const auto sensorSettings        = config.sensorSettings;
    const auto groundSettings        = config.groundSettings;
    const auto outputSettings        = config.outputSettings;

    // Propagate + access analysis
    const Time propTime         = analysisSettings.simTime;
    const Time accessResolution = analysisSettings.resolution;
    const Date epoch            = analysisSettings.epoch;

    // Build 3-shell Walker constellation
    const Distance altitude   = constellationSettings.altitude;
    const Distance semimajor  = altitude + get_equitorial_radius<planets::Earth>();
    const Angle inclination   = constellationSettings.inclination;
    const std::size_t nSats   = constellationSettings.nSats;
    const std::size_t nPlanes = constellationSettings.nPlanes;
    const Unitless phasing    = constellationSettings.phasing;
    const Angle anchorRaan    = constellationSettings.anchorRaan;
    const Angle anchorAnomaly = constellationSettings.anchorTrueAnomaly;

    Constellation<Viewer> constellation(epoch, semimajor, inclination, nSats, nPlanes, phasing, anchorRaan, anchorAnomaly);

    // Attach sensors
    CircularFieldOfView fovShape(sensorSettings.halfConeAngle);
    SensorParameters sensor(&fovShape);
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(sensor);
            }
        }
    }

    // Build grid — LatLon is (latitude, longitude)
    Grid<astro::planets::Earth> grid(
        groundSettings.gridSettings.latRange,
        groundSettings.gridSettings.lonRange,
        GridType::UNIFORM,
        groundSettings.gridSettings.spacing
    );

    // Run the access analysis
    const bool printProgress = outputSettings.printProgress;
    const AccessArray accesses =
        propagate_and_run_access_analysis(constellation, grid, epoch, propTime, accessResolution, printProgress);

    const AnalysisResult results{ accesses, AccessStats(accesses), FoldsOfCoverage(accesses, accessResolution, propTime) };

    // Save results
    if (outputSettings.saveResults) {
        utilities::StopWatch watch;

        const std::filesystem::path outdir = std::filesystem::path(outputSettings.outdir);
        std::filesystem::create_directories(outdir);

        const std::filesystem::path dbPath = outdir / outputSettings.dbName;
        if (printProgress) { std::cout << "[trace] Saving results to: " << dbPath << std::endl; }

        DatabaseOutputManager manager(dbPath, true);
        manager.save_results(results.folds, results.stats, results.accesses, constellation, grid);
        manager.save_ground_track(constellation, epoch, epoch + propTime, accessResolution);

        if (printProgress) { std::cout << "[trace] Save Time: " << watch.measure() << std::endl; }

        // Call plotter
        if (outputSettings.runPlotter) {
            watch.reset();
            const std::string cmd = "python3 " + std::string(_TRACE_ROOT_) + "/pytrace/tracer.py " + outdir.string();
            if (printProgress) { std::cout << "[trace] Plotting: " << cmd << std::endl; }

            const auto exitCode = std::system(cmd.c_str());

            if (exitCode != 0) { std::cerr << "[trace] Error: Plotter exited with code " << exitCode << std::endl; }
            if (printProgress) { std::cout << "[trace] Plotting Time: " << watch.measure() << std::endl; }
        }
    }

    return results;
}

} // namespace trace
} // namespace astrea