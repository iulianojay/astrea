#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/space/Spacecraft.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"

class Force {
protected:
    Force() = default;
    virtual ~Force() = default;

public:
    virtual basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const = 0;
};