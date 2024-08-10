#pragma once

#include <unordered_set>

#include "typedefs.hpp"
#include "solar_system.hpp"
#include "GravitationalBody.hpp"

namespace solar_system {

class Barycenter : public GravitationalBody {
public:

    Barycenter(SolarObject referenceBody, std::unordered_set<SolarObject> bodies) : referenceBody(referenceBody), bodies(bodies) {};
    ~Barycenter() {};

private:
    
    basis_array center;
    SolarObject referenceBody;
    std::unordered_set<SolarObject> bodies;
};

}