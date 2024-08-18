#pragma once

#ifndef SWIG
    #include <unordered_set>
    #include <vector>
#endif

#include "typedefs.hpp"
#include "solar_system.hpp"
#include "Barycenter.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectFactory.hpp"
#include "Date.hpp"


class AstrodynamicsSystem {
public: 

    AstrodynamicsSystem(SolarObject centralBody = EARTH, std::unordered_set<SolarObject> allBodies = {EARTH}, Date epoch = J2000) : 
        centralBody(centralBody), allBodies(allBodies), epoch(epoch) {
        create_all_bodies();
    };
    ~AstrodynamicsSystem() {}

    const SolarObject& center() const { return centralBody; }
    const GravitationalBody& get_center() const { return bodyFactory.get(centralBody); }

    const std::unordered_set<SolarObject>& all_bodies() const { return allBodies; }

    void propagate_bodies(double propTime);
    // basis_array get_radius_to_center(SolarObject target, double julianDate); //TODO: Implement

private:

    Date epoch; 
    const SolarObject centralBody;
    const std::unordered_set<SolarObject> allBodies;
    SolarObjectFactory bodyFactory;
    
    std::vector<std::vector<State>> statesToCenter;
    std::vector<State> centerToSun;

    void create_all_bodies();
};