#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include "solar_system.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectBuilder.hpp"
#include "Date.hpp"


class SolarObjectFactory {
public:

    SolarObjectFactory() : builder() {};
    ~SolarObjectFactory() {};

    const GravitationalBody& create(const SolarObject name);
    const GravitationalBody& create(const std::string name);

    const GravitationalBody& get(const SolarObject name) const;
    const GravitationalBody& get(const std::string name) const;
    
    const GravitationalBody& get_or_create(const SolarObject name);
    const GravitationalBody& get_or_create(const std::string name);

    const size_t number_of_bodies() const { return bodies.size(); }
    void propagate_bodies(Date epoch, double endTime);

    const SolarObject& get_root() const { return root; }

private:

    SolarObjectBuilder builder;
    std::unordered_map<SolarObject, GravitationalBody> bodies;
    SolarObject root;

    void find_root();
};
