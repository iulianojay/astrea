#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

AstrodynamicsSystem::AstrodynamicsSystem(const std::string& centralBody, const std::unordered_set<std::string>& secondaryBodies) :
    _centralBody(centralBody),
    _allBodies(secondaryBodies)
{
    _allBodies.insert(_centralBody);
    create_all_bodies();
};

void AstrodynamicsSystem::create_all_bodies()
{
    for (const auto& body : _allBodies) {
        _bodyFactory.create(body, *this);
    }
};

AstrodynamicsSystem AstrodynamicsSystem::DEFAULT() { return AstrodynamicsSystem(); }

const std::string& AstrodynamicsSystem::center() const { return _centralBody; }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_center() const { return _bodyFactory.get(_centralBody); }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get(const std::string& name) const { return _bodyFactory.get(name); }

const CelestialBodyUniquePtr& AstrodynamicsSystem::get_or_create(const std::string& name)
{
    return _bodyFactory.get_or_create(name, *this);
}

const std::unordered_set<std::string>& AstrodynamicsSystem::all_bodies() const { return _allBodies; }


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