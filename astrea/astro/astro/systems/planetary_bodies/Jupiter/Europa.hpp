#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Europa : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Jupiter/Europa.json"; }

  public:
    Europa() :
        CelestialBody(file())
    {
    }
    Europa(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Europa() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::JUPITER; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::EUROPA; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea