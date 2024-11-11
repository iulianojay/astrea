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

    // Enums
    enum DynamicsSet {
        TWO_BODY,
        COWELLS,
        COES_VOP,
        J2_MEAN,
        MEES_VOP
    };

    EquationsOfMotion(const AstrodynamicsSystem& system, const std::vector<DynamicForce> _forces) : system(system) {
        for (const auto& force : _forces) {
            forces.build(force);
        }
    };
    ~EquationsOfMotion() = default;

    // Derivative eval
    OrbitalElements evaluate_state_derivative(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft);

    // Event check
    bool check_crash(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const;

    // Initialize Cnm and Snm for oblateness pert
    void get_oblateness_coefficients(int N, int M);

    // Function: Set radius at which the satellite will crash
    // Inputs: Crash Radius (km)
    void set_crash_radius(double crashRadius);

    // Function: Set velocity at which the satellite will crash
    // Inputs: Crash Velocity (km)
    void set_crash_velocity(double crashVelocity);

    // Function: Switch oblateness perturbation on or off
    // Inputs: true -> on, false -> off
    void switch_oblateness(bool onOff);

    // Function: Switch oblateness perturbation on with a specifc spheroidal accuracey
    // Inputs: N -> zonals
    //         M -> Tessorals
    void switch_oblateness(size_t N, size_t M);

    // Function: Switch drag perturbation on or off
    // Inputs: true -> on, false -> off
    void switch_drag(bool onOff);

    // Function: Switch lift perturbation on or off
    // Inputs: true -> on, false -> off
    void switch_lift(bool onOff);

    // Function: Switch solar radiation pressure perturbation on or off
    // Inputs: true -> on, false -> off
    void switch_srp(bool onOff);

    // Function: Switch n-body effects on or off
    // Inputs: true -> on, false -> off
    void switch_nbody(bool onOff);

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

private:

    AstrodynamicsSystem system;

    // VoP Variables
    bool checkflag = false;
    const double checkTol = 1e-10;

    // Drag
    double doEstimateAltitude = false;

    // ECEF and LLA conversions
    Time julianDate{};

    // Perturbation toggles
    bool oblateness = false;
    size_t N = 2, M = 0;

    bool NxMOblateness = false;
    bool drag = false;
    bool lift = false;
    bool srp = false;
    bool nbody = false;

    double crashRadius = 0.0;
    double crashVelocity = 0.0;

    ForceModel forces;

    // Atmospheric Model
    std::string epoch = "2000-01-01 00:00:00";

    // Equation set
    DynamicsSet dynamicsSet = TWO_BODY;

    const std::unordered_map<std::string, DynamicsSet> dyanmicsSetMap {
        {"TWO_BODY", TWO_BODY},
        {"COWELLS", COWELLS},
        {"COES_VOP", COES_VOP},
        {"J2_MEAN", J2_MEAN},
        {"MEES_VOP", MEES_VOP}
    };
    const std::unordered_map<DynamicsSet, ElementSet> elementSetMap {
        {TWO_BODY, ElementSet::CARTESIAN},
        {COWELLS, ElementSet::CARTESIAN},
        {COES_VOP, ElementSet::COE},
        {J2_MEAN, ElementSet::COE},
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

