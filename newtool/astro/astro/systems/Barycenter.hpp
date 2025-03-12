#pragma once

#ifndef SWIG
    #include <unordered_set>
#endif

#include <astro/types/typedefs.hpp>
#include <astro/systems/CelestialBody.hpp>


class Barycenter : public CelestialBody {
public:

    Barycenter(CelestialBody referenceBody, std::unordered_set<CelestialBody> bodies) : referenceBody(referenceBody), bodies(bodies) {};
    ~Barycenter() {};

private:

    basis_array center;
    CelestialBody referenceBody;
    std::unordered_set<CelestialBody> bodies;
};
