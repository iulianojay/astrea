#pragma once

#ifndef SWIG
    #include <string>
    #include <iostream>
    #include <cmath>
    #include <algorithm>
    #include <stdio.h>
    #include <vector>
    #include <exception>
#endif

#include "astro/platforms/Vehicle.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"

#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"

class EquationsOfMotion {
public:

    EquationsOfMotion(const AstrodynamicsSystem& system) : system(system) {};
    virtual ~EquationsOfMotion() = default;

    virtual OrbitalElements operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const = 0;
    virtual bool check_crash(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const = 0;
    virtual const ElementSet& get_expected_set() const = 0;
    const AstrodynamicsSystem& get_system() const { return system; }

protected:

    const AstrodynamicsSystem& system;
};

