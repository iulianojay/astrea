#pragma once

#include <unordered_set>
#include <vector>

#include "typedefs.hpp"
#include "solar_system.hpp"
#include "Barycenter.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectFactory.hpp"

using namespace solar_system;

class AstrodynamicsSystem {
public: 

    AstrodynamicsSystem(SolarObject centralBody = EARTH, std::unordered_set<SolarObject> allBodies = {EARTH}) : centralBody(centralBody), allBodies(allBodies) {
        create_all_bodies();
    };
    ~AstrodynamicsSystem(){};

    const SolarObject& center() const { return centralBody; }
    const GravitationalBody& get_center() const { return bodyFactory.get(centralBody); }

    const std::unordered_set<SolarObject>& all_bodies() const { return allBodies; }

    void propagate_bodies(double endTime);
    basis_array get_radius_to_center(SolarObject target, double julianDate);

private:

    std::string epoch; 
    const SolarObject centralBody;
    const std::unordered_set<SolarObject> allBodies;
    SolarObjectFactory bodyFactory;

    void create_all_bodies();
};