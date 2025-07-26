#pragma once

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class CowellsMethod : public EquationsOfMotion {

    using GravParam =
        mp_units::quantity<mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)>;

  public:
    CowellsMethod(const AstrodynamicsSystem& system, const ForceModel& forces) :
        EquationsOfMotion(system),
        forces(forces),
        mu(system.get_center()->get_mu()){};
    ~CowellsMethod() = default;

    OrbitalElementPartials operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    const ElementSet expectedSet = ElementSet::CARTESIAN;
    const ForceModel& forces;

    const GravParam mu;
};

} // namespace astro
} // namespace waveguide