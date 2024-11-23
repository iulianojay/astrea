#pragma once

#include "astro/propagation/equations_of_motion/EquationsOfMotion.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/time/Time.hpp"
#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/OrbitalElements.hpp"
#include "astro/platforms/space/Spacecraft.hpp"

class CowellsMethod : public EquationsOfMotion {
public:
    CowellsMethod(const AstrodynamicsSystem& system, const ForceModel& forces) : EquationsOfMotion(system), forces(forces) {};
    ~CowellsMethod() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

private:

    const ElementSet expectedSet = ElementSet::CARTESIAN;
    const ForceModel& forces;
};