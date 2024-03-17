#pragma once

#include <string>
#include <unordered_map>

#include "solar_system.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectBuilder.hpp"

namespace solar_system {

class SolarObjectFactory {
public:

    SolarObjectFactory() : builder() {};
    ~SolarObjectFactory() {};

    GravitationalBody& create(SolarObject name);
    GravitationalBody& create(std::string name);
    
    GravitationalBody& get(SolarObject name, bool buildIfMissing=false);
    GravitationalBody& get(std::string name, bool buildIfMissing=false);

private:

    SolarObjectBuilder builder;
    std::unordered_map<SolarObject, GravitationalBody> bodies;

};

}