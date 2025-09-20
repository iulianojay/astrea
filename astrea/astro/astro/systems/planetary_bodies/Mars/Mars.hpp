#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Mars : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Mars/Mars.json"; }

  public:
    Mars() :
        CelestialBody(file())
    {
    }
    Mars(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Mars() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SUN; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::MARS; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::PLANET; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea