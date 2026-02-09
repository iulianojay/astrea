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

#include <astro/platforms/space/Constellation.hpp>

#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/risesets/AccessArray.hpp>

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
template <typename T>
void save_accesses_to_file(
    const AccessArray& accesses,
    const std::filesystem::path& outfile,
    const astro::Constellation<T>& satellites,
    const std::optional<GroundArchitecture>& grounds = std::nullopt
)
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
            if (grounds.has_value()) {
                for (const auto& ground : grounds.value()) {
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

} // namespace trace
} // namespace astrea