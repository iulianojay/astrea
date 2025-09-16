#pragma once

#include <unordered_set>

#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {

class Barycenter : public CelestialBody {
  public:
    Barycenter(CelestialBody referenceBody, std::unordered_set<CelestialBody> bodies) :
        referenceBody(referenceBody),
        bodies(bodies) {};
    ~Barycenter() {};

  private:
    CelestialBody referenceBody;
    std::unordered_set<CelestialBody> bodies;
};

} // namespace astro
} // namespace astrea