/**
 * @file GroundArchitecture.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief GroundArchitecture class definition
 * @date 2025-08-03
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

#include <vector>

#include <astro/systems/system_concepts.hpp>

#include <trace/platforms/ground/GroundStation.hpp>

namespace astrea {
namespace trace {

/**
 * @brief A collection of ground stations on the surface of a celestial body.
 *
 * This class manages and provides access to a set of ground stations, which can
 * be used for communication, observation, or data collection.
 *
 * @tparam _body_ The celestial body NTTP that all stations in this architecture reside on.
 */
template <astro::IsCelestialBody auto _body_>
class GroundArchitecture {
    using Station = GroundStation<_body_>;

  public:
    /**
     * @brief Constructs a GroundArchitecture with a list of ground stations.
     *
     * @param groundStations A vector of GroundStation objects representing the ground stations.
     */
    GroundArchitecture(const std::vector<Station>& groundStations) :
        _groundStations(groundStations)
    {
    }

    /**
     * @brief Default destructor for GroundArchitecture.
     */
    ~GroundArchitecture() = default;

    /**
     * @brief Access a ground station by index.
     *
     * @param idx The index of the ground station to access.
     * @return Station& Ground station at the specified index.
     */
    Station& operator[](const std::size_t& idx) { return _groundStations[idx]; }

    /**
     * @brief Access a ground station by index (const).
     *
     * @param idx The index of the ground station to access.
     * @return const Station& Ground station at the specified index.
     */
    const Station& operator[](const std::size_t& idx) const { return _groundStations[idx]; }

    /**
     * @brief Returns the number of ground stations in the architecture.
     *
     * @return std::size_t The number of ground stations.
     */
    std::size_t size() const { return _groundStations.size(); }

    /**
     * @brief Iterator type for the GroundArchitecture class.
     */
    using iterator = typename std::vector<Station>::iterator;

    /**
     * @brief Constant iterator type for the GroundArchitecture class.
     */
    using const_iterator = typename std::vector<Station>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the ground stations.
     *
     * @return An iterator to the first ground station.
     */
    iterator begin() { return _groundStations.begin(); }

    /**
     * @brief Returns an iterator to the end of the ground stations.
     *
     * @return An iterator to one past the last ground station.
     */
    iterator end() { return _groundStations.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground stations.
     *
     * @return A constant iterator to the first ground station.
     */
    const_iterator begin() const { return _groundStations.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground stations.
     *
     * @return A constant iterator to one past the last ground station.
     */
    const_iterator end() const { return _groundStations.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the ground stations.
     *
     * @return A constant iterator to the first ground station.
     */
    const_iterator cbegin() const { return _groundStations.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the ground stations.
     *
     * @return A constant iterator to one past the last ground station.
     */
    const_iterator cend() const { return _groundStations.end(); }

  private:
    std::vector<Station> _groundStations; //!< A vector containing the ground stations in this architecture.
};

} // namespace trace
} // namespace astrea