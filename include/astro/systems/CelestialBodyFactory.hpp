#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include "astro/systems/solar_system.hpp"
#include "astro/systems/GravitationalBody.hpp"
#include "astro/systems/CelestialBodyBuilder.hpp"
#include "astro/time/Date.hpp"


class CelestialBodyFactory {
public:

    CelestialBodyFactory() : builder() {};
    ~CelestialBodyFactory() {};

    const GravitationalBody& create(const CelestialBody& name);
    const GravitationalBody& create(const std::string& name);

    const GravitationalBody& get(const CelestialBody& name) const;
    const GravitationalBody& get(const std::string& name) const;

    const GravitationalBody& get_or_create(const CelestialBody& name);
    const GravitationalBody& get_or_create(const std::string& name);

    const size_t number_of_bodies() const { return bodies.size(); }
    void propagate_bodies(const Date& epoch, const Time& endTime);

    const CelestialBody& get_root() const { return root; }

private:

    CelestialBodyBuilder builder;
    std::unordered_map<CelestialBody, GravitationalBody> bodies;
    CelestialBody root;

    void find_root();
};
