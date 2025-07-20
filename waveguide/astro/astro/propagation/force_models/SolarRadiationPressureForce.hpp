#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

class SolarRadiationPressureForce : public Force {
  public:
    SolarRadiationPressureForce()  = default;
    ~SolarRadiationPressureForce() = default;

    AccelerationVector
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
};

} // namespace astro
} // namespace waveguide