#pragma once

#include <string>
#include <unordered_map>

#include "solar_system.hpp"
#include "GravitationalBody.hpp"

namespace SolarSystem {

class SolarObjectFactory {
public:

    SolarObjectFactory() {};
    ~SolarObjectFactory() {};

    GravitationalBody& create(SolarObject name);
    GravitationalBody& create(std::string name);
    
    GravitationalBody& get(SolarObject name, bool buildIfMissing=false);
    GravitationalBody& get(std::string name, bool buildIfMissing=false);

private:

    std::unordered_map<SolarObject, GravitationalBody> bodies;

};

}