#pragma once

#include "astro/platforms/vehicles/Spacecraft.hpp"
#include "astro/systems/GravitationalBody.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"

#include "astro/propagation/equations_of_motion/EquationsOfMotion.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/time/Time.hpp"
#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/platforms/vehicles/Spacecraft.hpp"

class J2MeanVop : public EquationsOfMotion {
public:

    J2MeanVop(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center().mu()),
        J2(system.get_center().j2()),
        equitorialR(system.get_center().eqR())
    {};
    ~J2MeanVop() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

private:

    mutable bool checkflag = false;
    const double checkTol = 1e-10;

    const ElementSet expectedSet = ElementSet::KEPLERIAN;

    const double mu;
    const double J2;
    const double equitorialR;
};