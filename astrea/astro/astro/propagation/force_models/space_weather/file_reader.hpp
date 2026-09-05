/**
 * @file file_reader.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the file_reader function, which reads space weather data from files.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <optional>

#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace space_weather {

/**
 * @brief Reads space weather data from a file and returns it as a SpaceWeatherData object.
 *
 * @param filePath The path to the space weather data file.
 * @param startDate Optional start date for filtering the data. If provided, only data on or after this date will be included.
 * @param endDate Optional end date for filtering the data. If provided, only data on or before this date will be included.
 * @return A SpaceWeatherData object containing the parsed space weather data.
 */
SpaceWeatherData
    read_space_weather_file(const std::string& filePath, std::optional<Date> startDate = std::nullopt, std::optional<Date> endDate = std::nullopt);

} // namespace space_weather
} // namespace astro
} // namespace astrea