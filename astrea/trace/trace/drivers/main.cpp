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
#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <string_view>

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

// ---------------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------------

struct TraceConfig {
    // Simulation timing
    double simTimeDays   = 30.0;
    double resolutionMin = 1.0;

    // Constellation (3-shell Walker)
    double altitudeKm          = 560.0;
    double inclinationDeg      = 97.6316;
    std::size_t nSats          = 1; // satellites per plane
    std::size_t nPlanes        = 1; // planes per shell
    double anchorRaanDeg       = 0.0;
    double crossTrackOffsetDeg = 0.0; // RAAN offset between shells 1 and 2
    double phasingDeg          = 0.0; // true-anomaly phasing between shells

    // Sensor
    double fovHalfAngleDeg = 30.0;

    // Ground grid
    double gridSpacingDeg = 5.0;
    double llLon          = -180.0; // LatLon first  arg = longitude (see LatLon convention)
    double llLat          = -90.0;  // LatLon second arg = latitude
    double urLon          = 180.0;
    double urLat          = 90.0;

    // Output
    std::string outdir = ""; // empty -> default to <TRACE_ROOT>/trace/drivers/results/global
    std::string dbName = "analysis.db";

    // Flags
    bool printProgress = false;
    bool runPlotter    = true;

    TraceConfig() = default;

    explicit TraceConfig(const nlohmann::json& json)
    {
        simTimeDays         = json.value("sim_time_days", simTimeDays);
        resolutionMin       = json.value("resolution_min", resolutionMin);
        altitudeKm          = json.value("altitude_km", altitudeKm);
        inclinationDeg      = json.value("inclination_deg", inclinationDeg);
        nSats               = json.value("n_sats", nSats);
        nPlanes             = json.value("n_planes", nPlanes);
        anchorRaanDeg       = json.value("anchor_raan_deg", anchorRaanDeg);
        crossTrackOffsetDeg = json.value("cross_track_offset_deg", crossTrackOffsetDeg);
        phasingDeg          = json.value("phasing_deg", phasingDeg);
        fovHalfAngleDeg     = json.value("fov_half_angle_deg", fovHalfAngleDeg);
        gridSpacingDeg      = json.value("grid_spacing_deg", gridSpacingDeg);
        llLon               = json.value("ll_lon", llLon);
        llLat               = json.value("ll_lat", llLat);
        urLon               = json.value("ur_lon", urLon);
        urLat               = json.value("ur_lat", urLat);
        outdir              = json.value("outdir", outdir);
        dbName              = json.value("db_name", dbName);
        printProgress       = json.value("print_progress", printProgress);
        runPlotter          = json.value("run_plotter", runPlotter);
    }
};

// ---------------------------------------------------------------------------
// CLI helpers
// ---------------------------------------------------------------------------

static void print_usage(const char* prog)
{
    // clang-format off
    std::cout <<
        "Usage: " << prog << " [OPTIONS]\n"
        "\n"
        "Timing:\n"
        "  --sim-time   <days>   Simulation duration            (default: 30)\n"
        "  --resolution <min>    Access check resolution        (default: 1)\n"
        "\n"
        "Constellation (3-shell Walker):\n"
        "  --altitude    <km>    Orbital altitude               (default: 560)\n"
        "  --inclination <deg>   Inclination                    (default: 97.6316)\n"
        "  --n-sats      <n>     Satellites per plane           (default: 1)\n"
        "  --n-planes    <n>     Planes per shell               (default: 1)\n"
        "  --raan        <deg>   Anchor RAAN (shell 1)          (default: 0)\n"
        "  --cross-track <deg>   RAAN offset for shell 2        (default: 0)\n"
        "  --phasing     <deg>   True-anomaly phasing/shell     (default: 0)\n"
        "\n"
        "Sensor:\n"
        "  --fov <deg>           Half-cone angle                (default: 30)\n"
        "\n"
        "Grid:\n"
        "  --grid-spacing <deg>  Grid resolution                (default: 5)\n"
        "  --ll-lon <deg>        Lower-left  longitude          (default: -180)\n"
        "  --ll-lat <deg>        Lower-left  latitude           (default: -90)\n"
        "  --ur-lon <deg>        Upper-right longitude          (default: 180)\n"
        "  --ur-lat <deg>        Upper-right latitude           (default: 90)\n"
        "\n"
        "Output:\n"
        "  --outdir  <path>      Results directory              (default: <trace_root>/results/global)\n"
        "  --db-name <name>      Database filename              (default: analysis.db)\n"
        "\n"
        "Config:\n"
        "  --config  <path>      Load defaults from JSON file (overridden by CLI flags)\n"
        "\n"
        "Flags:\n"
        "  --no-progress         Suppress progress output\n"
        "  --no-plot             Skip Python plotting step\n"
        "  --help                Show this message\n";
    // clang-format on
}

/// Returns false and sets @p error on bad input; handles --help by printing and exiting.
static bool parse_args(int argc, char* argv[], TraceConfig& config, std::string& error)
{
    auto next_val = [&](int i, int argc_, char* argv_[], std::string_view flag) -> std::string {
        if (i + 1 >= argc_) {
            error = std::string(flag) + " requires a value";
            return "";
        }
        return argv_[i + 1];
    };

    for (int i = 1; i < argc; ++i) {
        const std::string_view arg = argv[i];

        // --- JSON config file (processed before remaining flags) ---
        if (arg == "--config") {
            const std::string path = next_val(i, argc, argv, arg);
            if (!error.empty()) return false;
            std::ifstream f(path);
            if (!f) {
                error = "Cannot open config file: " + path;
                return false;
            }
            try {
                config = TraceConfig(nlohmann::json::parse(f));
            }
            catch (const std::exception& e) {
                error = std::string("JSON parse error: ") + e.what();
                return false;
            }
            ++i;
            continue;
        }

        // --- boolean flags ---
        if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            std::exit(0);
        }
        if (arg == "--no-progress") {
            config.printProgress = false;
            continue;
        }
        if (arg == "--no-plot") {
            config.runPlotter = false;
            continue;
        }

        // --- key-value options ---
        const std::string str = next_val(i, argc, argv, arg);
        if (!error.empty()) return false;

        try {
            if (arg == "--sim-time") { config.simTimeDays = std::stod(str); }
            else if (arg == "--resolution") {
                config.resolutionMin = std::stod(str);
            }
            else if (arg == "--altitude") {
                config.altitudeKm = std::stod(str);
            }
            else if (arg == "--inclination") {
                config.inclinationDeg = std::stod(str);
            }
            else if (arg == "--n-sats") {
                config.nSats = std::stoul(str);
            }
            else if (arg == "--n-planes") {
                config.nPlanes = std::stoul(str);
            }
            else if (arg == "--raan") {
                config.anchorRaanDeg = std::stod(str);
            }
            else if (arg == "--cross-track") {
                config.crossTrackOffsetDeg = std::stod(str);
            }
            else if (arg == "--phasing") {
                config.phasingDeg = std::stod(str);
            }
            else if (arg == "--fov") {
                config.fovHalfAngleDeg = std::stod(str);
            }
            else if (arg == "--grid-spacing") {
                config.gridSpacingDeg = std::stod(str);
            }
            else if (arg == "--ll-lon") {
                config.llLon = std::stod(str);
            }
            else if (arg == "--ll-lat") {
                config.llLat = std::stod(str);
            }
            else if (arg == "--ur-lon") {
                config.urLon = std::stod(str);
            }
            else if (arg == "--ur-lat") {
                config.urLat = std::stod(str);
            }
            else if (arg == "--outdir") {
                config.outdir = str;
            }
            else if (arg == "--db-name") {
                config.dbName = str;
            }
            else {
                error = "Unknown option: " + std::string(arg);
                return false;
            }
            ++i; // consume the value token
        }
        catch (const std::exception& e) {
            error = "Invalid value for " + std::string(arg) + ": " + e.what();
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------

int trace_analysis(const TraceConfig& config);

template <typename T, typename U>
AccessArray propagate_and_run_access_analysis(
    astro::Constellation<T>& constellation,
    U& grounds,
    const Date& startDate,
    const Time propTime,
    const Time accessResolution,
    const bool printProgress
);

// ---------------------------------------------------------------------------
// Entry point
// ---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    TraceConfig config;
    std::string error;
    if (!parse_args(argc, argv, config, error)) {
        std::cerr << "Error: " << error << "\n";
        print_usage(argv[0]);
        return 1;
    }
    return trace_analysis(config);
}

// ---------------------------------------------------------------------------
// Core analysis
// ---------------------------------------------------------------------------

int trace_analysis(const TraceConfig& config)
{
    // Setup system
    Date startDate = Date::now();

    // Build constellation
    const Distance altitude      = config.altitudeKm * km;
    const Distance semimajor     = altitude + get_equitorial_radius<planets::Earth>();
    const Angle inclination      = config.inclinationDeg * deg;
    const Angle anchorRaan       = config.anchorRaanDeg * deg;
    const Angle anchorAnomaly    = 0.0 * deg;
    const Angle crossTrackOffset = config.crossTrackOffsetDeg * deg;
    const Angle phasing          = config.phasingDeg * deg;

    Shell<Viewer> shell1(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan, anchorAnomaly);
    Shell<Viewer> shell2(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan + crossTrackOffset, anchorAnomaly - phasing);
    Shell<Viewer> shell3(startDate, semimajor, inclination, config.nSats, config.nPlanes, 1.0, anchorRaan, anchorAnomaly - 2.0 * phasing);
    Constellation<Viewer> constellation({ shell1, shell2, shell3 });

    // Attach sensors
    CircularFieldOfView fovLeo(config.fovHalfAngleDeg * deg);
    SensorParameters leoCone(&fovLeo);
    for (auto& shell : constellation.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(leoCone);
                sat.set_name("Sat " + std::to_string(sat.get_id()) + "(Cluster " + std::to_string(sat.get_id() % 3 + 1) + ")");
            }
        }
    }

    // Build grid
    // LatLon convention: first arg = longitude, second arg = latitude
    LatLon corner1{ config.llLon * deg, config.llLat * deg };
    LatLon corner4{ config.urLon * deg, config.urLat * deg };
    const Angle gridSpacing = config.gridSpacingDeg * deg;
    Grid<astro::planets::Earth> grid(corner1, corner4, GridType::UNIFORM, gridSpacing);

    // Propagate and find access
    const Time propTime         = days(config.simTimeDays);
    const Time accessResolution = minutes(config.resolutionMin);

    const AccessArray accesses =
        propagate_and_run_access_analysis(constellation, grid, startDate, propTime, accessResolution, config.printProgress);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, accessResolution, propTime);

    // Save results
    const std::filesystem::path outdir =
        config.outdir.empty() ? std::filesystem::path(std::string(_TRACE_ROOT_) + "/trace/drivers/results/global") :
                                std::filesystem::path(config.outdir);
    std::filesystem::create_directories(outdir);
    const std::filesystem::path dbPath = outdir / config.dbName;

    if (config.printProgress) { std::cout << "Saving results to: " << dbPath << std::endl; }
    DatabaseOutputManager manager(dbPath, true);
    manager.save_results(folds, stats, accesses, constellation, grid);

    // Call plotter
    if (config.runPlotter) {
        const std::string cmd = "python3 " + std::string(_TRACE_ROOT_) + "/pytrace/tracer.py " + outdir.string();
        if (config.printProgress) { std::cout << "Plotting: " << cmd << std::endl; }
        return std::system(cmd.c_str());
    }

    return 0;
}

template <typename T, typename U>
AccessArray propagate_and_run_access_analysis(
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
    auto start = std::chrono::steady_clock::now();

    const Date endDate = startDate + propTime;
    constellation.propagate(endDate, integrator);

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
