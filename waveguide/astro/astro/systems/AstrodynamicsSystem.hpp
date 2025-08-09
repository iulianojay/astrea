/**
 * @file AstrodynamicsSystem.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AstrodynamicsSystem class, which manages celestial bodies and their interactions.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include <astro/systems/Barycenter.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyFactory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>


namespace waveguide {
namespace astro {

/**
 * @class AstrodynamicsSystem
 * @brief Represents a system of celestial bodies and their interactions.
 *
 * This class manages celestial bodies, their properties, and provides methods to access them.
 */
class AstrodynamicsSystem {
  public:
    /**
     * @brief Constructs an AstrodynamicsSystem with a specified central body, set of all bodies, and epoch.
     *
     * @param centralBody The name of the central celestial body (default is "Earth").
     * @param allBodies A set of names of all celestial bodies in the system (default includes "Earth" and "Moon").
     * @param epoch The epoch date for the system (default is J2000).
     */
    AstrodynamicsSystem(std::string centralBody = "Earth", std::unordered_set<std::string> allBodies = { "Earth", "Moon" }, Date epoch = J2000) :
        centralBody(centralBody),
        allBodies(allBodies),
        epoch(epoch)
    {
        create_all_bodies();
    };

    /**
     * @brief Default destructor for the AstrodynamicsSystem class.
     */
    ~AstrodynamicsSystem() = default;

    /**
     * @brief Deleted copy constructor for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem(const AstrodynamicsSystem&) = delete;

    /**
     * @brief Deleted assignment operator for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem operator=(const AstrodynamicsSystem&) = delete;

    /**
     * @brief Creates a default AstrodynamicsSystem.
     *
     * @return A default AstrodynamicsSystem instance.
     */
    static AstrodynamicsSystem DEFAULT() { return AstrodynamicsSystem(); }

    /**
     * @brief Returns the central celestial body of the system.
     *
     * @return const std::string& The name of the central celestial body.
     */
    const std::string& center() const { return centralBody; }

    /**
     * @brief Returns the central celestial body as a CelestialBodyUniquePtr.
     *
     * @return const CelestialBodyUniquePtr& A pointer to the central celestial body.
     */
    const CelestialBodyUniquePtr& get_center() const { return bodyFactory.get(centralBody); }

    /**
     * @brief Return a specific celestial body by name.
     *
     * @param name The name of the celestial body to retrieve.
     * @return const CelestialBodyUniquePtr& A pointer to the celestial body with the specified name.
     */
    const CelestialBodyUniquePtr& get(const std::string& name) const { return bodyFactory.get(name); }

    /**
     * @brief Get or create a celestial body by name.
     *
     * @param name The name of the celestial body to retrieve or create.
     * @return const CelestialBodyUniquePtr& A pointer to the celestial body with the specified name, creating it if it does not exist.
     */
    const CelestialBodyUniquePtr& get_or_create(const std::string& name)
    {
        return bodyFactory.get_or_create(name, *this);
    }

    /**
     * @brief Returns a vector of all celestial bodies in the system.
     *
     * @return const std::unordered_set<std::string>& A set containing the names of all celestial bodies in the system.
     */
    const std::unordered_set<std::string>& all_bodies() const { return allBodies; }

    /**
     * @brief Returns a vector of all celestial bodies in the system.
     *
     * @return const std::vector<CelestialBodyUniquePtr>& A vector containing pointers to all celestial bodies in the system.
     */
    const auto& get_all_bodies() const { return bodyFactory.get_all_bodies(); }

    // RadiusVector<ECI> get_radius_to_center(CelestialBody target, double date); //TODO: Implement

    /**
     * @brief Iterator for iterating over celestial bodies in the system.
     */
    using iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::iterator;

    /**
     * @brief Const iterator for iterating over celestial bodies in the system.
     */
    using const_iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the celestial bodies in the system.
     *
     * @return iterator An iterator pointing to the first celestial body.
     */
    auto begin() const { return bodyFactory.begin(); }

    /**
     * @brief Returns an iterator to the end of the celestial bodies in the system.
     *
     * @return iterator An iterator pointing to one past the last celestial body.
     */
    auto end() const { return bodyFactory.end(); }

  private:
    const std::string centralBody; //!< The name of the central celestial body, default is "Earth".
    const std::unordered_set<std::string> allBodies; //!< A set of names of all celestial bodies in the system, default includes "Earth" and "Moon".

    Date epoch;                       //!< The epoch date for the system, default is J2000.
    CelestialBodyFactory bodyFactory; //!< Factory for creating and managing celestial bodies in the system.

    /**
     * @brief Creates all celestial bodies in the system based on the provided names.
     *
     * This method initializes the celestial bodies defined in the `allBodies` set.
     */
    void create_all_bodies();
};

} // namespace astro
} // namespace waveguide