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

#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
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
    const CelestialBodyUniquePtr& create(const PlanetaryBody& id, const AstrodynamicsSystem& system);

    /**
     * @brief Creates a celestial body of a specific type.
     *
     * This method allows for the creation of celestial bodies of derived types, such as specific planets or moons.
     * The created body is assigned to the provided astrodynamics system.
     *
     * @tparam T The type of celestial body to create, must be derived from CelestialBody.
     * @tparam Args The types of arguments to pass to the constructor of T.
     * @param args The arguments to pass to the constructor of T.
     * @param system The astrodynamics system to which the body belongs.
     * @return A unique pointer to the created CelestialBody of type T.
     */
    template <typename T, typename... Args>
        requires(std::is_base_of<CelestialBody, T>::value)
    const CelestialBodyUniquePtr& create(Args&&... args, const AstrodynamicsSystem& system)
    {
        const PlanetaryBody id = T::get_id();
        if (_bodies.count(id) == 0) {
            CelestialBodyUniquePtr body = std::make_unique<T>(std::forward<Args>(args)...);
            body->assign_system(system);
            _bodies.emplace(id, std::move(body));
        }
        return get(id);
    }

    /**
     * @brief Gets a celestial body by ID.
     *
     * @param id The ID of the celestial body.
     * @return A unique pointer to the CelestialBody if found, otherwise nullptr.
     */
    const CelestialBodyUniquePtr& get(const PlanetaryBody& id) const;

    /**
     * @brief Gets or creates a celestial body by ID.
     *
     * If the body does not exist, it will be created using the default JSON file for that body.
     *
     * @param id The ID of the celestial body.
     * @param system The astrodynamics system to which the body belongs.
     * @return A unique pointer to the CelestialBody.
     */
    const CelestialBodyUniquePtr& get_or_create(const PlanetaryBody& id, const AstrodynamicsSystem& system);

    /**
     * @brief Gets or creates a celestial body of a specific type.
     *
     * This method allows for the retrieval or creation of celestial bodies of derived types, such as specific planets
     * or moons. If the body does not exist, it will be created using the provided constructor arguments.
     *
     * @tparam T The type of celestial body to get or create, must be derived from CelestialBody.
     * @tparam Args The types of arguments to pass to the constructor of T.
     * @param args The arguments to pass to the constructor of T.
     * @param system The astrodynamics system to which the body belongs.
     * @return A unique pointer to the CelestialBody of type T.
     */
    template <typename T, typename... Args>
        requires(std::is_base_of<CelestialBody, T>::value)
    const CelestialBodyUniquePtr& get_or_create(Args&&... args, const AstrodynamicsSystem& system)
    {
        const PlanetaryBody id = T::get_id();
        if (_bodies.count(id) == 0) { return create<T>(args..., system); }
        return _bodies.at(id);
    }

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
     * @brief Iterator type for iterating over celestial bodies.
     */
    using iterator = std::unordered_map<PlanetaryBody, CelestialBodyUniquePtr>::iterator;

    /**
     * @brief Constant iterator type for iterating over celestial bodies.
     */
    using const_iterator = std::unordered_map<PlanetaryBody, CelestialBodyUniquePtr>::const_iterator;

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
    std::unordered_map<PlanetaryBody, CelestialBodyUniquePtr> _bodies; //!< Map of celestial bodies by enum.

    //!< Map of celestial body names to their corresponding JSON file paths.
    const std::unordered_map<PlanetaryBody, std::filesystem::path> _buildFiles = {
        { PlanetaryBody::SUN, "data/planetary/Sun/Sun.json" },
        { PlanetaryBody::MERCURY, "data/planetary/Mercury/Mercury.json" },
        { PlanetaryBody::VENUS, "data/planetary/Venus/Venus.json" },
        { PlanetaryBody::EARTH, "data/planetary/Earth/Earth.json" },
        { PlanetaryBody::MOON, "data/planetary/Earth/Moon.json" },
        { PlanetaryBody::MARS, "data/planetary/Mars/Mars.json" },
        { PlanetaryBody::PHOBOS, "data/planetary/Mars/Phobos.json" },
        { PlanetaryBody::DEIMOS, "data/planetary/Mars/Deimos.json" },
        { PlanetaryBody::JUPITER, "data/planetary/Jupiter/Jupiter.json" },
        { PlanetaryBody::GANYMEDE, "data/planetary/Jupiter/Ganymede.json" },
        { PlanetaryBody::CALLISTO, "data/planetary/Jupiter/Callisto.json" },
        { PlanetaryBody::IO, "data/planetary/Jupiter/Io.json" },
        { PlanetaryBody::EUROPA, "data/planetary/Jupiter/Europa.json" },
        { PlanetaryBody::SATURN, "data/planetary/Saturn/Saturn.json" },
        { PlanetaryBody::TITAN, "data/planetary/Saturn/Titan.json" },
        { PlanetaryBody::RHEA, "data/planetary/Saturn/Rhea.json" },
        { PlanetaryBody::IAPETUS, "data/planetary/Saturn/Iapetus.json" },
        { PlanetaryBody::URANUS, "data/planetary/Uranus/Uranus.json" },
        { PlanetaryBody::TITANIA, "data/planetary/Uranus/Titania.json" },
        { PlanetaryBody::OBERON, "data/planetary/Uranus/Oberon.json" },
        { PlanetaryBody::NEPTUNE, "data/planetary/Neptune/Neptune.json" },
        { PlanetaryBody::TRITON, "data/planetary/Neptune/Triton.json" }
    };
};

} // namespace astro
} // namespace astrea