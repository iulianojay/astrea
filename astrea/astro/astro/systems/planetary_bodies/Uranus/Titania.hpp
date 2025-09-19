#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Titania : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Uranus/Titania.json"; }

  public:
    Titania() :
        CelestialBody(file())
    {
    }
    Titania(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Titania() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::URANUS; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::TITANIA; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea