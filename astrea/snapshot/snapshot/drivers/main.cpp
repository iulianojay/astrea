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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <astro/state/orbital_data_formats/GeneralPerturbations.hpp>
#include <astro/time/Date.hpp>
#include <utilities/ProgressBar.hpp>

#include <snapshot/database/Database.hpp>
#include <snapshot/http-queries/spacetrack/SpaceTrackClient.hpp>

/**
 * @brief Main entry point for the SpaceTrack data retrieval application. This will query SpaceTrack using the provided
 * credentials, retrieve all available General Perturbations (GP) data, and store it in a local SQLite database.
 *
 * @param argc Command line argument count
 * @param argv Command line argument vector, where argv[1] is the SpaceTrack username and argv[2] is the password
 * @return int Exit status code (0 for success)
 */
int main(int argc, char** argv)
{
    // Build connection and connect
    using namespace astrea;
    using namespace astro;
    using namespace snapshot;
    using namespace sqlite_orm;

    // Build database
    auto snapshot = get_snapshot();
    snapshot.sync_schema();

    // Optimize database performance for bulk operations
    try {
        snapshot.pragma.journal_mode(sqlite_orm::journal_mode::WAL);
    }
    catch (...) {
        // If WAL mode fails, continue with default
    }

    // Query SpaceTrack
    SpaceTrackClient spaceTrack;
    const nlohmann::json spaceTrackData = spaceTrack.retrieve_all(argv[1], argv[2]);
    const std::size_t nRecords          = spaceTrackData.size();

    // Wrap all database operations in a single transaction for performance
    std::cout << "Storing SpaceTrack data in database at: " << std::string(_SNAPSHOT_ROOT_) + "/snapshot/database/snapshot.db"
              << std::endl;
    utilities::ProgressBar progressBar(nRecords, "Progress: ");
    snapshot.transaction([&] {
        for (const auto& data : spaceTrackData) {

            // Progress bar
            progressBar();

            // Build object
            const GeneralPerturbations gp(data);

            // Insert or update
            auto all = snapshot.get_all<GeneralPerturbations>(where(c(&GeneralPerturbations::NORAD_CAT_ID) == gp.NORAD_CAT_ID));
            if (all.size() == 0) { snapshot.insert(gp); }
            else {
                snapshot.update(gp);
            }
        }
        return true; // Commit transaction
    });
    std::cout << std::endl << "Data retrieval and storage complete. Total records processed: " << nRecords << std::endl;

    return 0;
}
