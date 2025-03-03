#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/Vehicle.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"

class Force {
public:
    Force() = default;
    virtual ~Force() = default;

    virtual AccelerationVector compute_force(const mp_units::quantity<mp_units::non_si::day>& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const = 0;
};