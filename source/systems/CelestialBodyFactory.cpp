
#include "CelestialBodyFactory.hpp"

#include "State.hpp"


const CelestialBodyUniquePtr& CelestialBodyFactory::create(const std::string& name) {
    if (bodies.count(name) == 0) {
        bodies[name] = std::make_unique<CelestialBody>(buildFiles.at(name));
    }
    return get(name);
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get(const std::string& name) const {
    if (bodies.count(name) > 0) {
        return bodies.at(name);
    }
    throw std::out_of_range("Input gravitational body," + name + ", not found.");
}

const CelestialBodyUniquePtr& CelestialBodyFactory::get_or_create(const std::string& name) {
    if (bodies.count(name) == 0) {
        create(name);
    }
    return bodies.at(name);
}


void CelestialBodyFactory::propagate_bodies(const Date& epoch, const Time& endTime) {

    // Find root object for reference
    find_root();

    // Propagate everything except the Sun
    for (auto& [name, body]: bodies) {
        if (name != "Sun") {
            // Get parent mu
            const std::string parent = body->get_parent();
            const double parentMu = get(parent)->get_mu();

            // Propagate
            body->propagate(epoch, endTime, parentMu);
        }
    }
}


void CelestialBodyFactory::find_root() {

    // Count total planets
    int planetCount = 0;
    for (const auto& [object, body]: bodies) {
        if (body->get_type() == "Planet") {
            planetCount++;
            root = object;
        }
    }

    // Check if other bodies are children of only planet -
    // assumes the common root cannot be a satellite
    if (planetCount == 1) {
        for (const auto& [object, _]: bodies) {
            std::string parent = object;
            while (parent != "Sun" && parent != root) {
                parent = get(parent)->get_name();
            }

            // If any object not in same planetary system, the common root
            // must be the Sun
            if (parent == "Sun") {
                root = "Sun";
                break;
            }
        }
    }
    else {
        // The only common root for multiple planets is the Sun
        root = "Sun";
    }
}
