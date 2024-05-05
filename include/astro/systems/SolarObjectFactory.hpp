#pragma once

#include <string>
#include <unordered_map>

#include "solar_system.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectBuilder.hpp"
#include "Date.hpp"

namespace solar_system {

class SolarObjectFactory {
public:

    SolarObjectFactory() : builder() {};
    ~SolarObjectFactory() {};

    const GravitationalBody& create(const SolarObject name);
    const GravitationalBody& create(const std::string name);

    const GravitationalBody& get(const SolarObject name) const;
    const GravitationalBody& get(const std::string name) const;
    
    const GravitationalBody& get(const SolarObject name, const bool buildIfMissing=false);
    const GravitationalBody& get(const std::string name, const bool buildIfMissing=false);

    const size_t number_of_bodies() const { return bodies.size(); }
    void propagate_bodies(Date epoch, double endTime);

private:

    SolarObjectBuilder builder;
    std::unordered_map<SolarObject, GravitationalBody> bodies;

};

}