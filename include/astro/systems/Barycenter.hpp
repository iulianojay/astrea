#pragma once

#ifndef SWIG
    #include <unordered_set>
#endif

#include "typedefs.hpp"
#include "solar_system.hpp"
#include "GravitationalBody.hpp"


class Barycenter : public GravitationalBody {
public:

    Barycenter(CelestialBody referenceBody, std::unordered_set<CelestialBody> bodies) : referenceBody(referenceBody), bodies(bodies) {};
    ~Barycenter() {};

private:

    basis_array center;
    CelestialBody referenceBody;
    std::unordered_set<CelestialBody> bodies;
};
