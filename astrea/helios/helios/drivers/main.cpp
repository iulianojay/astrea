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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <omp.h>
#include <webui.hpp>

#include <astro/astro.hpp>
#include <snapshot/snapshot.hpp>
#include <units/units.hpp>

#include <helios/helios.macros.hpp>
#include <helios/types.hpp>

using namespace astrea;
using namespace astro;
using namespace snapshot;
using namespace helios;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::unit_symbols::min;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace {

static const double EARTH_RADIUS_KM = get_celestial_body_parameters<planets::Earth>().equitorialRadius.numerical_value_in(km);

}


std::vector<GeneralPerturbations> load_gp_from_db()
{
    auto storage = snapshot::get_snapshot();

    std::vector<GeneralPerturbations> all = storage.get_all<GeneralPerturbations>();
    std::vector<GeneralPerturbations> result;
    result.reserve(all.size());
    for (auto& gp : all) {
        if (!gp.SEMIMAJOR_AXIS || !gp.ECCENTRICITY || !gp.INCLINATION || !gp.RA_OF_ASC_NODE || !gp.ARG_OF_PERICENTER ||
            !gp.MEAN_ANOMALY) {
            continue;
        }
        result.push_back(std::move(gp));
    }
    std::cout << "[helios] Loaded " << result.size() << " valid GP records from snapshot database\n";
    return result;
}

inline constexpr struct AppFrame
    : FixedOffsetFrame<frames::primary, Angle(90.0 * deg), Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} AppFrame;

PropagationResult propagate_many_objects(const std::vector<GeneralPerturbations>& gpObjects, const PropagationSettings& settings)
{
    const Time propTime = settings.propTime;
    const Time stepTime = settings.step;

    const std::size_t nExpectedFrames =
        static_cast<std::size_t>(propTime.numerical_value_in(s) / stepTime.numerical_value_in(s)) + 1;

    const std::size_t objectCount = gpObjects.size();
    PropagationResult result;
    result.nFrames = nExpectedFrames;
    result.frames.assign(nExpectedFrames, AnimationFrame{ std::vector<Point3>(objectCount, { 0.0, 0.0, 0.0 }) });

    const auto start = std::chrono::steady_clock::now();

    double maxRadius = 0.0;

#pragma omp parallel reduction(max : maxRadius)
    {
        Integrator integrator;
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);

        if (settings.ten || settings.fourty || settings.eighty || settings.srp || settings.nBody || settings.drag) {
            ForceModel forceModel;
            if (settings.eighty) { forceModel.add<OblatenessForce, planets::Earth, 80, 80>(); }
            else if (settings.fourty) {
                forceModel.add<OblatenessForce, planets::Earth, 40, 40>();
            }
            else if (settings.ten) {
                forceModel.add<OblatenessForce, planets::Earth, 10, 10>();
            }
            if (settings.srp) { forceModel.add<SolarRadiationPressure>(); }
            if (settings.nBody) { forceModel.add<NBodyForce, moons::Moon, star::Sun>(); }
            if (settings.drag) { forceModel.add<AtmosphericForce>(); }
            EquinoctialVop equinoctialVop{ forceModel };
            integrator.set_equations_of_motion(equinoctialVop);
        }
        else {
            J2MeanVop j2mean;
            integrator.set_equations_of_motion(j2mean);
        }
        integrator.switch_fixed_timestep(true, stepTime);

#pragma omp for schedule(dynamic, 64)
        for (std::size_t ii = 0; ii < objectCount; ++ii) {
            try {
                Spacecraft sc(gpObjects[ii]);
                Vehicle vehicle{ sc };
                const State state0         = sc.get_initial_state();
                const StateHistory history = integrator.propagate(state0, propTime, vehicle);

                std::size_t frameIdx = 0;
                for (const auto& state : history) {
                    if (frameIdx >= nExpectedFrames) break;
                    // TODO: Do this rotation here for speed
                    const auto rApp = state.get_position();
                    // const auto rApp             = state.get_position_in_frame<AppFrame>();
                    const double R              = rApp.norm().numerical_value_in(km);
                    const double x              = rApp.get_x().numerical_value_in(km);
                    const double y              = rApp.get_y().numerical_value_in(km);
                    const double z              = rApp.get_z().numerical_value_in(km);
                    result.frames[frameIdx][ii] = { x, y, z };
                    maxRadius                   = std::max(maxRadius, R);
                    ++frameIdx;
                }
                for (; frameIdx > 0 && frameIdx < nExpectedFrames; ++frameIdx) {
                    result.frames[frameIdx][ii] = result.frames[frameIdx - 1][ii];
                }
            }
            catch (...) {
                // Leave this object at (0,0,0) if it fails to propagate
            }
        }
    }

    const auto end   = std::chrono::steady_clock::now();
    result.elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();
    // Cap max radius at geostationary distance for better visualization scaling
    result.maxRadiusKm = std::min(maxRadius, 42000.0);

    return result;
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

int main(int argc, char* argv[])
{
    double kPropagationMinutes = 90.0;
    double kOutputStepMinutes  = 5.0;

    std::cout << "[helios] Loading GP data from snapshot database...\n";
    const auto gpObjects = load_gp_from_db();
    if (gpObjects.empty()) {
        std::cerr << "[helios] No GP data in snapshot database. Run the snapshot driver to populate it first.\n";
        return 1;
    }

    const PropagationSettings settings = { .propTime = minutes(kPropagationMinutes), .step = minutes(kOutputStepMinutes) };

    std::cout << "[helios] Propagating " << gpObjects.size() << " objects...\n";
    const auto result = propagate_many_objects(gpObjects, settings);
    std::cout << "[helios] Propagation complete in " << result.elapsedMs << " ms\n";

    webui::window window;
    const std::filesystem::path iconPath =
        std::string(_HELIOS_ROOT_) + "../../../docs/assets/images/astrea-color-crop.png";
    window.set_icon("<png>...</png>", iconPath.string()); // Set both SVG and PNG icons for compatibility
    window.set_size(1280, 860);
    window.set_center();

    // Repropagate binding: JS calls webui.call('repropagate', propMin, stepMin)
    // Returns the new frames+numeric+stats as a JSON string, which the JS side
    // receives as the resolved promise value and applies directly.
    window.bind("repropagate", [&](webui::window::event* e) {
        try {
            const nlohmann::json args             = nlohmann::json::parse(e->get_string(0));
            const PropagationSettings newSettings = { .propTime = minutes(args["propMin"].get<double>()),
                                                      .step     = minutes(args["stepMin"].get<double>()),
                                                      .ten      = args["ten"].get<bool>(),
                                                      .fourty   = args["fourty"].get<bool>(),
                                                      .eighty   = args["eighty"].get<bool>(),
                                                      .srp      = args["srp"].get<bool>(),
                                                      .nBody    = args["nbody"].get<bool>(),
                                                      .drag     = args["drag"].get<bool>() };

            std::cout << "[helios] Repropagating: " << newSettings.propTime.in(min) << " / " << newSettings.step.in(min) << " step...\n";
            const auto results = propagate_many_objects(gpObjects, newSettings);
            std::cout << "[helios] Repropagate complete in " << results.elapsedMs << " ms\n";

            const std::string json = build_repropagate_json(newSettings, results);
            e->return_string(json);
        }
        catch (const std::exception& ex) {
            std::cerr << "[helios] Repropagate error: " << ex.what() << "\n";
            e->return_string("{\"error\":\"" + std::string(ex.what()) + "\"}");
        }
    });

    const std::string html =
        build_html(result.frames, result.maxRadiusKm, result.elapsedMs, kPropagationMinutes, kOutputStepMinutes);

    window.show(html);
    webui::wait();

    return 0;
}
