#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Uranus : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Uranus/Uranus.json"; }

  public:
    Uranus() :
        CelestialBody(file())
    {
    }
    Uranus(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Uranus() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SUN; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::URANUS; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::PLANET; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea