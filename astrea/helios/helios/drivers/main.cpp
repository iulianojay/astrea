/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <omp.h>

#include <webui.hpp>

#include <units/units.hpp>

#include <astro/astro.hpp>
#include <snapshot/http-queries/spacetrack/SpaceTrackClient.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using namespace astrea::snapshot;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace {

struct Point3 {
    double x;
    double y;
    double z;
};

struct PropagationResult {
    std::vector<std::vector<Point3>> frames; // frames[frameIdx][objectIdx]
    std::size_t numFrames = 0;
    double elapsedMs      = 0.0;
    double maxRadiusKm    = 0.0;
};

// Parses a .env file of KEY=VALUE lines (# comments and blank lines ignored).
// Looks for the file next to the executable, then in the current working directory.
std::unordered_map<std::string, std::string> load_env_file(const std::string& execPath)
{
    std::unordered_map<std::string, std::string> env;

    // Build candidate paths: beside the binary, then cwd
    const std::string dir                     = execPath.substr(0, execPath.find_last_of("/\\") + 1);
    const std::vector<std::string> candidates = { dir + ".env", ".env" };

    std::ifstream file;
    for (const auto& path : candidates) {
        file.open(path);
        if (file.is_open()) {
            std::cout << "[helios] Loading credentials from " << path << "\n";
            break;
        }
    }
    if (!file.is_open()) { return env; }

    std::string line;
    while (std::getline(file, line)) {
        // Strip carriage return
        if (!line.empty() && line.back() == '\r') { line.pop_back(); }
        // Skip blanks and comments
        if (line.empty() || line.front() == '#') { continue; }
        const auto eq = line.find('=');
        if (eq == std::string::npos) { continue; }
        std::string key   = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        // Strip optional surrounding quotes from value
        if (value.size() >= 2 &&
            ((value.front() == '"' && value.back() == '"') || (value.front() == '\'' && value.back() == '\''))) {
            value = value.substr(1, value.size() - 2);
        }
        env[key] = value;
    }
    return env;
}

std::vector<GeneralPerturbations> fetch_active_gp(const std::string& username, const std::string& password)
{
    SpaceTrackClient client;
    // All on-orbit objects: decay_date=null-val (still flying), epoch within last 30 days.
    // Field names must be lowercase to match SpaceTrack URL path format.
    nlohmann::json response;
    try {
        response = client.query(
            username,
            password,
            SpaceTrackClient::Controller::BASIC_SPACE_DATA,
            SpaceTrackClient::Action::QUERY,
            SpaceTrackClient::SpaceDataClass::GP,
            { { "decay_date", "null-val" }, { "epoch", "%3Enow-30" }, { "orderby", "norad_cat_id" }, { "format", "json" } }
        );
    }
    catch (const std::exception& e) {
        std::cerr << "[helios] SpaceTrack query failed: " << e.what() << "\n";
        return {};
    }

    std::vector<GeneralPerturbations> result;
    result.reserve(response.size());
    for (const auto& entry : response) {
        try {
            GeneralPerturbations gp(entry);
            if (!gp.SEMIMAJOR_AXIS || !gp.ECCENTRICITY || !gp.INCLINATION || !gp.RA_OF_ASC_NODE ||
                !gp.ARG_OF_PERICENTER || !gp.MEAN_ANOMALY) {
                continue;
            }
            result.push_back(std::move(gp));
        }
        catch (...) {
        }
    }
    std::cout << "[helios] Fetched " << result.size() << " active GP records from SpaceTrack\n";
    return result;
}

PropagationResult propagate_many_objects(const std::vector<GeneralPerturbations>& gpObjects, const Time& propTime, const Time& stepTime)
{
    struct SimpleVehicle {
        Mass get_mass() const { return 1000.0 * kg; }
    };

    const std::size_t numExpectedFrames =
        static_cast<std::size_t>(propTime.numerical_value_in(s) / stepTime.numerical_value_in(s)) + 1;

    const std::size_t objectCount = gpObjects.size();
    PropagationResult result;
    result.numFrames = numExpectedFrames;
    result.frames.assign(numExpectedFrames, std::vector<Point3>(objectCount, { 0.0, 0.0, 0.0 }));

    const auto start = std::chrono::steady_clock::now();

    double maxRadius = 0.0;

#pragma omp parallel reduction(max : maxRadius)
    {
        Integrator integrator;
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);
        integrator.switch_fixed_timestep(true, stepTime);

        struct SimpleVehicle {
            Mass get_mass() const { return 1000.0 * kg; }
        };
        Vehicle vehicle{ SimpleVehicle{} };

#pragma omp for schedule(dynamic, 64)
        for (std::size_t i = 0; i < objectCount; ++i) {
            try {
                Spacecraft sc(gpObjects[i]);
                const State state0         = sc.get_initial_state();
                const StateHistory history = integrator.propagate(state0, propTime, vehicle);

                std::size_t frameIdx = 0;
                for (const auto& state : history) {
                    if (frameIdx >= numExpectedFrames) break;
                    const auto r               = state.get_position();
                    const double x             = r.get_x().numerical_value_in(km);
                    const double y             = r.get_y().numerical_value_in(km);
                    const double z             = r.get_z().numerical_value_in(km);
                    result.frames[frameIdx][i] = { x, y, z };
                    maxRadius                  = std::max(maxRadius, std::sqrt(x * x + y * y + z * z));
                    ++frameIdx;
                }
                for (; frameIdx > 0 && frameIdx < numExpectedFrames; ++frameIdx) {
                    result.frames[frameIdx][i] = result.frames[frameIdx - 1][i];
                }
            }
            catch (...) {
                // Leave this object at (0,0,0) if it fails to propagate
            }
        }
    }

    const auto end     = std::chrono::steady_clock::now();
    result.elapsedMs   = std::chrono::duration<double, std::milli>(end - start).count();
    result.maxRadiusKm = maxRadius;

    return result;
}

std::string build_frames_js(const std::vector<std::vector<Point3>>& frames)
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);
    os << "[";
    for (std::size_t f = 0; f < frames.size(); ++f) {
        if (f > 0) { os << ","; }
        os << "[";
        for (std::size_t i = 0; i < frames[f].size(); ++i) {
            if (i > 0) { os << ","; }
            os << "[" << frames[f][i].x << "," << frames[f][i].y << "," << frames[f][i].z << "]";
        }
        os << "]";
    }
    os << "]";
    return os.str();
}

std::string replace_all(std::string text, const std::string& from, const std::string& to)
{
    std::size_t pos = 0;
    while ((pos = text.find(from, pos)) != std::string::npos) {
        text.replace(pos, from.size(), to);
        pos += to.size();
    }
    return text;
}

std::string build_html(
    const std::string& templatePath,
    const std::vector<std::vector<Point3>>& frames,
    const double earthRadiusKm,
    const double maxRadiusKm,
    const double elapsedMs,
    const double propMinutes,
    const double stepMinutes
)
{
    const std::size_t numObjects = frames.empty() ? 0 : frames[0].size();
    const double throughput      = elapsedMs > 0.0 ? (1000.0 * static_cast<double>(numObjects) / elapsedMs) : 0.0;

    std::ostringstream stats;
    stats << std::fixed << std::setprecision(2);
    stats << "{"
          << "\"objects\":" << numObjects << ","
          << "\"elapsedMs\":" << elapsedMs << ","
          << "\"throughput\":" << throughput << ","
          << "\"propMinutes\":" << propMinutes << ","
          << "\"stepMinutes\":" << stepMinutes << ","
          << "\"numFrames\":" << frames.size() << "}";

    std::ostringstream nums;
    nums << std::fixed << std::setprecision(3);
    nums << "{"
         << "\"earthRadiusKm\":" << earthRadiusKm << ","
         << "\"maxRadiusKm\":" << maxRadiusKm << ""
         << "}";

    std::ifstream templateFile(templatePath);
    if (!templateFile.is_open()) { throw std::runtime_error("[helios] Cannot open HTML template: " + templatePath); }
    const std::string htmlTemplate(std::istreambuf_iterator<char>(templateFile), {});

    std::string html = htmlTemplate;
    html             = replace_all(std::move(html), "__STATS__", stats.str());
    html             = replace_all(std::move(html), "__NUMERIC__", nums.str());
    html             = replace_all(std::move(html), "__FRAMES__", build_frames_js(frames));
    return html;
}

} // namespace

int main(int argc, char* argv[])
{
    const std::string execPath = (argc > 0 && argv[0]) ? argv[0] : "";
    const auto env             = load_env_file(execPath);

    auto get_env = [&](const std::string& key) -> std::string {
        const auto it = env.find(key);
        return it != env.end() ? it->second : "";
    };

    const std::string username = get_env("SPACETRACK_USERNAME");
    const std::string password = get_env("SPACETRACK_PASSWORD");

    if (username.empty() || password.empty()) {
        std::cerr << "[helios] Missing SPACETRACK_USERNAME or SPACETRACK_PASSWORD.\n"
                  << "        Create a .env file beside the binary with:\n"
                  << "        SPACETRACK_USERNAME=your@email.com\n"
                  << "        SPACETRACK_PASSWORD=yourpassword\n";
        return 1;
    }

    constexpr double kPropagationMinutes = 90.0;
    constexpr double kOutputStepMinutes  = 5.0;

    std::cout << "[helios] Fetching live GP data from SpaceTrack...\n";
    const auto gpObjects = fetch_active_gp(username, password);
    if (gpObjects.empty()) {
        std::cerr << "[helios] No GP data returned. Check credentials or network.\n";
        return 1;
    }

    const Time propagationInterval = minutes(kPropagationMinutes);
    const Time stepInterval        = minutes(kOutputStepMinutes);

    std::cout << "[helios] Propagating " << gpObjects.size() << " objects...\n";
    const auto result = propagate_many_objects(gpObjects, propagationInterval, stepInterval);
    std::cout << "[helios] Propagation complete in " << result.elapsedMs << " ms\n";

    const double earthRadiusKm = get_celestial_body_parameters<planets::Earth>().equitorialRadius.numerical_value_in(km);

    webui::window window;
    window.set_size(1280, 860);
    window.set_center();

    const std::string binDir   = execPath.substr(0, execPath.find_last_of("/\\") + 1);
    const std::string tmplPath = binDir + "templates/index.html";

    const std::string html =
        build_html(tmplPath, result.frames, earthRadiusKm, result.maxRadiusKm, result.elapsedMs, kPropagationMinutes, kOutputStepMinutes);

    window.show(html);
    webui::wait();

    return 0;
}
