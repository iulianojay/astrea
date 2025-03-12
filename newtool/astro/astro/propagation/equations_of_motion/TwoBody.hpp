#pragma once

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/time/Time.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>

class TwoBody : public EquationsOfMotion {
public:
    TwoBody(const AstrodynamicsSystem& system) : EquationsOfMotion(system), mu(system.get_center()->get_mu()) {};
    ~TwoBody() = default;

    OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

private:

    const ElementSet expectedSet = ElementSet::CARTESIAN;
    const double mu;
};