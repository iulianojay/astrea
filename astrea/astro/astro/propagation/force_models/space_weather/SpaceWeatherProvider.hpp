/**
 * @file SpaceWeatherProvider.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Lightweight immutable provider for shared space weather data.
 * @date 2026-09-05
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

#include <memory>
#include <utility>

#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Lightweight provider that shares an immutable space weather data snapshot. Using this layer of abstraction
 * for now to enable data hot-swapping in the future if needed.
 */
class SpaceWeatherProvider {
  public:
    using DataPtr = std::shared_ptr<const SpaceWeatherData>;

    /**
     * @brief Default constructor for SpaceWeatherProvider.
     */
    SpaceWeatherProvider() = default;

    /**
     * @brief Construct a SpaceWeatherProvider with an explicit immutable space weather snapshot.
     *
     * @param data Shared immutable space weather data.
     */
    explicit SpaceWeatherProvider(DataPtr data) :
        _data(std::move(data))
    {
    }

    /**
     * @brief Construct a SpaceWeatherProvider with a pre-built space weather data object.
     *
     * @param data Space weather data to share.
     */
    explicit SpaceWeatherProvider(SpaceWeatherData data) :
        _data(std::make_shared<const SpaceWeatherData>(std::move(data)))
    {
    }

    /**
     * @brief Construct a SpaceWeatherProvider with a pre-built space weather data object in place.
     *
     * @param args Arguments to construct the SpaceWeatherData object.
     */
    template <typename... Args>
    explicit SpaceWeatherProvider(std::in_place_t, Args&&... args) :
        _data(std::make_shared<const SpaceWeatherData>(std::forward<Args>(args)...))
    {
    }

    /**
     * @brief Returns the number of space weather data entries.
     *
     * @return std::size_t The number of space weather data entries.
     */
    [[nodiscard]] std::size_t size() const { return _data ? _data->size() : 0; }

    /**
     * @brief Checks if the space weather data is empty.
     *
     * @return true If there are no space weather data entries.
     * @return false If there are space weather data entries.
     */
    [[nodiscard]] bool empty() const noexcept { return !_data || _data->empty(); }

    /**
     * @brief Access the space weather data snapshot.
     *
     * @return const DataPtr& Shared pointer to the immutable space weather data.
     */
    [[nodiscard]] const DataPtr& data() const noexcept { return _data; }

  private:
    DataPtr _data; //<! Shared immutable space weather data snapshot
};

} // namespace astro
} // namespace astrea