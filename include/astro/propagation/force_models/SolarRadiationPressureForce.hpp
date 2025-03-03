#pragma once

#include "astro/element_sets/orbital_elements/Cartesian.hpp"
#include "astro/types/typedefs.hpp"
#include "astro/platforms/Vehicle.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"

class SolarRadiationPressureForce : public Force {
public:
    SolarRadiationPressureForce() = default;
    ~SolarRadiationPressureForce() = default;

    AccelerationVector compute_force(const mp_units::quantity<mp_units::non_si::day>& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

private:
};