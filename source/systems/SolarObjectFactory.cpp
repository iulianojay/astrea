
#include "SolarObjectFactory.hpp"

namespace solar_system {

GravitationalBody& SolarObjectFactory::create(std::string name) {
    return create(_nameMap.at(name));
}

GravitationalBody& SolarObjectFactory::create(SolarObject name) {
    if (!bodies.count(name)) {
        GravitationalBody body(name);
        bodies.insert({name, body});
    }
    return get(name);
}


GravitationalBody& SolarObjectFactory::get(std::string name, bool buildIfMissing) {
    return get(_nameMap.at(name), buildIfMissing);
}

GravitationalBody& SolarObjectFactory::get(SolarObject name, bool buildIfMissing) {
    if (bodies.count(name)) {
        return bodies.at(name);
    }
    else if (buildIfMissing) {
        create(name);
    }
    throw std::out_of_range("Input gravitational body," + _mapName.at(name) + ", not found.");
}

}