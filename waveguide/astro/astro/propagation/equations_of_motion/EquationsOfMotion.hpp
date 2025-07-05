#pragma once

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astro {

class EquationsOfMotion {
  public:
    EquationsOfMotion(const AstrodynamicsSystem& system) :
        system(system){};
    virtual ~EquationsOfMotion() = default;

    virtual OrbitalElementPartials operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const = 0;
    virtual bool check_crash(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
    {
        return false; // TODO: Implement these
    }

    virtual const ElementSet& get_expected_set() const = 0;
    const AstrodynamicsSystem& get_system() const { return system; }

  protected:
    const AstrodynamicsSystem& system;
};

} // namespace astro
