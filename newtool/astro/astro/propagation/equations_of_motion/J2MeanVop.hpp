#pragma once

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/time/Time.hpp>

class J2MeanVop : public EquationsOfMotion {

    using GravParam =
        mp_units::quantity<mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)>;
    using Unitless = mp_units::quantity<mp_units::one>;
    using Distance = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using Degree   = mp_units::quantity<mp_units::si::unit_symbols::rad>;

  public:
    J2MeanVop(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center()->get_mu()),
        J2(system.get_center()->get_j2()),
        equitorialR(system.get_center()->get_equitorial_radius()){};
    ~J2MeanVop() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    mutable bool checkflag = false;
    const Unitless ecccTol = 1e-10 * mp_units::one;
    const Degree incTol    = 1e-10 * mp_units::si::unit_symbols::rad;

    const ElementSet expectedSet = ElementSet::KEPLERIAN;

    const GravParam mu;
    const Unitless J2;
    const Distance equitorialR;
};