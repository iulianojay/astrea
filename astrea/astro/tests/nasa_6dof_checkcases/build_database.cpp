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
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <system_error>
#include <thread>

#include <csv.hpp>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <utilities/ProgressBar.hpp>

#include <astro/astro.macros.hpp>
#include <astro/time/Date.hpp>
#include <tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp>

namespace {

std::vector<std::filesystem::path> get_csv_files(const std::filesystem::path& root)
{
    std::vector<std::filesystem::path> files;
    if (!std::filesystem::exists(root)) { return files; }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {
        if (entry.path().extension() == ".csv") { files.push_back(entry.path()); }
    }
    std::sort(files.begin(), files.end());
    return files;
}

template <typename StorageT>
void refresh_atmospheric_checkcase(StorageT& ccdb, const std::filesystem::path& filepath)
{
    using namespace sqlite_orm;
    using json = nlohmann::json;
    using astrea::astro::tests::AtmosphericCheckcase;
    using astrea::astro::tests::AtmosphericCheckcaseRow;

    const AtmosphericCheckcase checkcase(filepath);

    ccdb.template remove_all<AtmosphericCheckcaseRow>(where(
        c(&AtmosphericCheckcaseRow::checkcase_num) == checkcase.checkcase_num &&
        c(&AtmosphericCheckcaseRow::sim_num) == checkcase.sim_num
    ));
    ccdb.template remove_all<AtmosphericCheckcase>(where(
        c(&AtmosphericCheckcase::checkcase_num) == checkcase.checkcase_num &&
        c(&AtmosphericCheckcase::sim_num) == checkcase.sim_num
    ));

    ccdb.insert(checkcase);

    csv::CSVReader reader(filepath.string());
    for (const auto& row : reader) {
        const json rowJson = json::parse(row.to_json());
        AtmosphericCheckcaseRow checkcaseRow(checkcase.checkcase_num, checkcase.sim_num, rowJson);
        ccdb.insert(checkcaseRow);
    }
}

template <typename StorageT>
void refresh_orbital_checkcase(StorageT& ccdb, const std::filesystem::path& filepath)
{
    using namespace sqlite_orm;
    using json = nlohmann::json;
    using astrea::astro::tests::OrbitalCheckcase;
    using astrea::astro::tests::OrbitalCheckcaseRow;

    const OrbitalCheckcase checkcase(filepath);

    ccdb.template remove_all<OrbitalCheckcaseRow>(where(
        c(&OrbitalCheckcaseRow::checkcase_num) == checkcase.checkcase_num &&
        c(&OrbitalCheckcaseRow::sim_num) == checkcase.sim_num
    ));
    ccdb.template remove_all<OrbitalCheckcase>(where(
        c(&OrbitalCheckcase::checkcase_num) == checkcase.checkcase_num && c(&OrbitalCheckcase::sim_num) == checkcase.sim_num
    ));

    ccdb.insert(checkcase);

    csv::CSVReader reader(filepath.string());
    for (const auto& row : reader) {
        const json rowJson = json::parse(row.to_json());
        OrbitalCheckcaseRow checkcaseRow(checkcase.checkcase_num, checkcase.sim_num, rowJson);
        ccdb.insert(checkcaseRow);
    }
}

bool has_full_rebuild_flag(const int argc, char** argv)
{
    for (int ii = 1; ii < argc; ++ii) {
        if (std::string(argv[ii]) == "--full-rebuild") { return true; }
    }
    return false;
}

} // namespace

namespace astrea::astro::tests {

int build_checkcase_database_once(const bool fullRebuild)
{
    using namespace sqlite_orm;

    // Build database
    auto ccdb = get_checkcase_database();
    ccdb.sync_schema();

    // Optional full rebuild for one-shot refreshes.
    if (fullRebuild) {
        ccdb.remove_all<AtmosphericCheckcaseRow>();
        ccdb.remove_all<OrbitalCheckcaseRow>();
        ccdb.remove_all<AtmosphericCheckcase>();
        ccdb.remove_all<OrbitalCheckcase>();
    }

    // Get atmospheric checkcase files
    std::vector<std::filesystem::path> checkcaseFiles =
        get_csv_files(std::string(_ASTRO_ROOT_) + "/tests/nasa_6dof_checkcases/data/checkcases/atmospheric");

    // Store in DB
    utilities::ProgressBar bar1(checkcaseFiles.size(), "Building Atmospheric Checkcases");
    for (const auto& filepath : checkcaseFiles) {

        // Progress bar
        bar1();

        // Keep each file update atomic so partial failures don't leave mixed rows.
        ccdb.transaction([&]() {
            refresh_atmospheric_checkcase(ccdb, filepath);
            return true;
        });
    }
    std::cout << std::endl;

    // Now get orbital checkcase files
    checkcaseFiles = get_csv_files(std::string(_ASTRO_ROOT_) + "/tests/nasa_6dof_checkcases/data/checkcases/orbital/");

    // Store in DB
    utilities::ProgressBar bar2(checkcaseFiles.size(), "Building Orbital Checkcases");
    for (const auto& filepath : checkcaseFiles) {

        // Progress bar
        bar2();

        // Keep each file update atomic so partial failures don't leave mixed rows.
        ccdb.transaction([&]() {
            refresh_orbital_checkcase(ccdb, filepath);
            return true;
        });
    }
    std::cout << std::endl;

    return 0;
}

} // namespace astrea::astro::tests

/**
 * @brief Builds out the checkcase database by reading data from public NASA checkcase files.
 *
 * @return int Exit status code (0 for success)
 */
int main(int argc, char** argv)
{
    const bool fullRebuild = has_full_rebuild_flag(argc, argv);

    constexpr int maxRetries = 5;
    for (int attempt = 1; attempt <= maxRetries; ++attempt) {
        try {
            return astrea::astro::tests::build_checkcase_database_once(fullRebuild);
        }
        catch (const std::system_error& e) {
            const std::string msg = e.what();
            if (msg.find("database is locked") == std::string::npos || attempt == maxRetries) {
                std::cerr << "Failed to build checkcase database: " << msg << std::endl;
                std::cerr << "Hint: close any open sqlite3 sessions using checkcases.db and retry." << std::endl;
                return 1;
            }

            const auto backoff = std::chrono::milliseconds(250 * attempt);
            std::cerr << "Database is locked, retrying in " << backoff.count() << " ms (attempt " << attempt << "/"
                      << maxRetries << ")..." << std::endl;
            std::this_thread::sleep_for(backoff);
        }
    }

    return 1;
}
