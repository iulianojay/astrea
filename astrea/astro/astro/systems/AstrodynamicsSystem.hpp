/**
 * @file AstrodynamicsSystem.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AstrodynamicsSystem class, which manages celestial bodies and their interactions.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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
#include <ranges>
#include <unordered_set>
#include <vector>

#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/types/type_traits.hpp>


namespace astrea {
namespace astro {

template <typename T>
concept IsDerivedCelestialBody = requires(T) {
    std::is_base_of<CelestialBody, T>::value;
    std::negation<std::is_same<CelestialBody, remove_cv_ref<T>>>::value;
};

/**
 * @class AstrodynamicsSystem
 * @brief Represents a system of celestial bodies and their interactions.
 *
 * This class manages celestial bodies, their properties, and provides methods to access them.
 */
class AstrodynamicsSystem {

    using BodyMap = std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr>;

  public:
    /**
     * @brief Constructs an AstrodynamicsSystem with a specified central body, and the set of all other bodies.
     *
     * @param centralBody The name of the central celestial body (default is "Earth").
     * @param allBodies A set of names of all secondary celestial bodies in the system (default is none).
     */
    AstrodynamicsSystem(const CelestialBodyId& centralBody = CelestialBodyId::EARTH, const std::unordered_set<CelestialBodyId>& secondaryBodies = {});

    /**
     * @brief Constructs an AstrodynamicsSystem with a specified central body, and the set of all other bodies.
     *
     * @param centralBody The central celestial body.
     * @param allBodies A set of all secondary celestial bodies in the system (default is none).
     */
    template <IsDerivedCelestialBody T>
    AstrodynamicsSystem(const T& centralBody, const std::unordered_set<CelestialBodyId>& secondaryBodies = {}) :
        _centerType(SystemCenter::CENTRAL_BODY),
        _centralBody(centralBody.get_id())
    {
        add_body(centralBody);
        for (const auto& body : secondaryBodies) {
            add_body(body);
        }
    }

    /**
     * @brief Default destructor for the AstrodynamicsSystem class.
     */
    ~AstrodynamicsSystem() = default;

    /**
     * @brief Copy constructor for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem(const AstrodynamicsSystem&);

    /**
     * @brief Assignment operator for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem& operator=(const AstrodynamicsSystem&);

    /**
     * @brief Default move constructor for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem(AstrodynamicsSystem&&) = default;

    /**
     * @brief Default move assignment operator for the AstrodynamicsSystem class.
     */
    AstrodynamicsSystem& operator=(AstrodynamicsSystem&&) = default;

    /**
     * @brief Creates a default AstrodynamicsSystem.
     *
     * @return A default AstrodynamicsSystem instance.
     */
    static AstrodynamicsSystem EarthMoon()
    {
        return AstrodynamicsSystem(CelestialBodyId::EARTH, { CelestialBodyId::MOON });
    }

    /**
     * @brief Returns the central celestial body of the system.
     *
     * @return const SystemCenter& The name of the central celestial body.
     */
    const SystemCenter& get_center_type() const;

    /**
     * @brief Returns the central celestial body ID.
     *
     * @return const CelestialBodyId& The ID of the central celestial body.
     */
    const CelestialBodyId& get_central_body_id() const;

    /**
     * @brief Returns the central celestial body as a CelestialBodyUniquePtr.
     *
     * @return const CelestialBodyUniquePtr& A pointer to the central celestial body.
     */
    const CelestialBodyUniquePtr& get_central_body() const;

    /**
     * @brief Return a specific celestial body by ID.
     *
     * @param id The ID of the celestial body to retrieve.
     * @return const CelestialBodyUniquePtr& A pointer to the celestial body with the specified ID.
     */
    const CelestialBodyUniquePtr& get_body(const CelestialBodyId& id) const;

    /**
     * @brief Build a celestial body by ID without storing it
     */
    CelestialBodyUniquePtr create_body(const CelestialBodyId& id) const;

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
    template <IsDerivedCelestialBody T, typename... Args>
    const CelestialBodyUniquePtr& add_body(Args&&... args)
    {
        const CelestialBodyId id = T::get_id();
        if (_bodies.count(id) == 0) {
            CelestialBodyUniquePtr body = std::make_unique<T>(std::forward<Args>(args)...);
            _bodies.emplace(id, std::move(body));
            _root = find_common_ancestor({ std::from_range, std::views::keys(_bodies) });
        }
        return get_body(id);
    }

    /**
     * @brief Create a celestial body by id.
     *
     * @param id The id of the celestial body to create.
     * @param system The astrodynamics system to which the body belongs.
     * @return const CelestialBodyUniquePtr& A pointer to the created celestial body.
     */
    const CelestialBodyUniquePtr& add_body(const CelestialBodyId& id);

    /**
     * @brief Store manually generated celestial body.
     *
     * @param id The id of the celestial body to create.
     * @param system The astrodynamics system to which the body belongs.
     * @return const CelestialBodyUniquePtr& A pointer to the created celestial body.
     */
    template <IsDerivedCelestialBody T>
    const CelestialBodyUniquePtr& add_body(const T& body)
    {
        const CelestialBodyId id = body.get_id();
        if (_bodies.count(id) == 0) {
            _bodies.emplace(id, std::make_unique<CelestialBody>(T(body)));
            _root = find_common_ancestor({ std::from_range, std::views::keys(_bodies) });
        }
        return get_body(id);
    }

    /**
     * @brief Returns a vector of all celestial bodies in the system.
     *
     * @return const std::vector<CelestialBodyUniquePtr>& A vector containing pointers to all celestial bodies in the system.
     */
    const BodyMap& get_all_bodies() const;

    /**
     * @brief Get the root object of the celestial body hierarchy.
     *
     * @return const CelestialBodyId& The name of the root celestial body.
     */
    const CelestialBodyId& get_system_root() const;

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
    const std::size_t size() const;

    /**
     * @brief Clears all celestial bodies managed by this factory.
     */
    void clear();

    /**
     * @brief Get the relative position between two celestial bodies at a specific date.
     *
     * @param date The date at which to get the relative position.
     * @param id1 The ID of the first celestial body.
     * @param id2 The ID of the second celestial body.
     * @return CartesianVector<Distance, frames::solar_system_barycenter::icrf> The relative position vector from id2 to id1.
     */
    CartesianVector<Distance, frames::solar_system_barycenter::icrf>
        get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const;

    /**
     * @brief Get the relative position between two celestial bodies at a specific date.
     *
     * @param date The date at which to get the relative position.
     * @param id1 The ID of the first celestial body.
     * @param id2 The ID of the second celestial body.
     * @return CartesianVector<Velocity, frames::solar_system_barycenter::icrf> The relative velocity vector from id2 to id1.
     */
    CartesianVector<Velocity, frames::solar_system_barycenter::icrf>
        get_relative_velocity(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const;

    /**
     * @brief Iterator type for iterating over celestial bodies.
     */
    using iterator = BodyMap::iterator;

    /**
     * @brief Constant iterator type for iterating over celestial bodies.
     */
    using const_iterator = BodyMap::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the celestial bodies.
     *
     * @return const_iterator An iterator to the first celestial body.
     */
    const_iterator begin() const { return _bodies.begin(); }

    /**
     * @brief Returns an iterator to the end of the celestial bodies.
     *
     * @return const_iterator An iterator to the end of the celestial bodies.
     */
    const_iterator end() const { return _bodies.end(); }

  private:
    SystemCenter _centerType;     //!< System center type, either "CENTRAL_BODY" or "BARYCENTER".
    CelestialBodyId _centralBody; //!< The id of the central body.
    CelestialBodyId _root;        //!< The root celestial body (first common lineage).
    BodyMap _bodies;              //!< Map of celestial bodies by enum.

    /**
     * @brief Finds the root celestial body in the hierarchy.
     *
     * @param bodies A set of celestial body IDs to consider.
     * @return CelestialBodyId The ID of the root celestial body.
     */
    CelestialBodyId find_common_ancestor(const std::unordered_set<CelestialBodyId>& bodies) const;

    /**
     * @brief Implementation function to create a celestial body by id.
     *
     * @param id The id of the celestial body to create.
     * @return CelestialBodyUniquePtr A unique pointer to the created celestial body.
     * @throws std::runtime_error If the celestial body ID is not implemented in the factory.
     * @note Dont judge me.
     */
    CelestialBodyUniquePtr create_impl(const CelestialBodyId& id) const;

    /**
     * @brief Get the position of a celestial body relative to the root at a specific date.
     *
     * @param date The date at which to get the position.
     * @param id The ID of the celestial body.
     * @return CartesianVector<Distance, frames::solar_system_barycenter::icrf> The position vector of the celestial body relative to the root.
     */
    CartesianVector<Distance, frames::solar_system_barycenter::icrf>
        get_position_relative_to_ancestor(const Date& date, const CelestialBodyId id, const CelestialBodyId ancestor) const;

    /**
     * @brief Get the velocity of a celestial body relative to the root at a specific date.
     *
     * @param date The date at which to get the velocity.
     * @param id The ID of the celestial body.
     * @return CartesianVector<Velocity, frames::solar_system_barycenter::icrf> The velocity vector of the celestial body relative to the root.
     */
    CartesianVector<Velocity, frames::solar_system_barycenter::icrf>
        get_velocity_relative_to_ancestor(const Date& date, const CelestialBodyId id, const CelestialBodyId ancestor) const;
};

} // namespace astro
} // namespace astrea