#pragma once

#include "astro/propagation/equations_of_motion/EquationsOfMotion.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/time/Time.hpp"
#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/platforms/vehicles/Spacecraft.hpp"

class EquinoctialVop : public EquationsOfMotion {
public:
    EquinoctialVop(const AstrodynamicsSystem& system, const ForceModel& forces) : EquationsOfMotion(system), forces(forces), mu(system.get_center().mu()) {};
    ~EquinoctialVop() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

private:

    mutable bool checkflag = false;
    const double checkTol = 1e-10;

    const ElementSet expectedSet = ElementSet::EQUINOCTIAL;
    const ForceModel& forces;

    const double mu;
};