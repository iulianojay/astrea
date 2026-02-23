/**
 * @file output.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for outputting access analysis info.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

#include <csv.hpp>
#include <mp-units/systems/si/units.h>

#include <astro/platforms/space/Constellation.hpp>

#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/risesets/riseset_utils.hpp>

using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {

/**
 * @brief Saves the AccessArray to a file in a human-readable format.
 *
 * @tparam T The type of Spacecraft used in the Constellation.
 * @param accesses The AccessArray containing the access times to be saved.
 * @param outfile The name of the file to save to.
 * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
 * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
 */
template <typename T, typename U>
void save_accesses_to_file(const AccessArray& accesses, const std::filesystem::path& outfile, const astro::Constellation<T>& satellites, const U& grounds = U())
{
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    writer << std::vector<std::string>({ "Sender", "Receiver", "Rise - Set Times (s)" });
    for (const auto& [idPair, risesets] : accesses) {
        if (risesets.size() > 0) {

            // Gross
            std::string sender, receiver;
            for (const auto& shell : satellites.get_shells()) {
                for (const auto& plane : shell.get_planes()) {
                    for (const auto& viewer : plane.get_all_spacecraft()) {
                        if (viewer.get_id() == idPair.sender) { sender = viewer.get_name(); }
                        if (viewer.get_id() == idPair.receiver) { receiver = viewer.get_name(); }
                    }
                }
            }
            if (grounds.size() != 0) {
                for (const auto& ground : grounds) {
                    if (ground.get_id() == idPair.sender) { sender = ground.get_name(); }
                    if (ground.get_id() == idPair.receiver) { receiver = ground.get_name(); }
                }
            }

            std::vector<std::string> row{ sender, receiver };
            for (const auto& str : risesets.to_string_vector()) {
                row.push_back(str);
            }
            writer << row;
        }
    }
}


/**
 * @brief Saves the AccessArray to a file in a human-readable format.
 *
 * @tparam T The type of Spacecraft used in the Constellation.
 * @param accesses The AccessArray containing the access times to be saved.
 * @param outfile The name of the file to save to.
 * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
 * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
 */
template <typename T, typename U>
void save_riseset_metrics_to_file(
    const AccessArray& accesses,
    const std::filesystem::path& outfile,
    const astro::Constellation<T>& satellites,
    const U& grounds = U()
)
{
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    std::vector<std::string> header = { "Sender", "Receiver" };
    for (const auto& metric : { "Access", "Gap" }) {
        header.push_back(std::string("MIN ") + metric + " Time (s)");
        header.push_back(std::string("AVG ") + metric + " Time (s)");
        header.push_back(std::string("MAX ") + metric + " Time (s)");

        for (const auto& pct : DEFAULT_PERCENTILES) {
            int pctVal = pct.numerical_value_ref_in(pct.unit);
            header.push_back(std::to_string(pctVal) + "th PCT " + metric + " Time (s)");
        }
    }

    writer << header;
    for (const auto& [idPair, risesets] : accesses) {
        if (risesets.size() > 0) {

            // Gross
            std::string sender, receiver;
            for (const auto& shell : satellites.get_shells()) {
                for (const auto& plane : shell.get_planes()) {
                    for (const auto& viewer : plane.get_all_spacecraft()) {
                        if (viewer.get_id() == idPair.sender) { sender = viewer.get_name(); }
                        if (viewer.get_id() == idPair.receiver) { receiver = viewer.get_name(); }
                    }
                }
            }
            if (grounds.size() != 0) {
                for (const auto& ground : grounds) {
                    if (ground.get_id() == idPair.sender) { sender = ground.get_name(); }
                    if (ground.get_id() == idPair.receiver) { receiver = ground.get_name(); }
                }
            }

            RiseSetStats stats(risesets);

            std::vector<std::string> row{ sender, receiver };
            for (const auto& str : stats.to_string_vector()) {
                row.push_back(str);
            }
            writer << row;
        }
    }
}


/**
 * @brief Saves the AccessArray to a file in a human-readable format.
 *
 * @tparam T The type of Spacecraft used in the Constellation.
 * @param accesses The AccessArray containing the access times to be saved.
 * @param outfile The name of the file to save to.
 * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
 * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
 */
template <typename T, typename U>
void save_access_metrics_to_file(
    const AccessArray& accesses,
    const std::filesystem::path& outfile,
    const astro::Constellation<T>& satellites,
    const U& grounds = U()
)
{
    AccessStats stats(accesses);

    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    std::vector<std::string> statStrings = { "MIN", "AVG", "MAX" };
    for (const auto& pct : DEFAULT_PERCENTILES) {
        int pctVal = pct.numerical_value_ref_in(pct.unit);
        statStrings.push_back(std::to_string(pctVal) + "th PCT");
    }

    std::vector<std::string> header = { "Object", "N Folds" };
    for (const auto& statStr : statStrings) {
        for (const auto& metric : { "Access", "Gap" }) {
            header.push_back(std::string("MIN ") + statStr + " " + metric + " Time (s)");
            header.push_back(std::string("AVG ") + statStr + " " + metric + " Time (s)");
            header.push_back(std::string("MAX ") + statStr + " " + metric + " Time (s)");

            for (const auto& pct : DEFAULT_PERCENTILES) {
                int pctVal = pct.numerical_value_ref_in(pct.unit);
                header.push_back(std::to_string(pctVal) + "th PCT " + statStr + " " + metric + " Time (s)");
            }
        }
    }

    writer << header;
    for (const auto& [id, statsPair] : stats.stats) {

        // Gross
        std::string object;
        for (const auto& shell : satellites.get_shells()) {
            for (const auto& plane : shell.get_planes()) {
                for (const auto& viewer : plane.get_all_spacecraft()) {
                    if (viewer.get_id() == id) { object = viewer.get_name(); }
                }
            }
        }
        if (grounds.size() != 0) {
            for (const auto& ground : grounds) {
                if (ground.get_id() == id) { object = ground.get_name(); }
            }
        }

        std::vector<std::string> row{ object };
        for (const auto& str : statsPair.at(RiseSetMetric::ACCESS_TIME).to_string_vector()) {
            row.push_back(str);
        }
        for (const auto& str : statsPair.at(RiseSetMetric::GAP).to_string_vector()) {
            row.push_back(str);
        }
        writer << row;
    }
}


/**
 * @brief Saves the AccessArray to a file in a human-readable format.
 *
 * @tparam T The type of Spacecraft used in the Constellation.
 * @param accesses The AccessArray containing the access times to be saved.
 * @param outfile The name of the file to save to.
 * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
 * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
 */
template <typename T, typename U>
void save_number_of_folds_to_file(
    const AccessArray& accesses,
    const std::filesystem::path& outfile,
    const astro::Constellation<T>& satellites,
    const U& grounds,
    const Time& resolution,
    const Time& start,
    const Time& end
)
{
    FoldsOfCoverage folds(accesses, resolution, start, end);

    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    std::vector<std::string> header = { "Object", "N Folds" };
    header.push_back(std::string("MIN N Folds"));
    header.push_back(std::string("AVG N Folds"));
    header.push_back(std::string("MAX N Folds"));

    for (const auto& pct : DEFAULT_PERCENTILES) {
        int pctVal = pct.numerical_value_ref_in(pct.unit);
        header.push_back(std::to_string(pctVal) + "th PCT N Folds");
    }

    writer << header;
    for (const auto& [id, foldsVector] : folds) {

        // Gross
        std::string object;
        for (const auto& shell : satellites.get_shells()) {
            for (const auto& plane : shell.get_planes()) {
                for (const auto& viewer : plane.get_all_spacecraft()) {
                    if (viewer.get_id() == id) { object = viewer.get_name(); }
                }
            }
        }
        if (grounds.size() != 0) {
            for (const auto& ground : grounds) {
                if (ground.get_id() == id) { object = ground.get_name(); }
            }
        }

        std::vector<std::string> row{ object };
        for (const auto& str : folds.get_stats(id).to_string_vector()) {
            row.push_back(str);
        }
        for (const auto& nFolds : foldsVector) {
            row.push_back(std::to_string(nFolds));
        }
        writer << row;
    }
}

} // namespace trace
} // namespace astrea