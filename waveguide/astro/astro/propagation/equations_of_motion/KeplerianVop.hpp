#pragma once

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class KeplerianVop : public EquationsOfMotion {

    using GravParam =
        mp_units::quantity<mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)>;

  public:
    KeplerianVop(const AstrodynamicsSystem& system, const ForceModel& forces, const bool doWarn = true) :
        EquationsOfMotion(system),
        forces(forces),
        mu(system.get_center()->get_mu()),
        doWarn(doWarn){};
    ~KeplerianVop() = default;

    OrbitalElementPartials operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    const mp_units::quantity<mp_units::one> checkTol = 1e-10 * mp_units::one;

    const ElementSet expectedSet = ElementSet::KEPLERIAN;
    const ForceModel& forces;
    const GravParam mu;
    const bool doWarn;

    void check_degenerate(const mp_units::quantity<mp_units::one>& ecc, const mp_units::quantity<mp_units::angular::unit_symbols::rad>& inc) const;
};

} // namespace astro
} // namespace waveguide