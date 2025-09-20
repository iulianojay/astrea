#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Jupiter : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Jupiter/Jupiter.json"; }

  public:
    Jupiter() :
        CelestialBody(file())
    {
    }
    Jupiter(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Jupiter() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::SUN; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::JUPITER; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::PLANET; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea