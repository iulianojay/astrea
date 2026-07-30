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

#include <helios/app.hpp>
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

int main(int argc, char* argv[])
{
    // Default propagation parameters
    const double propagationMinutes = 90.0;
    const double outputStepMinutes  = 5.0;

    // Load GP data from snapshot database
    std::cout << "[helios] Loading GP data from snapshot database...\n";
    const auto gpObjects = load_gp_from_db();
    if (gpObjects.empty()) {
        std::cerr << "[helios] No GP data in snapshot database. Run the snapshot driver to populate it first.\n";
        return 1;
    }

    // Propagate everything
    const PropagationSettings settings{ minutes(propagationMinutes), minutes(outputStepMinutes) };

    std::cout << "[helios] Propagating " << gpObjects.size() << " objects...\n";
    const auto result = propagate_many_objects(gpObjects, settings);
    std::cout << "[helios] Propagation complete in " << result.elapsedMs << " ms\n";

    // Launch web UI
    webui::window window;
    const std::filesystem::path iconPath =
        std::string(_HELIOS_ROOT_) + "../../../docs/assets/images/astrea-color-crop.png";
    window.set_icon("<png>...</png>", iconPath.string()); // Set both SVG and PNG icons for compatibility
    window.set_size(1280, 860);
    window.set_center();

    // Repropagate binding: JS calls webui.call('repropagate', propMin, stepMin)
    // Returns the new frames+numeric+stats as a JSON string, which the JS side
    // receives as the resolved promise value and applies directly.
    window.bind("repropagate", [&](webui::window::event* event) {
        try {
            const nlohmann::json args = nlohmann::json::parse(event->get_string(0));
            const PropagationSettings rerunSettings(args);

            std::cout << "[helios] Repropagating: " << rerunSettings.propTime.in(min) << " / "
                      << rerunSettings.step.in(min) << " step...\n";
            const auto results = propagate_many_objects(gpObjects, rerunSettings);
            std::cout << "[helios] Repropagate complete in " << results.elapsedMs << " ms\n";

            const std::string json = build_repropagate_json(rerunSettings, results);
            event->return_string(json);
        }
        catch (const std::exception& ex) {
            std::cerr << "[helios] Repropagate error: " << ex.what() << "\n";
            event->return_string("{\"error\":\"" + std::string(ex.what()) + "\"}");
        }
    });

    // Build initial HTML with the first propagation result
    const std::string html = build_html(result.frames, result.maxRadiusKm, result.elapsedMs, propagationMinutes, outputStepMinutes);

    window.show(html);
    webui::wait();

    return 0;
}
