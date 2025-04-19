#pragma once

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/time/Time.hpp>

class TwoBody : public EquationsOfMotion {

    using GravParam =
        mp_units::quantity<mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)>;

  public:
    TwoBody(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center()->get_mu()){};
    ~TwoBody() = default;

    OrbitalElementPartials operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const override;
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    const ElementSet expectedSet = ElementSet::CARTESIAN;
    const GravParam mu;
};