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
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>
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
    constexpr AstrodynamicsSystem(const PlanetaryBody& centralBody = PlanetaryBody::EARTH, const std::unordered_set<PlanetaryBody>& secondaryBodies = {}) :
        _centerType(SystemCenter::CENTRAL_BODY),
        _centralBody(centralBody)
    {
        create(centralBody);
        for (const auto& body : secondaryBodies) {
            create(body);
        }
    }

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
    static constexpr AstrodynamicsSystem EarthMoon()
    {
        return AstrodynamicsSystem(PlanetaryBody::EARTH, { PlanetaryBody::MOON });
    }

    /**
     * @brief Returns the central celestial body of the system.
     *
     * @return const SystemCenter& The name of the central celestial body.
     */
    constexpr const SystemCenter& get_center_type() const { return _centerType; }

    /**
     * @brief Returns the central celestial body as a CelestialBodyUniquePtr.
     *
     * @return const CelestialBodyUniquePtr& A pointer to the central celestial body.
     */
    constexpr const CelestialBodyUniquePtr& get_central_body() const
    {
        switch (_centerType) {
            case SystemCenter::CENTRAL_BODY: return get(_centralBody);
            case SystemCenter::BARYCENTER:
            default: throw std::runtime_error("Barycenteric systems have no central body.");
        }
    }

    /**
     * @brief Return a specific celestial body by ID.
     *
     * @param id The ID of the celestial body to retrieve.
     * @return const CelestialBodyUniquePtr& A pointer to the celestial body with the specified ID.
     */
    constexpr const CelestialBodyUniquePtr& get(const PlanetaryBody& id) const
    {
        if (_bodies.count(id) > 0) { return _bodies.at(id); }
        throw std::out_of_range("Input gravitational body not found.");
    }

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
    constexpr const CelestialBodyUniquePtr& create(Args&&... args)
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
    constexpr const CelestialBodyUniquePtr& create(const PlanetaryBody& id)
    {
        using namespace planetary_bodies;
        if (_bodies.count(id) == 0) {
            switch (id) {
                case (PlanetaryBody::SUN): {
                    _bodies.emplace(id, std::make_unique<Sun>());
                    break;
                }
                case (PlanetaryBody::MERCURY): {
                    _bodies.emplace(id, std::make_unique<Mercury>());
                    break;
                }
                case (PlanetaryBody::VENUS): {
                    _bodies.emplace(id, std::make_unique<Venus>());
                    break;
                }
                case (PlanetaryBody::EARTH): {
                    _bodies.emplace(id, std::make_unique<Earth>());
                    break;
                }
                case (PlanetaryBody::MOON): {
                    _bodies.emplace(id, std::make_unique<Moon>());
                    break;
                }
                case (PlanetaryBody::MARS): {
                    _bodies.emplace(id, std::make_unique<Mars>());
                    break;
                }
                case (PlanetaryBody::PHOBOS): {
                    _bodies.emplace(id, std::make_unique<Phobos>());
                    break;
                }
                case (PlanetaryBody::DEIMOS): {
                    _bodies.emplace(id, std::make_unique<Deimos>());
                    break;
                }
                case (PlanetaryBody::JUPITER): {
                    _bodies.emplace(id, std::make_unique<Jupiter>());
                    break;
                }
                case (PlanetaryBody::GANYMEDE): {
                    _bodies.emplace(id, std::make_unique<Ganymede>());
                    break;
                }
                case (PlanetaryBody::CALLISTO): {
                    _bodies.emplace(id, std::make_unique<Callisto>());
                    break;
                }
                case (PlanetaryBody::IO): {
                    _bodies.emplace(id, std::make_unique<Io>());
                    break;
                }
                case (PlanetaryBody::EUROPA): {
                    _bodies.emplace(id, std::make_unique<Europa>());
                    break;
                }
                case (PlanetaryBody::SATURN): {
                    _bodies.emplace(id, std::make_unique<Saturn>());
                    break;
                }
                case (PlanetaryBody::TITAN): {
                    _bodies.emplace(id, std::make_unique<Titan>());
                    break;
                }
                case (PlanetaryBody::RHEA): {
                    _bodies.emplace(id, std::make_unique<Rhea>());
                    break;
                }
                case (PlanetaryBody::IAPETUS): {
                    _bodies.emplace(id, std::make_unique<Iapetus>());
                    break;
                }
                case (PlanetaryBody::URANUS): {
                    _bodies.emplace(id, std::make_unique<Uranus>());
                    break;
                }
                case (PlanetaryBody::TITANIA): {
                    _bodies.emplace(id, std::make_unique<Titania>());
                    break;
                }
                case (PlanetaryBody::OBERON): {
                    _bodies.emplace(id, std::make_unique<Oberon>());
                    break;
                }
                case (PlanetaryBody::NEPTUNE): {
                    _bodies.emplace(id, std::make_unique<Neptune>());
                    break;
                }
                case (PlanetaryBody::TRITON): {
                    _bodies.emplace(id, std::make_unique<Triton>());
                    break;
                }
                default: throw std::runtime_error("Error: Celestial body not implemented in factory.");
            }

            _activeBodies.insert(id);
            find_system_root();
        }

        return get(id);
    }


    /**
     * @brief Returns a vector of all celestial bodies in the system.
     *
     * @return const std::vector<CelestialBodyUniquePtr>& A vector containing pointers to all celestial bodies in the system.
     */
    constexpr const auto& get_all_bodies() const { return _bodies; }

    /**
     * @brief Get the root object of the celestial body hierarchy.
     *
     * @return const PlanetaryBody& The name of the root celestial body.
     */
    constexpr const PlanetaryBody& get_system_root() const { return _root; }

    /**
     * @brief Get the gravitational parameter (mu) of the central body.
     *
     * @return GravParam The gravitational parameter of the central body.
     */
    constexpr GravParam get_mu() const
    {
        switch (_centerType) {
            case SystemCenter::CENTRAL_BODY: return get_central_body()->get_mu();
            case SystemCenter::BARYCENTER:
                throw std::runtime_error("Barycenteric systems have not been implemented yet.");
            default: throw std::runtime_error("AstrodynamicsSystem::get_mu: Unknown system center type.");
        }
    }

    /**
     * @brief Returns the number of celestial bodies managed by this factory.
     *
     * @return const std::size_t The number of celestial bodies.
     */
    constexpr const std::size_t size() const { return _bodies.size(); }

    /**
     * @brief Clears all celestial bodies managed by this factory.
     */
    constexpr void clear() { return _bodies.clear(); }

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
    constexpr auto begin() const { return _bodies.begin(); }

    /**
     * @brief Returns an iterator to the end of the celestial bodies.
     *
     * @return iterator An iterator to the end of the celestial bodies.
     */
    constexpr auto end() const { return _bodies.end(); }

  private:
    SystemCenter _centerType;                        //!< System center type, either "CENTRAL_BODY" or "BARYCENTER".
    PlanetaryBody _centralBody;                      //!< The id of the central body.
    std::unordered_set<PlanetaryBody> _activeBodies; //!< Set of names of all celestial bodies in the system.
    PlanetaryBody _root;                             //!< The root celestial body (first common lineage).
    std::unordered_map<PlanetaryBody, CelestialBodyUniquePtr> _bodies; //!< Map of celestial bodies by enum.

    /**
     * @brief Finds the root celestial body in the hierarchy.
     */
    constexpr void find_system_root()
    {
        // Count total planets
        std::size_t planetCount = 0;
        for (const auto& id : _activeBodies) {
            const auto& body = get(id);
            if (body->get_type() == CelestialBodyType::PLANET) {
                planetCount++;
                _root = id;
            }
        }

        // Check if other bodies are children of only planet -
        // assumes the common root cannot be a satellite
        if (planetCount == 1) {
            for (const auto& id : _activeBodies) {
                PlanetaryBody parentId = id;
                while (parentId != PlanetaryBody::SUN && parentId != _root) {
                    parentId = create(parentId)->get_parent();
                    _activeBodies.erase(parentId);
                }

                // If any object not in same planetary system, the common root
                // must be the Sun
                if (parentId == PlanetaryBody::SUN) {
                    _root = PlanetaryBody::SUN;
                    break;
                }
            }
        }
        else {
            // The only common root for multiple planets is the Sun
            _root = PlanetaryBody::SUN;
        }
    }
};

} // namespace astro
} // namespace astrea