#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class Force {
  public:
    Force()          = default;
    virtual ~Force() = default;

    virtual AccelerationVector
        compute_force(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const = 0;
};

} // namespace astro