/**
 * @file CelestialBodyFactory.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Factory class for creating and managing celestial bodies in an astrodynamics system.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Unique pointer type for CelestialBody.
 */
using CelestialBodyUniquePtr = std::unique_ptr<CelestialBody>;

/**
 * @brief Factory class for creating and managing celestial bodies in an astrodynamics system.
 *
 * This class is responsible for creating celestial bodies from JSON files, managing their lifetimes,
 * and providing access to them through a unique pointer interface.
 */
class CelestialBodyFactory {
  public:
    /**
     * @brief Default constructor for CelestialBodyFactory.
     */
    CelestialBodyFactory() = default; // TODO: Hide this. Since CelestialBody now requires the AstrodynamicsSystem
                                      // it's built in as a reference, this factory shouldn't be able to exist outside
                                      // of a system. This likely has unintended consequences. Investigate

    /**
     * @brief Default destructor for CelestialBodyFactory.
     */
    ~CelestialBodyFactory() = default;

    /**
     * @brief Deleted copy constructor for CelestialBodyFactory.
     */
    CelestialBodyFactory(const CelestialBodyFactory&) = delete;

    /**
     * @brief Deleted copy assignment operator for CelestialBodyFactory.
     */
    CelestialBodyFactory operator=(const CelestialBodyFactory&) = delete;

    /**
     * @brief Creates a celestial body from a JSON file.
     *
     * @param name The name of the celestial body.
     * @param system The astrodynamics system to which the body belongs.
     * @return A unique pointer to the created CelestialBody.
     */
    const CelestialBodyUniquePtr& create(const std::string& name, const AstrodynamicsSystem& system);

    /**
     * @brief Gets a celestial body by name.
     *
     * @param name The name of the celestial body.
     * @return A unique pointer to the CelestialBody if found, otherwise nullptr.
     */
    const CelestialBodyUniquePtr& get(const std::string& name) const;

    /**
     * @brief Gets or creates a celestial body by name.
     *
     * If the body does not exist, it will be created using the default JSON file for that body.
     *
     * @param name The name of the celestial body.
     * @param system The astrodynamics system to which the body belongs.
     * @return A unique pointer to the CelestialBody.
     */
    const CelestialBodyUniquePtr& get_or_create(const std::string& name, const AstrodynamicsSystem& system);

    /**
     * @brief Gets all celestial bodies managed by this factory.
     *
     * @return const auto& A reference to the unordered map of celestial bodies.
     */
    const auto& get_all_bodies() const { return _bodies; }

    /**
     * @brief Returns the number of celestial bodies managed by this factory.
     *
     * @return const std::size_t The number of celestial bodies.
     */
    const std::size_t size() const { return _bodies.size(); }

    /**
     * @brief Clears all celestial bodies managed by this factory.
     */
    void clear() { return _bodies.clear(); }

    // void propagate_bodies(const Date& epoch, const Time& endTime);

    /**
     * @brief Get the root object of the celestial body hierarchy.
     *
     * @return const std::string& The name of the root celestial body.
     */
    const std::string& get_root() const { return _root; }

    /**
     * @brief Iterator type for iterating over celestial bodies.
     */
    using iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::iterator;

    /**
     * @brief Constant iterator type for iterating over celestial bodies.
     */
    using const_iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the celestial bodies.
     *
     * @return iterator An iterator to the first celestial body.
     */
    auto begin() const { return _bodies.begin(); }

    /**
     * @brief Returns an iterator to the end of the celestial bodies.
     *
     * @return iterator An iterator to the end of the celestial bodies.
     */
    auto end() const { return _bodies.end(); }

  private:
    std::unordered_map<std::string, CelestialBodyUniquePtr> _bodies; //!< Map of celestial bodies by name.
    std::string _root;                                               //!< The name of the root celestial body.

    /**
     * @brief Finds the root celestial body in the hierarchy.
     */
    void find_root();

    //!< Map of celestial body names to their corresponding JSON file paths.
    const std::unordered_map<std::string, std::string> _buildFiles = { { "Sun", "/data/planetary/Sun/Sun.json" },
                                                                       { "Mercury", "/data/planetary/Mercury/Mercury.json" },
                                                                       { "Venus", "/data/planetary/Venus/Venus.json" },
                                                                       { "Earth", "/data/planetary/Earth/Earth.json" },
                                                                       { "Moon", "/data/planetary/Earth/Moon.json" },
                                                                       { "Mars", "/data/planetary/Mars/Mars.json" },
                                                                       { "Phobos", "/data/planetary/Mars/Phobos.json" },
                                                                       { "Deimos", "/data/planetary/Mars/Deimos.json" },
                                                                       { "Jupiter", "/data/planetary/Jupiter/Jupiter.json" },
                                                                       { "Ganymede", "/data/planetary/Jupiter/Ganymede.json" },
                                                                       { "Callisto", "/data/planetary/Jupiter/Callisto.json" },
                                                                       { "Io", "/data/planetary/Jupiter/Io.json" },
                                                                       { "Europa", "/data/planetary/Jupiter/Europa.json" },
                                                                       { "Saturn", "/data/planetary/Saturn/Saturn.json" },
                                                                       { "Titan", "/data/planetary/Saturn/Titan.json" },
                                                                       { "Rhea", "/data/planetary/Saturn/Rhea.json" },
                                                                       { "Iapetus", "/data/planetary/Saturn/Iapetus.json" },
                                                                       { "Uranus", "/data/planetary/Uranus/Uranus.json" },
                                                                       { "Titania", "/data/planetary/Uranus/Titania.json" },
                                                                       { "Oberon", "/data/planetary/Uranus/Oberon.json" },
                                                                       { "Neptune", "/data/planetary/Neptune/Neptune.json" },
                                                                       { "Triton", "/data/planetary/Neptune/Triton.json" } };
};

} // namespace astro
} // namespace waveguide