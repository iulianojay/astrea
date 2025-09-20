#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Ganymede : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Jupiter/Ganymede.json"; }

  public:
    Ganymede() :
        CelestialBody(file())
    {
    }
    Ganymede(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Ganymede() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::JUPITER; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::GANYMEDE; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea