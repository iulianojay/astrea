#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

class Force {
public:
    Force() = default;
    virtual ~Force() = default;

    virtual basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const = 0;
};