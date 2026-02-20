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

#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/risesets/riseset_utils.hpp>

using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {

struct RisesetStats {

    RisesetStats(const RiseSetArray& risesets) :
        avgAccessTime(risesets.access_time(Stat::MEAN)),
        minAccessTime(risesets.access_time(Stat::MIN)),
        maxAccessTime(risesets.access_time(Stat::MAX)),
        pct10AccessTime(risesets.access_time(Stat::PCT, 0.1)),
        pct90AccessTime(risesets.access_time(Stat::PCT, 0.9)),
        avgGapTime(risesets.gap(Stat::MEAN)),
        minGapTime(risesets.gap(Stat::MIN)),
        maxGapTime(risesets.gap(Stat::MAX)),
        pct10GapTime(risesets.gap(Stat::PCT, 0.1)),
        pct90GapTime(risesets.gap(Stat::PCT, 0.9))
    {
    }

    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(10);

        retval.push_back(to_formatted_string(minAccessTime));
        retval.push_back(to_formatted_string(avgAccessTime));
        retval.push_back(to_formatted_string(maxAccessTime));
        retval.push_back(to_formatted_string(pct10AccessTime));
        retval.push_back(to_formatted_string(pct90AccessTime));
        retval.push_back(to_formatted_string(minGapTime));
        retval.push_back(to_formatted_string(avgGapTime));
        retval.push_back(to_formatted_string(maxGapTime));
        retval.push_back(to_formatted_string(pct10GapTime));
        retval.push_back(to_formatted_string(pct90GapTime));

        return retval;
    }

    Time avgAccessTime;
    Time minAccessTime;
    Time maxAccessTime;
    Time pct10AccessTime;
    Time pct90AccessTime;
    Time avgGapTime;
    Time minGapTime;
    Time maxGapTime;
    Time pct10GapTime;
    Time pct90GapTime;
};

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
void save_access_metrics_to_file(
    const AccessArray& accesses,
    const std::filesystem::path& outfile,
    const astro::Constellation<T>& satellites,
    const U& grounds = U()
)
{
    std::filesystem::create_directories(outfile.parent_path());
    std::ofstream ss(outfile);
    auto writer = csv::make_csv_writer(ss);

    writer << std::vector<std::string>({
        "Sender",
        "Receiver",
        "MIN Access Time (s)",
        "AVG Access Time (s)",
        "MAX Access Time (s)",
        "10th PCT Access Time (s)",
        "90th PCT Access Time (s)",
        "MIN Gap Time (s)",
        "AVG Gap Time (s)",
        "MAX Gap Time (s)",
        "10th PCT Gap Time (s)",
        "90th PCT Gap Time (s)",
    });
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

                RisesetStats stats(risesets);

                std::vector<std::string> row{ sender, receiver };
                for (const auto& str : stats.to_string_vector()) {
                    row.push_back(str);
                }
                writer << row;
            }
        }
    }
}

} // namespace trace
} // namespace astrea