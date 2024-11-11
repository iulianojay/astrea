#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"

class AtmosphericForce : public Force {
public:

    AtmosphericForce() = default;
    ~AtmosphericForce() = default;

    basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const;

private:

    const OrbitalElements find_accel_drag_and_lift(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const;
    const double AtmosphericForce::find_atmospheric_density(const double& julianDate, const OrbitalElements& state, const AstrodynamicsSystem& sys) const;

};