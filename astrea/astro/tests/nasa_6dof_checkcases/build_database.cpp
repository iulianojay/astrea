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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <utilities/ProgressBar.hpp>

#include <astro/time/Date.hpp>
#include <tests/nasa_6dof_checkcases/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/OrbitalCheckcase.hpp>

/**
 * @brief Builds out the checkcase database by reading data from public NASA checkcase files.
 *
 * @return int Exit status code (0 for success)
 */
int main()
{
    // Build connection and connect
    using namespace astrea;
    using namespace astro;
    using namespace astro::tests;
    using namespace sqlite_orm;

    // Build database
    auto ccdb = get_checkcase_database();
    ccdb.sync_schema();

    // Get atmospheric checkcase files
    std::vector<std::filesystem::path> checkcaseFiles;
    const std::string root = std::getenv("ASTREA_ROOT");
    auto atmoIterator =
        std::filesystem::directory_iterator(root + "/astrea/astro/tests/data/nasa_6dof_checkcases/checkcases/atmospheric/");
    for (const auto& entry : atmoIterator) {
        if (entry.path().extension() == ".csv") { checkcaseFiles.push_back(entry.path()); }
    }

    // Store in DB
    utilities::ProgressBar bar1(checkcaseFiles.size(), "Building Atmospheric Checkcases");
    for (const auto& data : checkcaseFiles) {

        // Progress bar
        bar1();

        // Build object
        const AtmosphericCheckcase checkcase(data);

        // Insert or update
        auto all = ccdb.get_all<AtmosphericCheckcase>(where(c(&AtmosphericCheckcase::id) == checkcase.id));
        if (all.size() == 0) { ccdb.insert(checkcase); }
        else {
            ccdb.update(checkcase);
        }
    }

    // Now get orbital checkcase files
    checkcaseFiles.clear();
    auto orbitIterator =
        std::filesystem::directory_iterator(root + "/astrea/astro/tests/data/nasa_6dof_checkcases/checkcases/orbital/");
    for (const auto& entry : orbitIterator) {
        if (entry.path().extension() == ".csv") { checkcaseFiles.push_back(entry.path()); }
    }

    // Store in DB
    utilities::ProgressBar bar2(checkcaseFiles.size(), "Building Orbital Checkcases");
    for (const auto& data : checkcaseFiles) {

        // Progress bar
        bar2();

        // Build object
        const OrbitalCheckcase checkcase(data);

        // Insert or update
        auto all = ccdb.get_all<OrbitalCheckcase>(where(c(&OrbitalCheckcase::id) == checkcase.id));
        if (all.size() == 0) { ccdb.insert(checkcase); }
        else {
            ccdb.update(checkcase);
        }
    }

    return 0;
}
