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

#include "astro/constants/astronomical_constants.h"
#include "astro/constants/math_constants.h"
#include "astro/utilities/math/math_c.hpp"
#include "astro/utilities/conversions.hpp"

#include "astro/platforms/space/Spacecraft.hpp"
#include "astro/systems/GravitationalBody.hpp"
#include "astro/systems/AstrodynamicsSystem.hpp"

#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/propagation/force_models/AtmosphericForce.hpp"
#include "astro/propagation/force_models/NBodyForce.hpp"
#include "astro/propagation/force_models/OblatenessForce.hpp"
#include "astro/propagation/force_models/SolarRadiationPressureForce.hpp"

class EquationsOfMotion {
public:

    enum DynamicsSet {
        TWO_BODY,
        COWELLS,
        COES_VOP,
        J2_MEAN,
        MEES_VOP
    };

    EquationsOfMotion(const AstrodynamicsSystem& system, const ForceModel& forces) : system(system), forces(forces) {};
    ~EquationsOfMotion() = default;

    // Derivative eval
    OrbitalElements evaluate_state_derivative(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);

    // Event check
    bool check_crash(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const;

    // Function: Set radius at which the satellite will crash
    // Inputs: Crash Radius (km)
    void set_crash_radius(double crashRadius);

    // Function: Set velocity at which the satellite will crash
    // Inputs: Crash Velocity (km)
    void set_crash_velocity(double crashVelocity);

    // Function: Switch oblateness perturbation on with a specifc spheroidal accuracey
    // Inputs: N -> zonals
    //         M -> Tessorals
    void set_oblateness(size_t N, size_t M);

    // Function: Switch dynamics set
    // Inputs: "Two Body" or "two body"             for simple 2-body mechanics. Perturbations will be ignored
    //         "Cowells Method" or "cowells method" for cowell's method VoP
    //         "COEs VoP" or "coes vop"             for traditional COEs VoP
    //         "J2 Mean VoP" or "j2 mean vop"       for J2 Mean VoP. All perturbations other than J2 will be ignored
    //         "MEEs VoP" or "mees vop"             for modified equinoctial elements VoP
    void switch_dynamics(DynamicsSet _dynamicsSet) {
        dynamicsSet = _dynamicsSet;
    }
    void switch_dynamics(std::string dynamicsSet) {
        switch_dynamics(dyanmicsSetMap.at(dynamicsSet));
    };

    const ElementSet& get_expected_set() const {
        return elementSetMap.at(dynamicsSet);
    }

    const AstrodynamicsSystem& get_system() const { return system; }

    void toggle_force(std::string force, bool onOff);

private:

    const AstrodynamicsSystem& system;
    const ForceModel& forces;

    // VoP Variables
    bool checkflag = false;
    const double checkTol = 1e-10;

    // Event
    double crashRadius = 0.0;
    double crashVelocity = 0.0;

    // ECEF and LLA conversions
    Time julianDate{};

    // Atmospheric Model
    std::string epoch = "2000-01-01 00:00:00";

    // Equation set
    DynamicsSet dynamicsSet = TWO_BODY;

    const std::unordered_map<std::string, DynamicsSet> dyanmicsSetMap {
        {"TWO_BODY", TWO_BODY},
        {"COWELLS",  COWELLS},
        {"COES_VOP", COES_VOP},
        {"J2_MEAN",  J2_MEAN},
        {"MEES_VOP", MEES_VOP}
    };
    const std::unordered_map<DynamicsSet, ElementSet> elementSetMap {
        {TWO_BODY, ElementSet::CARTESIAN},
        {COWELLS,  ElementSet::CARTESIAN},
        {COES_VOP, ElementSet::COE},
        {J2_MEAN,  ElementSet::COE},
        {MEES_VOP, ElementSet::MEE}
    };

    //------------------------------------------------ Methods ------------------------------------------------//
    const OrbitalElements evaluate_two_body_dynamics(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements evaluate_cowells_method(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements evaluate_coes_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements evaluate_j2mean_coes_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements evaluate_mees_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);

    const basis_array find_perts(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);

    const OrbitalElements find_accel_oblateness(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements find_accel_drag(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements find_accel_lift(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements find_accel_srp(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
    const OrbitalElements find_accel_n_body(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);

    void assign_legendre(const double latitude);
    const double find_atmospheric_density(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);
};

