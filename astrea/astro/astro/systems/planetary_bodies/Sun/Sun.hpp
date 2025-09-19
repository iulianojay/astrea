#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Sun : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Sun/Sun.json"; }

  public:
    Sun() :
        CelestialBody(file())
    {
    }
    Sun(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Sun() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SUN; }; // Sun is its own parent/center
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::SUN; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::STAR; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea