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
    const double checkTol  = 1e-10;

    const ElementSet expectedSet = ElementSet::KEPLERIAN;

    const double mu;
    const double J2;
    const double equitorialR;
};