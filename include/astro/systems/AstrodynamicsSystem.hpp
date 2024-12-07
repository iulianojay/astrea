#pragma once

#ifndef SWIG
    #include <unordered_set>
    #include <vector>
#endif

#include "astro/types/typedefs.hpp"
#include "astro/systems/solar_system.hpp"
#include "astro/systems/Barycenter.hpp"
#include "astro/systems/CelestialBody.hpp"
#include "astro/systems/CelestialBodyFactory.hpp"
#include "astro/time/Date.hpp"
#include "astro/platforms/vehicles/Spacecraft.hpp"


class AstrodynamicsSystem {
public:

    AstrodynamicsSystem(CelestialBody centralBody = EARTH, std::unordered_set<CelestialBody> allBodies = {EARTH}, Date epoch = J2000) :
        centralBody(centralBody), allBodies(allBodies), epoch(epoch) {
        create_all_bodies();
    };
    ~AstrodynamicsSystem() {}

    const CelestialBody& center() const { return centralBody; }
    const CelestialBody& get_center() const { return bodyFactory.get(centralBody); }

    const std::unordered_set<CelestialBody>& all_bodies() const { return allBodies; }

    void propagate_bodies(double propTime);
    // basis_array get_radius_to_center(CelestialBody target, double julianDate); //TODO: Implement

private:

    const CelestialBody centralBody;
    const std::unordered_set<CelestialBody> allBodies;

    Date epoch;
    CelestialBodyFactory bodyFactory;

    std::vector<std::vector<State>> statesToCenter;
    std::vector<State> centerToSun;

    void create_all_bodies();
};