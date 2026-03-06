

# File AstrodynamicsSystem.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**AstrodynamicsSystem.hpp**](AstrodynamicsSystem_8hpp.md)

[Go to the documentation of this file](AstrodynamicsSystem_8hpp.md)


```C++

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

class AstrodynamicsSystem {
  public:
    constexpr AstrodynamicsSystem(
        const CelestialBodyId& centralBody                         = CelestialBodyId::EARTH,
        const std::unordered_set<CelestialBodyId>& secondaryBodies = {}
    ) :
        _centerType(SystemCenter::CENTRAL_BODY),
        _centralBody(centralBody)
    {
        add_body(centralBody);
        for (const auto& body : secondaryBodies) {
            add_body(body);
        }
    }

    constexpr AstrodynamicsSystem(const CelestialBody& centralBody, const std::unordered_set<CelestialBodyId>& secondaryBodies = {}) :
        _centerType(SystemCenter::CENTRAL_BODY),
        _centralBody(centralBody.get_id())
    {
        add_body(centralBody);
        for (const auto& body : secondaryBodies) {
            add_body(body);
        }
    }

    constexpr AstrodynamicsSystem(const CelestialBody& centralBody, const std::unordered_set<CelestialBody>& secondaryBodies = {}) :
        _centerType(SystemCenter::CENTRAL_BODY),
        _centralBody(centralBody.get_id())
    {
        add_body(centralBody);
        for (const auto& body : secondaryBodies) {
            add_body(body);
        }
    }

    ~AstrodynamicsSystem() = default;

    AstrodynamicsSystem(const AstrodynamicsSystem&) = delete;

    AstrodynamicsSystem& operator=(const AstrodynamicsSystem&) = delete;

    AstrodynamicsSystem(AstrodynamicsSystem&&) = default;

    AstrodynamicsSystem& operator=(AstrodynamicsSystem&&) = default;

    static constexpr AstrodynamicsSystem EarthMoon()
    {
        return AstrodynamicsSystem(CelestialBodyId::EARTH, { CelestialBodyId::MOON });
    }

    constexpr const SystemCenter& get_center_type() const { return _centerType; }

    constexpr const CelestialBodyId& get_central_body_id() const { return _centralBody; }

    constexpr const CelestialBodyUniquePtr& get_central_body() const
    {
        switch (_centerType) {
            case SystemCenter::CENTRAL_BODY: return get_body(_centralBody);
            case SystemCenter::BARYCENTER:
            default: throw std::runtime_error("Barycenteric systems have no central body.");
        }
    }

    constexpr const CelestialBodyUniquePtr& get_body(const CelestialBodyId& id) const
    {
        if (_bodies.count(id) > 0) { return _bodies.at(id); }
        throw std::out_of_range("Input gravitational body not found.");
    }

    template <typename T, typename... Args>
        requires(std::is_base_of<CelestialBody, T>::value)
    constexpr const CelestialBodyUniquePtr& add_body(Args&&... args)
    {
        const CelestialBodyId id = T::get_id();
        if (_bodies.count(id) == 0) {
            CelestialBodyUniquePtr body = std::make_unique<T>(std::forward<Args>(args)...);
            _bodies.emplace(id, std::move(body));
            _activeBodies.insert(id);
            _root = find_common_root(_activeBodies);
        }
        return get_body(id);
    }

    constexpr const CelestialBodyUniquePtr& add_body(const CelestialBodyId& id)
    {
        if (_bodies.count(id) == 0) {
            _bodies.emplace(id, create_impl(id));
            _activeBodies.insert(id);
            _root = find_common_root(_activeBodies);
        }

        return get_body(id);
    }

    constexpr const CelestialBodyUniquePtr& add_body(const CelestialBody& body)
    {
        const CelestialBodyId id = body.get_id();
        if (_bodies.count(id) == 0) {
            _bodies.emplace(id, std::make_unique<CelestialBody>(body));
            _activeBodies.insert(id);
            _root = find_common_root(_activeBodies);
        }
        return get_body(id);
    }

    constexpr CelestialBodyUniquePtr add_body(const CelestialBodyId& id) const { return create_impl(id); }

    constexpr const auto& get_all_bodies() const { return _bodies; }

    constexpr const CelestialBodyId& get_system_root() const { return _root; }

    constexpr GravParam get_mu() const
    {
        switch (_centerType) {
            case SystemCenter::CENTRAL_BODY: return get_central_body()->get_mu();
            case SystemCenter::BARYCENTER:
                throw std::runtime_error("Barycenteric systems have not been implemented yet.");
            default: throw std::runtime_error("AstrodynamicsSystem::get_mu: Unknown system center type.");
        }
    }

    constexpr const std::size_t size() const { return _bodies.size(); }

    constexpr void clear() { return _bodies.clear(); }

    CartesianVector<Distance, frames::solar_system_barycenter::icrf>
        get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const;

    using iterator = std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr>::iterator;

    using const_iterator = std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr>::const_iterator;

    constexpr auto begin() const { return _bodies.begin(); }

    constexpr auto end() const { return _bodies.end(); }

  private:
    SystemCenter _centerType;                          
    CelestialBodyId _centralBody;                      
    std::unordered_set<CelestialBodyId> _activeBodies; 
    CelestialBodyId _root;                             
    std::unordered_map<CelestialBodyId, CelestialBodyUniquePtr> _bodies; 

    constexpr CelestialBodyId find_common_root(const std::unordered_set<CelestialBodyId>& bodies)
    {
        // If there's only one body, it is the root
        if (bodies.size() == 1) { return *(bodies.begin()); }

        // Count total planets
        CelestialBodyId root;
        std::size_t planetCount = 0;
        for (const auto& id : bodies) {
            const auto& body = get_body(id);
            if (body->get_type() == CelestialBodyType::PLANET) {
                planetCount++;
                root = id;
            }
        }

        // Check if other bodies are children of only planet -
        // assumes the common root cannot be a satellite
        if (planetCount == 1) {
            for (const auto& id : bodies) {
                CelestialBodyId parentId = id;
                while (parentId != CelestialBodyId::SUN && parentId != _root) {
                    // Don't add parent to active bodies if it's not already there
                    parentId = add_body(parentId)->get_parent();
                }

                // If any object not in same planetary system, the common root
                // must be the Sun
                if (parentId == CelestialBodyId::SUN) {
                    root = CelestialBodyId::SUN;
                    break;
                }
            }
        }
        else {
            // The only common root for multiple planets is the Sun
            root = CelestialBodyId::SUN;
        }

        return root;
    }

    constexpr CelestialBodyUniquePtr create_impl(const CelestialBodyId& id) const
    {
        using namespace planetary_bodies;
        switch (id) {
            case (CelestialBodyId::SUN): {
                return std::make_unique<Sun>();
            }
            case (CelestialBodyId::MERCURY): {
                return std::make_unique<Mercury>();
            }
            case (CelestialBodyId::VENUS): {
                return std::make_unique<Venus>();
            }
            case (CelestialBodyId::EARTH): {
                return std::make_unique<Earth>();
            }
            case (CelestialBodyId::MOON): {
                return std::make_unique<Moon>();
            }
            case (CelestialBodyId::MARS): {
                return std::make_unique<Mars>();
            }
            case (CelestialBodyId::PHOBOS): {
                return std::make_unique<Phobos>();
            }
            case (CelestialBodyId::DEIMOS): {
                return std::make_unique<Deimos>();
            }
            case (CelestialBodyId::JUPITER): {
                return std::make_unique<Jupiter>();
            }
            case (CelestialBodyId::GANYMEDE): {
                return std::make_unique<Ganymede>();
            }
            case (CelestialBodyId::CALLISTO): {
                return std::make_unique<Callisto>();
            }
            case (CelestialBodyId::IO): {
                return std::make_unique<Io>();
            }
            case (CelestialBodyId::EUROPA): {
                return std::make_unique<Europa>();
            }
            case (CelestialBodyId::SATURN): {
                return std::make_unique<Saturn>();
            }
            case (CelestialBodyId::TITAN): {
                return std::make_unique<Titan>();
            }
            case (CelestialBodyId::RHEA): {
                return std::make_unique<Rhea>();
            }
            case (CelestialBodyId::IAPETUS): {
                return std::make_unique<Iapetus>();
            }
            case (CelestialBodyId::URANUS): {
                return std::make_unique<Uranus>();
            }
            case (CelestialBodyId::TITANIA): {
                return std::make_unique<Titania>();
            }
            case (CelestialBodyId::OBERON): {
                return std::make_unique<Oberon>();
            }
            case (CelestialBodyId::NEPTUNE): {
                return std::make_unique<Neptune>();
            }
            case (CelestialBodyId::TRITON): {
                return std::make_unique<Triton>();
            }
            default: throw std::runtime_error("Error: Celestial body not implemented in factory.");
        }
    }
};

} // namespace astro
} // namespace astrea
```


