#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Phobos : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Mars/Phobos.json"; }

  public:
    Phobos() :
        CelestialBody(file())
    {
    }
    Phobos(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Phobos() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::MARS; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::PHOBOS; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea