#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Io : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Jupiter/Io.json"; }

  public:
    Io() :
        CelestialBody(file())
    {
    }
    Io(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Io() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::JUPITER; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::IO; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea