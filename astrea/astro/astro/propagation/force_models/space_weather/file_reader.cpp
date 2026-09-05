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
#include <astro/propagation/force_models/space_weather/file_reader.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <mp-units/systems/si.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using astrea::units::unit_symbols::sfu;

std::vector<SpaceWeatherParameters>
    read_space_weather_file(const std::filesystem::path& filePath, std::optional<Date> startDate, std::optional<Date> endDate)
{
    // Check if the file exists
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open space weather file: ") + filePath.string());
    }

    // Speed up the read by checking dates
    int startYear = 0, startMonth = 0, startDay = 0;
    int endYear = 0, endMonth = 0, endDay = 0;

    if (startDate.has_value()) {
        const auto startYmd = startDate->year_month_day();
        startYear           = static_cast<int>(startYmd.year());
        startMonth          = static_cast<unsigned>(startYmd.month());
        startDay            = static_cast<unsigned>(startYmd.day());
    }

    if (endDate.has_value()) {
        const auto endYmd = endDate->year_month_day();
        endYear           = static_cast<int>(endYmd.year());
        endMonth          = static_cast<unsigned>(endYmd.month());
        endDay            = static_cast<unsigned>(endYmd.day());
    }

    // Read the file
    std::string line;
    MeasurementType measurementType = MeasurementType::OBSERVED; // Default to OBSERVED if not specified
    std::vector<SpaceWeatherParameters> spaceWeatherParams;
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') { continue; }

        SpaceWeatherParameters row;

        // 0  1  2  3    4  5  6  7  8  9  10 11 12 13 14   15  16  17  18  19  20  21  22  23 24 25  26    27 28    29 30    31    32
        // yy mm dd BSRN ND Kp Kp Kp Kp Kp Kp Kp Kp Sum Ap  Ap  Ap  Ap  Ap  Ap  Ap  Ap  Avg Cp C9 ISN F10.7 Q  Ctr81 Lst81 F10.7 Ctr81 Lst81
        const auto tokens = astrea::utilities::split(line, " ");

        // Check if the date is within the specified range
        const int year  = std::stoi(tokens[0]);
        const int month = std::stoi(tokens[1]);
        const int day   = std::stoi(tokens[2]);

        // there's probably a better way to do this
        if (startDate.has_value()) {
            if (year < startYear) { continue; }
            if (year == startYear && month < startMonth) { continue; }
            if (year == startYear && month == startMonth && day < startDay) { continue; }
        }
        if (endDate.has_value()) {
            if (year > endYear) { break; }
            if (year == endYear && month > endMonth) { break; }
            if (year == endYear && month == endMonth && day > endDay) { break; }
        }

        // Check for measurement type
        if (line.find("OBSERVED") != std::string::npos) {
            measurementType = MeasurementType::OBSERVED;
            continue;
        }
        else if (line.find("DAILY_PREDICTED") != std::string::npos) {
            measurementType = MeasurementType::DAILY_PREDICTED;
            continue;
        }
        else if (line.find("MONTHLY_PREDICTED") != std::string::npos) {
            measurementType = MeasurementType::MONTHLY_PREDICTED;
            continue;
        }
        else if (line.find("MONTHLY_FIT") != std::string::npos) {
            measurementType = MeasurementType::MONTHLY_FIT;
            continue;
        }
        row.measurement = measurementType;

        // Construct the date from the first three tokens (year, month, day)
        row.date = Date(tokens[0] + " " + tokens[1] + " " + tokens[2], "%Y %m %d");

        // Bartels Solar Rotation Number and Number of Day within the Bartels 27-day cycle
        row.bsrn = std::stoi(tokens[3]);
        row.nd   = std::stoi(tokens[4]);

        // Read the Kp and Ap indices
        for (std::size_t ii = 0; ii < 8; ++ii) {
            row.kp[ii] = std::stoi(tokens[5 + ii]) * one;
            row.ap[ii] = std::stoi(tokens[14 + ii]) * one;
        }
        row.sumKp = std::stoi(tokens[13]) * one;
        row.avgAp = std::stoi(tokens[22]) * one;

        // Read the Cp, C9, and ISN values
        row.cp  = std::stoi(tokens[23]);
        row.c9  = std::stoi(tokens[24]);
        row.isn = std::stoi(tokens[25]);

        // Read the F10.7 solar flux values
        row.f107Obs.nominal              = std::stod(tokens[26]) * sfu;
        row.f107Obs.centered81DayAverage = std::stod(tokens[28]) * sfu; // skip the Q column
        row.f107Obs.last81DayAverage     = std::stod(tokens[29]) * sfu;

        row.f107Adj.nominal              = std::stod(tokens[30]) * sfu;
        row.f107Adj.centered81DayAverage = std::stod(tokens[31]) * sfu;
        row.f107Adj.last81DayAverage     = std::stod(tokens[32]) * sfu;

        // Store
        spaceWeatherParams.push_back(row);
    }

    return spaceWeatherParams;
}

} // namespace astro
} // namespace astrea