#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astro {

void AstrodynamicsSystem::create_all_bodies()
{
    for (const auto& body : allBodies) {
        bodyFactory.create(body);
    }
};


void AstrodynamicsSystem::propagate_bodies(const Time& propTime)
{

    // Ask factory to propagate
    bodyFactory.propagate_bodies(epoch, propTime);

    // Assign properties from central body
    const CelestialBodyUniquePtr& center    = bodyFactory.get(centralBody);
    const std::vector<State> centerToParent = center->get_states();

    // Get root body
    std::string root                = bodyFactory.get_root();
    std::vector<State> centerToRoot = centerToParent;
    if (centralBody != root) {
        auto parent = center->get_parent();
        while (parent != root) {
            const CelestialBodyUniquePtr& parentBody = bodyFactory.get(parent);
            auto parentToGrandParent                 = parentBody->get_states();
            for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {

                centerToRoot[ii].elements = centerToRoot[ii].elements + parentToGrandParent[ii].elements;
            }
            parent = parentBody->get_parent();
        }
    }
    else {
        for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {
            centerToRoot[ii].elements = OrbitalElements(Keplerian());
        }
    }

    // Get root to Sun
    if (centralBody != "Sun") {
        std::vector<State> centerToSun = centerToParent;
        auto parent                    = center->get_parent();
        while (parent != "None") {
            const CelestialBodyUniquePtr& parentBody = bodyFactory.get_or_create(parent);
            if (parent == "Sun") {
                for (std::size_t ii = 0; ii < centerToSun.size(); ii++) {
                    centerToSun[ii].elements = centerToSun[ii].elements;
                }
            }
            else {
                auto parentToGrandParent = parentBody->get_states();
                for (std::size_t ii = 0; ii < centerToSun.size(); ii++) {
                    centerToSun[ii].elements = centerToSun[ii].elements + parentToGrandParent[ii].elements;
                }
            }
            parent = parentBody->get_parent();
        }
    }
    else {
        for (std::size_t ii = 0; ii < centerToRoot.size(); ii++) {
            centerToSun[ii].elements = OrbitalElements(Keplerian());
        }
    }

    // Get states for ith bodies to center
    for (auto&& [name, ithBody] : bodyFactory) {
        if (name == centralBody) { continue; }

        // Get ith body states
        statesToCenter.push_back(ithBody->get_states());

        // If parent is not root, back track to root
        auto parent  = ithBody->get_parent();
        auto& states = statesToCenter.back();
        while (parent != root && parent != "None") {
            const CelestialBodyUniquePtr& parentBody = bodyFactory.get(parent);
            auto parentToGrandParent                 = parentBody->get_states();
            for (std::size_t ii = 0; ii < states.size(); ii++) {
                states[ii].elements = states[ii].elements + parentToGrandParent[ii].elements;
            }
            parent = parentBody->get_parent();
        }

        // Convert to state relative to central body
        for (std::size_t ii = 0; ii < states.size(); ii++) {
            states[ii].elements = states[ii].elements - centerToRoot[ii].elements;
        }
    }
}

} // namespace astro