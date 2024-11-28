
#include "SolarObjectFactory.hpp"

#include "State.hpp"


const GravitationalBody& SolarObjectFactory::create(const std::string& name) {
    return create(builder._nameMap.at(name));
}

const GravitationalBody& SolarObjectFactory::create(const SolarObject& name) {
    if (!bodies.count(name)) {
        GravitationalBody body = builder.build(name);
        bodies.insert({name, body});
    }
    return get(name);
}


const GravitationalBody& SolarObjectFactory::get(const std::string& name) const {
    return get(builder._nameMap.at(name));
}

const GravitationalBody& SolarObjectFactory::get(const SolarObject& name) const {
    if (bodies.count(name)) {
        return bodies.at(name);
    }
    throw std::out_of_range("Input gravitational body," + builder._mapName.at(name) + ", not found.");
}

const GravitationalBody& SolarObjectFactory::get_or_create(const std::string& name) {
    return get_or_create(builder._nameMap.at(name));
}

const GravitationalBody& SolarObjectFactory::get_or_create(const SolarObject& name) {
    if (!bodies.count(name)) {
        create(name);
    }
    return bodies.at(name);
}


void SolarObjectFactory::propagate_bodies(const Date& epoch, const Time& endTime) {

    // Find root object for reference
    find_root();

    // Go until end julian date
    for (auto [name, body]: bodies) {
        // Create ith body
        body.propagate(epoch, endTime);
    }
}


void SolarObjectFactory::find_root() {

    // Count total planets
    int planetCount = 0;
    for (const auto& [object, body]: bodies) {
        if (body.type() == PLANET) {
            planetCount++;
            root = object;
        }
    }

    // Check if other bodies are children of only planet -
    // assumes the common root cannot be a satellite
    if (planetCount == 1) {
        for (const auto& [object, _]: bodies) {
            SolarObject parent = object;
            while (parent != SUN && parent != root) {
                parent = builder._parentMap.at(parent);
            }

            // If any object not in same planetary system, the common root
            // must be the Sun
            if (parent == SUN) {
                root = SUN;
                break;
            }
        }
    }
    else {
        // The only common root for multiple planets is the Sun
        root = SUN;
    }
}
