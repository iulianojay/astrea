/**
 * @file GroundArchitecture.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief GroundArchitecture class definition
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <trace/platforms/ground/GroundStation.hpp>

namespace astrea {
namespace trace {

/**
 * @brief GroundArchitecture class represents a collection of ground stations.
 *
 * This class is used to manage and access a set of ground stations, which can be used for various purposes such as communication, observation, or data collection.
 */
class GroundArchitecture {
  public:
    /**
     * @brief Constructs a GroundArchitecture with a list of ground stations.
     *
     * @param groundStations A vector of GroundStation objects representing the ground stations.
     */
    GroundArchitecture(const std::vector<GroundStation>& groundStations) :
        _groundStations(groundStations)
    {
    }

    /**
     * @brief Default destructor for GroundArchitecture.
     */
    ~GroundArchitecture() = default;

    /**
     * @brief Access operator for GroundStation.
     *
     * @param idx The index of the ground station to access.
     * @return GroundStation& Ground station at the specified index.
     */
    GroundStation& operator[](const std::size_t& idx) { return _groundStations[idx]; }

    /**
     * @brief Access operator for GroundStation (const).
     *
     * @param idx The index of the ground station to access.
     * @return const GroundStation& Ground station at the specified index.
     */
    const GroundStation& operator[](const std::size_t& idx) const { return _groundStations[idx]; }

    /**
     * @brief Returns the number of ground stations in the architecture.
     *
     * @return std::size_t The number of ground stations.
     */
    std::size_t size() const { return _groundStations.size(); }

    /**
     * @brief Iterator type for the GroundArchitecture class.
     */
    using iterator = std::vector<GroundStation>::iterator;

    /**
     * @brief Constant iterator type for the GroundArchitecture class.
     */
    using const_iterator = std::vector<GroundStation>::const_iterator;

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
    std::vector<GroundStation> _groundStations; ///< A vector containing the ground stations in this architecture.
};

} // namespace trace
} // namespace astrea