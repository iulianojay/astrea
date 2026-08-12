/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <helios/app/animations.hpp>

#include <mp-units/systems/si.h>

#include <astro/astro.hpp>
#include <units/units.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace helios {

namespace {

static const double EARTH_RADIUS_KM = get_celestial_body_parameters<planets::Earth>().equitorialRadius.numerical_value_in(km);

}

void replace_all(std::string& text, const std::string& from, const std::string& to)
{
    std::size_t pos = 0;
    while ((pos = text.find(from, pos)) != std::string::npos) {
        text.replace(pos, from.size(), to);
        pos += to.size();
    }
}


std::string
    build_html(const std::vector<AnimationFrame>& frames, const double maxRadiusKm, const double elapsedMs, const double propMinutes, const double stepMinutes)
{
    const std::size_t nObjects = frames.empty() ? 0 : frames[0].size();
    const double throughput    = elapsedMs > 0.0 ? (1000.0 * static_cast<double>(nObjects) / elapsedMs) : 0.0;

    nlohmann::json stats;
    stats["objects"]     = nObjects;
    stats["elapsedMs"]   = elapsedMs;
    stats["throughput"]  = throughput;
    stats["propMinutes"] = propMinutes;
    stats["stepMinutes"] = stepMinutes;
    stats["nFrames"]     = frames.size();

    nlohmann::json nums;
    nums["earthRadiusKm"] = EARTH_RADIUS_KM;
    nums["maxRadiusKm"]   = maxRadiusKm;

    static const std::filesystem::path templatePath = std::string(_HELIOS_ROOT_) + "/templates/index.html";
    std::ifstream templateFile(templatePath);
    if (!templateFile.is_open()) {
        throw std::runtime_error("[helios] Cannot open HTML template: " + templatePath.string());
    }
    const std::string htmlTemplate(std::istreambuf_iterator<char>(templateFile), {});

    std::string html = htmlTemplate;
    replace_all(html, "__STATS__", stats.dump());
    replace_all(html, "__NUMERIC__", nums.dump());
    replace_all(html, "__FRAMES__", build_frames_js(frames));
    return html;
}

std::string build_repropagate_json(const PropagationSettings& settings, const PropagationResult& results)
{
    const std::size_t nObjects = results.frames.empty() ? 0 : results.frames[0].size();
    const double throughput = results.elapsedMs > 0.0 ? (1000.0 * static_cast<double>(nObjects) / results.elapsedMs) : 0.0;

    nlohmann::json stats;
    stats["objects"]     = nObjects;
    stats["elapsedMs"]   = results.elapsedMs;
    stats["throughput"]  = throughput;
    stats["propMinutes"] = settings.propTime.numerical_value_in(min);
    stats["stepMinutes"] = settings.step.numerical_value_in(min);
    stats["nFrames"]     = results.frames.size();

    nlohmann::json nums;
    nums["earthRadiusKm"] = EARTH_RADIUS_KM;
    nums["maxRadiusKm"]   = results.maxRadiusKm;

    std::ostringstream json; // nlohmann::json doesn't work here for some reason
    json << "{\"frames\":" << build_frames_js(results.frames) << ",\"numeric\":" << nums.dump()
         << ",\"stats\":" << stats.dump() << "}";
    return json.str();
}


std::string build_frames_js(const std::vector<AnimationFrame>& frames)
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);
    os << "[";
    for (const auto& frame : frames) {
        if (&frame != &frames[0]) { os << ","; }
        os << frame;
    }
    os << "]";
    return os.str();
}

} // namespace helios
} // namespace astrea