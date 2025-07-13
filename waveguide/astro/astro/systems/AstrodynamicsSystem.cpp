#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/state/StateHistory.hpp>

namespace astro {

void AstrodynamicsSystem::create_all_bodies()
{
    for (const auto& body : allBodies) {
        bodyFactory.create(body, *this);
    }
};


// void AstrodynamicsSystem::propagate_bodies(const Time& propTime)
// {
// TODO: Since we're now just accessing the location of bodies by date directly,
// we don't need to do this in advance. But this logic is still useful for getting relative locations.
// Figure out how to make it accessible if needed. Since this is looking like an earth-centric tool,
// this might be overkill.

// // Ask factory to propagate
// bodyFactory.propagate_bodies(epoch, propTime);

// // Assign properties from central body
// const CelestialBodyUniquePtr& center = bodyFactory.get(centralBody);
// const StateHistory centerToParent    = center->get_state_history();

// // Get root body
// std::string root          = bodyFactory.get_root();
// StateHistory centerToRoot = centerToParent;
// if (centralBody != root) {
//     auto parent = center->get_parent();
//     while (parent != root) {
//         const CelestialBodyUniquePtr& parentBody = bodyFactory.get(parent);
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
// if (centralBody != "Sun") {
//     StateHistory centerToSun = centerToParent;
//     auto parent              = center->get_parent();
//     while (parent != "None") {
//         const CelestialBodyUniquePtr& parentBody = bodyFactory.get_or_create(parent);
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
// for (auto&& [name, ithBody] : bodyFactory) {
//     if (name == centralBody) { continue; }

//     // Get ith body states
//     statesToCenter.push_back(ithBody->get_state_history());

//     // If parent is not root, back track to root
//     auto parent  = ithBody->get_parent();
//     auto& states = statesToCenter.back();
//     while (parent != root && parent != "None") {
//         const CelestialBodyUniquePtr& parentBody = bodyFactory.get(parent);
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