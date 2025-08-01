#pragma once

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <units/typedefs.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class CowellsMethod : public EquationsOfMotion {

  public:
    CowellsMethod(const AstrodynamicsSystem& system, const ForceModel& forces = ForceModel()) :
        EquationsOfMotion(system),
        forces(forces),
        mu(system.get_center()->get_mu()){};
    ~CowellsMethod() = default;

    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    const ElementSet expectedSet = ElementSet::CARTESIAN;
    const ForceModel& forces;

    const GravParam mu;
};

} // namespace astro
} // namespace waveguide