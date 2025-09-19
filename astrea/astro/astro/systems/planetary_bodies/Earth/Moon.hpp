#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Moon : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Earth/Moon.json"; }

  public:
    Moon() :
        CelestialBody(file())
    {
    }
    Moon(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Moon() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::EARTH; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::MOON; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea