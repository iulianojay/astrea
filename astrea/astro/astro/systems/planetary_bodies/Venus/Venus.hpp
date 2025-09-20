#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Venus : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Venus/Venus.json"; }

  public:
    Venus() :
        CelestialBody(file())
    {
    }
    Venus(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Venus() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SUN; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::VENUS; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::PLANET; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea