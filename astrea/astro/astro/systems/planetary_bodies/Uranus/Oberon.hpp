#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Oberon : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Uranus/Oberon.json"; }

  public:
    Oberon() :
        CelestialBody(file())
    {
    }
    Oberon(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Oberon() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::URANUS; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::OBERON; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea