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

#include <iomanip>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/http-queries/ethz/EthzClient.hpp>
#include <snapshot/http-queries/spacetrack/SpaceTrackClient.hpp>

using namespace snapshot;

void query_ethz_database();
void query_spacetrack(int argc, char** argv);

int main(int argc, char** argv)
{
    // query_ethz_database();
    query_spacetrack(argc, argv);

    return 0;
}

void query_ethz_database()
{
    const astro::Date startDate("2024-01-01 00:00:00.0");
    const astro::Date endDate("2024-01-02 00:00:00.0");
    // const unsigned noradId = 44714;
    const std::string name = "NAVSTAR";

    EthzClient ethz;

    // std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, noradId) << std::endl;
    std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, name, true) << std::endl;
}

void query_spacetrack(int argc, char** argv)
{
    SpaceTrackClient spaceTrack;
    nlohmann::json allSpaceTrackData = spaceTrack.retrieve_all(argv[1], argv[2]);
    std::ofstream outFileStream("./astrea/snapshot/snapshot/database/spacetrack_data.json");
    outFileStream << std::setw(4) << allSpaceTrackData;
}