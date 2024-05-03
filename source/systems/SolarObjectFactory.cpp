
#include "SolarObjectFactory.hpp"

namespace solar_system {

const GravitationalBody& SolarObjectFactory::create(const std::string name) {
    return create(builder._nameMap.at(name));
}

const GravitationalBody& SolarObjectFactory::create(const SolarObject name) {
    if (!bodies.count(name)) {
        GravitationalBody body = builder.build(name);
        bodies.insert({name, body});
    }
    return get(name);
}


const GravitationalBody& SolarObjectFactory::get(const std::string name) const {
    return get(builder._nameMap.at(name));
}

const GravitationalBody& SolarObjectFactory::get(const SolarObject name) const {
    if (bodies.count(name)) {
        return bodies.at(name);
    }
    throw std::out_of_range("Input gravitational body," + builder._mapName.at(name) + ", not found.");
}

const GravitationalBody& SolarObjectFactory::get(const std::string name, const bool buildIfMissing) {
    return get(builder._nameMap.at(name), buildIfMissing);
}

const GravitationalBody& SolarObjectFactory::get(const SolarObject name, const bool buildIfMissing) {
    if (bodies.count(name)) {
        return bodies.at(name);
    }
    else if (buildIfMissing) {
        create(name);
    }
    throw std::out_of_range("Input gravitational body," + builder._mapName.at(name) + ", not found.");
}


void SolarObjectFactory::propagate_bodies(double endTime) {

    // Go until end julian date
    for (auto [name, body]: bodies) {
        // Create ith body
        body.propagate(endTime);
    }
}

}