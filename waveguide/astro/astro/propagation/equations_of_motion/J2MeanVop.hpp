#pragma once

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

class J2MeanVop : public EquationsOfMotion {

  public:
    J2MeanVop(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center()->get_mu()),
        J2(system.get_center()->get_j2()),
        equitorialR(system.get_center()->get_equitorial_radius()){};
    ~J2MeanVop() = default;

    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    mutable bool checkflag = false;
    const Unitless eccTol  = 1e-10 * mp_units::one;
    const Angle incTol     = 1e-10 * mp_units::angular::unit_symbols::rad;

    const ElementSet expectedSet = ElementSet::KEPLERIAN;

    const GravParam mu;
    const Unitless J2;
    const Distance equitorialR;
};

} // namespace astro
} // namespace waveguide