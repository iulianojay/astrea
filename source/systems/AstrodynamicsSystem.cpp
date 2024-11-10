#include "AstrodynamicsSystem.hpp"


void AstrodynamicsSystem::create_all_bodies() {
    for (const auto body: allBodies) {
        bodyFactory.create(body);
    }
};


void AstrodynamicsSystem::propagate_bodies(double propTime) {

    // Ask factory to propagate
    bodyFactory.propagate_bodies(epoch, propTime);

    // Assign properties from central body
    GravitationalBody center = bodyFactory.get(centralBody);
    const std::vector<State> centerToParent = center.get_states();

    // Get root body
    SolarObject root = bodyFactory.get_root();
    std::vector<State> centerToRoot = centerToParent;
    if (centralBody != root) {
        auto parent = center.parent();
        while (parent != root) {
            GravitationalBody parentBody = bodyFactory.get(parent);
            auto parentToGrandParent = parentBody.get_states();
            for (size_t ii = 0; ii < centerToRoot.size(); ii++) {
                centerToRoot[ii].elements = centerToRoot[ii].elements + parentToGrandParent[ii].elements;
            }
            parent = parentBody.parent();
        }
    }
    else {
        const element_array noDiff = {0.0};
        for (size_t ii = 0; ii < centerToRoot.size(); ii++) {
            centerToRoot[ii].elements = OrbitalElements(noDiff, ElementSet::CARTESIAN);
        }
    }

    // Get root to Sun
    if (centralBody != SUN) {
        std::vector<State> centerToSun = centerToParent;
        auto parent = center.parent();
        // auto& states = centerToSun.back();
        while (parent != GC) {
            GravitationalBody parentBody = bodyFactory.get(parent);
            auto parentToGrandParent = parentBody.get_states();
            for (size_t ii = 0; ii < centerToSun.size(); ii++) {
                centerToSun[ii].elements = centerToSun[ii].elements + parentToGrandParent[ii].elements;
            }
            parent = parentBody.parent();
        }
    }
    else {
        const element_array noDiff{0.0};
        for (size_t ii = 0; ii < centerToSun.size(); ii++) {
            centerToSun[ii].elements = OrbitalElements(noDiff, ElementSet::CARTESIAN);
        }
    }

    // Get states for ith bodies to center
    for (const auto body: allBodies) {
        if (body == centralBody) {
            continue;
        }

        // Get ith body states
        GravitationalBody ithBody = bodyFactory.get(body);
        statesToCenter.push_back(ithBody.get_states());

        // If parent is not root, back track to root
        auto parent = ithBody.parent();
        auto& states = statesToCenter.back();
        while (parent != root) {
            GravitationalBody parentBody = bodyFactory.get(parent);
            auto parentToGrandParent = parentBody.get_states();
            for (size_t ii = 0; ii < states.size(); ii++) {
                states[ii].elements = states[ii].elements + parentToGrandParent[ii].elements;
            }
            parent = parentBody.parent();
        }

        // Convert to state relative to central body
        for (size_t ii = 0; ii < states.size(); ii++) {
            states[ii].elements = states[ii].elements - centerToRoot[ii].elements;
        }
    }

}