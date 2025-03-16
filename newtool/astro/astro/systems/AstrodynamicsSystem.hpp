#pragma once

#ifndef SWIG
#include <unordered_set>
#include <vector>
#endif

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/systems/Barycenter.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyFactory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>


class AstrodynamicsSystem {
  public:
    AstrodynamicsSystem(std::string centralBody = "Earth", std::unordered_set<std::string> allBodies = { "Earth", "Moon" }, Date epoch = J2000)
        : centralBody(centralBody), allBodies(allBodies), epoch(epoch)
    {
        create_all_bodies();
    };
    ~AstrodynamicsSystem() {}

    const std::string& center() const { return centralBody; }
    const CelestialBodyUniquePtr& get_center() const { return bodyFactory.get(centralBody); }
    const CelestialBodyUniquePtr& get(const std::string& name) const { return bodyFactory.get(name); }

    const std::unordered_set<std::string>& all_bodies() const { return allBodies; }

    void propagate_bodies(double propTime);
    // basis_array get_radius_to_center(CelestialBody target, double julianDate); //TODO: Implement


    using iterator       = std::unordered_map<std::string, CelestialBodyUniquePtr>::iterator;
    using const_iterator = std::unordered_map<std::string, CelestialBodyUniquePtr>::const_iterator;
    auto begin() const { return bodyFactory.begin(); }
    auto end() const { return bodyFactory.end(); }

  private:
    const std::string centralBody;
    const std::unordered_set<std::string> allBodies;

    Date epoch;
    CelestialBodyFactory bodyFactory;

    std::vector<std::vector<State>> statesToCenter;
    std::vector<State> centerToSun;

    void create_all_bodies();
};