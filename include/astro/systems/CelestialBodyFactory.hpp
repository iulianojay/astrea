#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include "astro/systems/solar_system.hpp"
#include "astro/systems/CelestialBody.hpp"
#include "astro/systems/CelestialBodyBuilder.hpp"
#include "astro/time/Date.hpp"


class CelestialBodyFactory {
public:

    CelestialBodyFactory() : builder() {};
    ~CelestialBodyFactory() {};

    const CelestialBody& create(const CelestialBody& name);
    const CelestialBody& create(const std::string& name);

    const CelestialBody& get(const CelestialBody& name) const;
    const CelestialBody& get(const std::string& name) const;

    const CelestialBody& get_or_create(const CelestialBody& name);
    const CelestialBody& get_or_create(const std::string& name);

    const size_t number_of_bodies() const { return bodies.size(); }
    void propagate_bodies(const Date& epoch, const Time& endTime);

    const CelestialBody& get_root() const { return root; }

private:

    CelestialBodyBuilder builder;
    std::unordered_map<CelestialBody, CelestialBody> bodies;
    CelestialBody root;

    void find_root();
};
