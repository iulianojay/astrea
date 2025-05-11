#pragma once

#include <unordered_set>

#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

namespace astro {

class Barycenter : public CelestialBody {
  public:
    Barycenter(CelestialBody referenceBody, std::unordered_set<CelestialBody> bodies) :
        referenceBody(referenceBody),
        bodies(bodies){};
    ~Barycenter(){};

  private:
    RadiusVector center;
    CelestialBody referenceBody;
    std::unordered_set<CelestialBody> bodies;
};

} // namespace astro