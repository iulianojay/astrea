#pragma once

#include <units/typedefs.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class EquinoctialVop : public EquationsOfMotion {

  public:
    EquinoctialVop(const AstrodynamicsSystem& system, const ForceModel& forces) :
        EquationsOfMotion(system),
        forces(forces),
        mu(system.get_center()->get_mu()){};
    ~EquinoctialVop() = default;

    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    mutable bool checkflag                           = false;
    const mp_units::quantity<mp_units::one> checkTol = 1e-10 * mp_units::one;

    const ElementSet expectedSet = ElementSet::EQUINOCTIAL;
    const ForceModel& forces;

    const GravParam mu;
};

} // namespace astro
} // namespace waveguide