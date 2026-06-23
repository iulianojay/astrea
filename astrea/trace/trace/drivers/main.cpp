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

#include <trace/analysis/analysis.hpp>
#include <trace/trace.hpp>
#include <trace/trace.macros.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

using astrea::trace::TraceConfig;

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

    // Run analysis
    const auto result = run_trace_analysis(config);

    return 0;
}
