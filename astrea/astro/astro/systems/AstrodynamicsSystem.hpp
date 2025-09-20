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

#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>


namespace astrea {
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
     * @brief Constructs an AstrodynamicsSystem with a specified central body, and the set of all other bodies.
     *
     * @param centralBody The name of the central celestial body (default is "Earth").
     * @param allBodies A set of names of all secondary celestial bodies in the system (default is the "Moon").
     */
    AstrodynamicsSystem(const PlanetaryBody& centralBody = PlanetaryBody::EARTH, const std::unordered_set<PlanetaryBody>& secondaryBodies = {});

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
    static AstrodynamicsSystem EarthMoon();

    /**
     * @brief Returns the central celestial body of the system.
     *
     * @return const SystemCenter& The name of the central celestial body.
     */
    const SystemCenter& get_center_type() const;

    /**
     * @brief Returns the central celestial body as a CelestialBodyUniquePtr.
     *
     * @return const CelestialBodyUniquePtr& A pointer to the central celestial body.
     */
    const CelestialBodyUniquePtr& get_central_body() const;

    /**
     * @brief Return a specific celestial body by name.
     *
     * @param name The name of the celestial body to retrieve.
     * @return const CelestialBodyUniquePtr& A pointer to the celestial body with the specified name.
     */
    const CelestialBodyUniquePtr& get(const PlanetaryBody& name) const;

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
    const CelestialBodyUniquePtr& create(Args&&... args)
    {
        const PlanetaryBody id = T::get_id();
        if (_bodies.count(id) == 0) {
            CelestialBodyUniquePtr body = std::make_unique<T>(std::forward<Args>(args)...);
            body->assign_system(*this);
            _bodies.emplace(id, std::move(body));

            _activeBodies.insert(id);
            find_system_root();
        }
        return get(id);
    }

    /**
     * @brief Create a celestial body by id.
     *
     * @param id The id of the celestial body to create.
     * @param system The astrodynamics system to which the body belongs.
     * @return const CelestialBodyUniquePtr& A pointer to the created celestial body.
     */
    const CelestialBodyUniquePtr& create(const PlanetaryBody& id);

    /**
     * @brief Returns a vector of all celestial bodies in the system.
     *
     * @return const std::vector<CelestialBodyUniquePtr>& A vector containing pointers to all celestial bodies in the system.
     */
    const auto& get_all_bodies() const { return _bodies; }

    /**
     * @brief Get the root object of the celestial body hierarchy.
     *
     * @return const PlanetaryBody& The name of the root celestial body.
     */
    const PlanetaryBody& get_system_root() const { return _root; }

    /**
     * @brief Get the gravitational parameter (mu) of the central body.
     *
     * @return GravParam The gravitational parameter of the central body.
     */
    GravParam get_mu() const;

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

    // RadiusVector<ECI> get_radius_to_center(CelestialBody target, double date); //TODO: Implement

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
    SystemCenter _centerType;                        //!< System center type, either "CENTRAL_BODY" or "BARYCENTER".
    PlanetaryBody _centralBody;                      //!< The id of the central body.
    std::unordered_set<PlanetaryBody> _activeBodies; //!< Set of names of all celestial bodies in the system.
    PlanetaryBody _root;                             //!< The root celestial body (first common lineage).
    std::unordered_map<PlanetaryBody, CelestialBodyUniquePtr> _bodies; //!< Map of celestial bodies by enum.

    /**
     * @brief Creates all celestial bodies in the system based on the provided names.
     *
     * This method initializes the celestial bodies defined in the `allBodies` set.
     */
    void create_all_bodies();

    /**
     * @brief Finds the root celestial body in the hierarchy.
     */
    void find_system_root();
};

} // namespace astro
} // namespace astrea