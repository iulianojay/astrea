#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

class Triton : public CelestialBody {

    static const std::filesystem::path file() { return ASTREA_ROOT / "data/planetary/Neptune/Triton.json"; }

  public:
    Triton() :
        CelestialBody(file())
    {
    }
    Triton(const AstrodynamicsSystem& system) :
        CelestialBody(file(), system)
    {
    }
    ~Triton() = default;

    constexpr PlanetaryBody get_parent() const override { return PlanetaryBody::NEPTUNE; };
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::TRITON; };
    constexpr CelestialBodyType get_type() const override { return CelestialBodyType::MOON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea