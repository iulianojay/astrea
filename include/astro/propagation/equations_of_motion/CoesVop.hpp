#pragma once

#include "astro/propagation/equations_of_motion/EquationsOfMotion.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/time/Time.hpp"
#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/platforms/space/Spacecraft.hpp"

class CoesVop : public EquationsOfMotion {
public:

    CoesVop(const AstrodynamicsSystem& system, const ForceModel& forces, const bool doWarn = true) :
        EquationsOfMotion(system),
        forces(forces),
        mu(system.get_center().mu()),
        doWarn(doWarn)
    {};
    ~CoesVop() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

private:

    const double checkTol = 1e-10;

    const ElementSet expectedSet = ElementSet::COE;
    const ForceModel& forces;

    const double mu;
    const bool doWarn;

    void check_degenerate(const double& ecc, const double& inc) const;
};