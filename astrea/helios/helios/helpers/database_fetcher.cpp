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

#include <helios/helpers/database_fetcher.hpp>

using namespace astrea;
using namespace astro;

namespace astrea {
namespace helios {

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

} // namespace helios
} // namespace astrea