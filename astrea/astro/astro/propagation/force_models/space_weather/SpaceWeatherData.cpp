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
#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>

#include <astro/propagation/force_models/space_weather/file_reader.hpp>

namespace astrea {
namespace astro {

SpaceWeatherData::SpaceWeatherData(const std::filesystem::path& infile, std::optional<Date> startDate, std::optional<Date> endDate) :
    _infile(infile),
    _startDate(startDate),
    _endDate(endDate),
    _data(read_space_weather_file(infile, startDate, endDate))
{
}

[[nodiscard]] std::size_t SpaceWeatherData::size() const { return _data.size(); }

[[nodiscard]] const std::vector<SpaceWeatherParameters>& SpaceWeatherData::data() const { return _data; }

[[nodiscard]] const std::filesystem::path& SpaceWeatherData::infile() const noexcept { return _infile; }

[[nodiscard]] bool SpaceWeatherData::empty() const noexcept { return _data.empty(); }

[[nodiscard]] const SpaceWeatherParameters& SpaceWeatherData::operator[](std::size_t index) const
{
    return _data[index];
}

[[nodiscard]] SpaceWeatherParameters& SpaceWeatherData::operator[](std::size_t index) { return _data[index]; }

[[nodiscard]] const SpaceWeatherParameters& SpaceWeatherData::at(std::size_t index) const { return _data.at(index); }

[[nodiscard]] SpaceWeatherParameters& SpaceWeatherData::at(std::size_t index) { return _data.at(index); }

[[nodiscard]] const std::optional<Date>& SpaceWeatherData::startDate() const noexcept { return _startDate; }

[[nodiscard]] const std::optional<Date>& SpaceWeatherData::endDate() const noexcept { return _endDate; }

} // namespace astro
} // namespace astrea