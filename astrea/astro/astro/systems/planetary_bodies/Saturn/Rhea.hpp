#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Rhea : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Saturn/Rhea.json"; }

  public:
    Rhea() :
        CelestialBody(file())
    {
    }
    Rhea(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Rhea() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SATURN; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::RHEA; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea