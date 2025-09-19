#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

AstrodynamicsSystem::AstrodynamicsSystem(const PlanetaryBody& centralBody, const std::unordered_set<PlanetaryBody>& secondaryBodies) :
    _centerType(SystemCenter::CENTRAL_BODY),
    _centralBody(centralBody),
    _bodies(secondaryBodies)
{
    _bodies.insert(centralBody);
    create_all_bodies();
};

void AstrodynamicsSystem::create_all_bodies()
{
    for (const auto& body : _bodies) {
        _bodyFactory.create(body, *this);
    }
};

AstrodynamicsSystem AstrodynamicsSystem::DEFAULT() { return AstrodynamicsSystem(); }

const SystemCenter& AstrodynamicsSystem::get_center_type() const { return _centerType; }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_central_body() const
{
    switch (_centerType) {
        case SystemCenter::CENTRAL_BODY: return _bodyFactory.get(_centralBody);
        case SystemCenter::BARYCENTER:
        default: throw std::runtime_error("Barycenteric systems have no central body.");
    }
}

const CelestialBodyUniquePtr& AstrodynamicsSystem::get(const PlanetaryBody& id) const { return _bodyFactory.get(id); }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_or_create(const PlanetaryBody& id)
{
    return _bodyFactory.get_or_create(id, *this);
}

const CelestialBodyUniquePtr& AstrodynamicsSystem::create(const PlanetaryBody& id, const AstrodynamicsSystem& system)
{
    _bodies.insert(id);
    return _bodyFactory.create(id, system);
}

void AstrodynamicsSystem::find_root()
{
    // TODO: Move this to the system

    // Count total planets
    std::size_t planetCount = 0;
    for (const auto& id : _bodies) {
        const auto& body = get(id);
        if (body->get_type() == CelestialBodyType::PLANET) {
            planetCount++;
            _root = id;
        }
    }

    // Check if other bodies are children of only planet -
    // assumes the common root cannot be a satellite
    if (planetCount == 1) {
        for (const auto& id : _bodies) {
            PlanetaryBody parent = id;
            while (parent != PlanetaryBody::SUN && parent != _root) {
                parent = get_or_create(parent)->get_parent();
            }

            // If any object not in same planetary system, the common root
            // must be the Sun
            if (parent == PlanetaryBody::SUN) {
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
// std::string root          = _bodyFactory.get_root();
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