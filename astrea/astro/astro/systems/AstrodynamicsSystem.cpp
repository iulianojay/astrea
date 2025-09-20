#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/state/StateHistory.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

namespace astrea {
namespace astro {

AstrodynamicsSystem::AstrodynamicsSystem(const PlanetaryBody& centralBody, const std::unordered_set<PlanetaryBody>& secondaryBodies) :
    _centerType(SystemCenter::CENTRAL_BODY),
    _centralBody(centralBody)
{
    create(centralBody);
    for (const auto& body : secondaryBodies) {
        create(body);
    }
};

AstrodynamicsSystem AstrodynamicsSystem::EarthMoon()
{
    return AstrodynamicsSystem(PlanetaryBody::EARTH, { PlanetaryBody::MOON });
}

const SystemCenter& AstrodynamicsSystem::get_center_type() const { return _centerType; }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_central_body() const
{
    switch (_centerType) {
        case SystemCenter::CENTRAL_BODY: return get(_centralBody);
        case SystemCenter::BARYCENTER:
        default: throw std::runtime_error("Barycenteric systems have no central body.");
    }
}

const CelestialBodyUniquePtr& AstrodynamicsSystem::create(const PlanetaryBody& id)
{
    using namespace planetary_bodies;
    if (_bodies.count(id) == 0) {
        switch (id) {
            case (PlanetaryBody::SUN): {
                _bodies.emplace(id, std::make_unique<Sun>(*this));
                break;
            }
            case (PlanetaryBody::MERCURY): {
                _bodies.emplace(id, std::make_unique<Mercury>(*this));
                break;
            }
            case (PlanetaryBody::VENUS): {
                _bodies.emplace(id, std::make_unique<Venus>(*this));
                break;
            }
            case (PlanetaryBody::EARTH): {
                _bodies.emplace(id, std::make_unique<Earth>(*this));
                break;
            }
            case (PlanetaryBody::MOON): {
                _bodies.emplace(id, std::make_unique<Moon>(*this));
                break;
            }
            case (PlanetaryBody::MARS): {
                _bodies.emplace(id, std::make_unique<Mars>(*this));
                break;
            }
            case (PlanetaryBody::PHOBOS): {
                _bodies.emplace(id, std::make_unique<Phobos>(*this));
                break;
            }
            case (PlanetaryBody::DEIMOS): {
                _bodies.emplace(id, std::make_unique<Deimos>(*this));
                break;
            }
            case (PlanetaryBody::JUPITER): {
                _bodies.emplace(id, std::make_unique<Jupiter>(*this));
                break;
            }
            case (PlanetaryBody::GANYMEDE): {
                _bodies.emplace(id, std::make_unique<Ganymede>(*this));
                break;
            }
            case (PlanetaryBody::CALLISTO): {
                _bodies.emplace(id, std::make_unique<Callisto>(*this));
                break;
            }
            case (PlanetaryBody::IO): {
                _bodies.emplace(id, std::make_unique<Io>(*this));
                break;
            }
            case (PlanetaryBody::EUROPA): {
                _bodies.emplace(id, std::make_unique<Europa>(*this));
                break;
            }
            case (PlanetaryBody::SATURN): {
                _bodies.emplace(id, std::make_unique<Saturn>(*this));
                break;
            }
            case (PlanetaryBody::TITAN): {
                _bodies.emplace(id, std::make_unique<Titan>(*this));
                break;
            }
            case (PlanetaryBody::RHEA): {
                _bodies.emplace(id, std::make_unique<Rhea>(*this));
                break;
            }
            case (PlanetaryBody::IAPETUS): {
                _bodies.emplace(id, std::make_unique<Iapetus>(*this));
                break;
            }
            case (PlanetaryBody::URANUS): {
                _bodies.emplace(id, std::make_unique<Uranus>(*this));
                break;
            }
            case (PlanetaryBody::TITANIA): {
                _bodies.emplace(id, std::make_unique<Titania>(*this));
                break;
            }
            case (PlanetaryBody::OBERON): {
                _bodies.emplace(id, std::make_unique<Oberon>(*this));
                break;
            }
            case (PlanetaryBody::NEPTUNE): {
                _bodies.emplace(id, std::make_unique<Neptune>(*this));
                break;
            }
            case (PlanetaryBody::TRITON): {
                _bodies.emplace(id, std::make_unique<Triton>(*this));
                break;
            }
            default: throw std::runtime_error("Error: Celestial body not implemented in factory.");
        }

        _activeBodies.insert(id);
        find_system_root();
    }

    return get(id);
}

const CelestialBodyUniquePtr& AstrodynamicsSystem::get(const PlanetaryBody& id) const
{
    if (_bodies.count(id) > 0) { return _bodies.at(id); }
    throw std::out_of_range("Input gravitational body not found.");
}

void AstrodynamicsSystem::find_system_root()
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

GravParam AstrodynamicsSystem::get_mu() const
{
    switch (_centerType) {
        case SystemCenter::CENTRAL_BODY: return get_central_body()->get_mu();
        case SystemCenter::BARYCENTER: throw std::runtime_error("Barycenteric systems have not been implemented yet.");
        default: throw std::runtime_error("AstrodynamicsSystem::get_mu: Unknown system center type.");
    }
}


// void CelestialBodyFactory::propagate_bodies(const Date& epoch, const Time& endTime)
// {
//     // Propagate everything except the Sun
//     for (auto& [name, body] : _bodies) {
//         if (name != "Sun") {
//             // Get parent mu
//             const std::string parent = body->get_parent();
//             const auto parentMu      = get_or_create(parent)->get_mu();

//             // Propagate
//             body->propagate(epoch, endTime, parentMu);
//         }
//     }
// }

// void AstrodynamicsSystem::propagate_bodies(const Time& propTime)
// {
// TODO: Since we're now just accessing the location of bodies by date directly,
// we don't need to do this in advance. But this logic is still useful for getting relative locations.
// Figure out how to make it accessible if needed. Since this is looking like an earth-centric tool,
// this might be overkill.

// // Ask factory to propagate
// _bodyFactory.propagate_bodies(epoch, propTime);

// // Assign properties from central body
// const CelestialBodyUniquePtr& center = _bodyFactory.get(_centralBody);
// const StateHistory centerToParent    = center->get_state_history();

// // Get root body
// std::string root          = _bodyFactory.get_system_root();
// StateHistory centerToRoot = centerToParent;
// if (_centralBody != root) {
//     auto parent = center->get_parent();
//     while (parent != root) {
//         const CelestialBodyUniquePtr& parentBody = _bodyFactory.get(parent);
//         auto parentToGrandParent                 = parentBody->get_state_history();
//         for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {

//             centerToRoot[ii].get_elements() = centerToRoot[ii].get_elements() + parentToGrandParent[ii].get_elements();
//         }
//         parent = parentBody->get_parent();
//     }
// }
// else {
//     for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {
//         centerToRoot[ii].get_elements() = OrbitalElements(Keplerian());
//     }
// }

// // Get root to Sun
// if (_centralBody != "Sun") {
//     StateHistory centerToSun = centerToParent;
//     auto parent              = center->get_parent();
//     while (parent != "None") {
//         const CelestialBodyUniquePtr& parentBody = _bodyFactory.get_or_create(parent);
//         if (parent == "Sun") {
//             for (std::size_t ii = 0; ii < centerToSun.size(); ii++) {
//                 centerToSun[ii].get_elements() = centerToSun[ii].get_elements();
//             }
//         }
//         else {
//             auto parentToGrandParent = parentBody->get_state_history();
//             for (std::size_t ii = 0; ii < centerToSun.size(); ii++) {
//                 centerToSun[ii].get_elements() = centerToSun[ii].get_elements() + parentToGrandParent[ii].get_elements();
//             }
//         }
//         parent = parentBody->get_parent();
//     }
// }
// else {
//     for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {
//         centerToSun[ii].get_elements() = OrbitalElements(Keplerian());
//     }
// }

// // Get states for ith bodies to center
// std::vector<StateHistory> statesToCenter;
// for (auto&& [name, ithBody] : _bodyFactory) {
//     if (name == _centralBody) { continue; }

//     // Get ith body states
//     statesToCenter.push_back(ithBody->get_state_history());

//     // If parent is not root, back track to root
//     auto parent  = ithBody->get_parent();
//     auto& states = statesToCenter.back();
//     while (parent != root && parent != "None") {
//         const CelestialBodyUniquePtr& parentBody = _bodyFactory.get(parent);
//         auto parentToGrandParent                 = parentBody->get_state_history();
//         for (std::size_t ii = 0; ii < states.size(); ii++) {
//             states[ii].get_elements() = states[ii].get_elements() + parentToGrandParent[ii].get_elements();
//         }
//         parent = parentBody->get_parent();
//     }

//     // Convert to state relative to central body
//     for (std::size_t ii = 0; ii < states.size(); ii++) {
//         states[ii].get_elements() = states[ii].get_elements() - centerToRoot[ii].get_elements();
//     }
// }
// }

} // namespace astro
} // namespace astrea