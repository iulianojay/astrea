#pragma once

#ifndef SWIG
#include <unordered_set>
#endif

#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>


class Barycenter : public CelestialBody {
  public:
    Barycenter(CelestialBody referenceBody, std::unordered_set<CelestialBody> bodies) :
        referenceBody(referenceBody),
        bodies(bodies){};
    ~Barycenter(){};

  private:
    BasisArray center;
    CelestialBody referenceBody;
    std::unordered_set<CelestialBody> bodies;
};
