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

static const double EARTH_RADIUS_KM = get_celestial_body_parameters<planets::Earth>().equatorialRadius.numerical_value_in(km);

std::string
    build_stats_json(const std::size_t nObjects, const double elapsedMs, const double throughput, const double propMinutes, const double stepMinutes, const std::size_t nFrames)
{
    std::ostringstream os;
    os << "{\"objects\":" << nObjects << ",\"elapsedMs\":" << elapsedMs << ",\"throughput\":" << throughput
       << ",\"propMinutes\":" << propMinutes << ",\"stepMinutes\":" << stepMinutes << ",\"nFrames\":" << nFrames << "}";
    return os.str();
}

std::string build_numeric_json(const double maxRadiusKm)
{
    std::ostringstream os;
    os << "{\"earthRadiusKm\":" << EARTH_RADIUS_KM << ",\"maxRadiusKm\":" << maxRadiusKm << "}";
    return os.str();
}

} // namespace

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

    const std::string stats = build_stats_json(nObjects, elapsedMs, throughput, propMinutes, stepMinutes, frames.size());
    const std::string nums = build_numeric_json(maxRadiusKm);

    static const std::filesystem::path templatePath = std::string(_HELIOS_ROOT_) + "/templates/index.html";
    std::ifstream templateFile(templatePath);
    if (!templateFile.is_open()) {
        throw std::runtime_error("[helios] Cannot open HTML template: " + templatePath.string());
    }
    const std::string htmlTemplate(std::istreambuf_iterator<char>(templateFile), {});

    std::string html = htmlTemplate;
    replace_all(html, "__STATS__", stats);
    replace_all(html, "__NUMERIC__", nums);
    replace_all(html, "__FRAMES__", build_frames_js(frames));
    return html;
}

std::string build_repropagate_json(const PropagationSettings& settings, const PropagationResult& results)
{
    const std::size_t nObjects = results.frames.empty() ? 0 : results.frames[0].size();
    const double throughput = results.elapsedMs > 0.0 ? (1000.0 * static_cast<double>(nObjects) / results.elapsedMs) : 0.0;

    const std::string stats = build_stats_json(
        nObjects,
        results.elapsedMs,
        throughput,
        settings.propTime.numerical_value_in(min),
        settings.step.numerical_value_in(min),
        results.frames.size()
    );
    const std::string nums = build_numeric_json(results.maxRadiusKm);

    std::ostringstream json; // Build object manually to keep frames pre-serialized for speed.
    json << "{\"frames\":" << build_frames_js(results.frames) << ",\"numeric\":" << nums << ",\"stats\":" << stats << "}";
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