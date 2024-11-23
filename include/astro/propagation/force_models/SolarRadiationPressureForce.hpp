#pragma once

#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/space/Spacecraft.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"

class SolarRadiationPressureForce : public Force {
public:
    SolarRadiationPressureForce() = default;
    ~SolarRadiationPressureForce() = default;

    basis_array compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const override;

private:
};