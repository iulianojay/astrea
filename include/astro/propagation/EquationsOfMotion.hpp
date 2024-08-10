#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <exception>

#include "astronomical_constants.h"	// my tables of constants
#include "math_constants.h"         // my common math constants
#include "math_c.hpp"
#include "conversions.hpp"

#include "Spacecraft.hpp"
#include "GravitationalBody.hpp"
#include "AstrodynamicsSystem.hpp"

class EquationsOfMotion
{

public:
    //------------------------------------------------ Methods ------------------------------------------------//
    // Constructors and destructor
    EquationsOfMotion(const AstrodynamicsSystem& system);
    ~EquationsOfMotion();

    // Derivative eval
    void evaluate_state_derivative(double time, double* state, Spacecraft* sc, double* stateDerivative);

    // Event check
    bool check_crash(double* state);

    // Initialize Cnm and Snm for oblateness pert
    void get_oblateness_coefficients(int N, int M);

    // Setters

    // Getters
    const AstrodynamicsSystem& get_system() { return system; }

    double netAccel[3] = { 0.0, 0.0, 0.0 };
    double dcoesdt[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    //-------------------------------------------Gravitational Body--------------------------------------------//

    // Function: Set the gravitational parameter used for integration. This does not effect the properties of the central body
    // Inputs: gravitational parameter, mu (km^3/s^2)
    void set_mu(double mu);

    // Function: Set radius at which the satellite will crash
    // Inputs: Crash Radius (km)
    void set_crash_radius(double crashRadius);

    // Function: Set velocity at which the satellite will crash
    // Inputs: Crash Velocity (km)
    void set_crash_velocity(double crashVelocity);

    // Function: Get the gravitational parameter used for integration. This is not the value of the graviational parameter for the central body
    // Outputs: gravitational parameter, mu (km^3/s^2)
    double get_mu();

    //------------------------------------------Perturbation toggles-------------------------------------------//

    // Function: Switch oblateness perturbation on or off
    // Inputs: true -> on, false -> off
    void switch_oblateness(bool onOff);

    // Function: Switch oblateness perturbation on with a specifc spheroidal accuracey
    // Inputs: N -> zonals
    //         M -> Tessorals
    void switch_oblateness(int N, int M);

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
    void switch_dynamics(std::string dynamics);
    
private:
    //----------------------------------------------- Variables -----------------------------------------------//

    Spacecraft* spacecraft;
    const AstrodynamicsSystem system;
    const GravitationalBody centralBody;

    // Time
    double t{};

    // VoP Variables
    bool checkflag = false;
    const double checkTol = 1e-10;
    
    // Oblateness
    double** P = {};
    double** C = {};
    double** S = {};

    // Drag
    double doEstimateAltitude = false;

    // ECEF and LLA conversions
    double julianDate{};

    // Perturbation toggles
    bool oblateness = false;
    int N = 2, M = 0;

    bool NxMOblateness = false;
    bool drag = false;
    bool lift = false;
    bool srp = false;
    bool nbody = false;
    
    double crashRadius = 0.0;
    double crashVelocity = 0.0;

    // Atmospheric Model
    std::string epoch = "2000-01-01 00:00:00";

    // Equation set
    bool twoBody = false;
    bool cowellsMethod = true;
    bool coesVoP = false;
    bool j2MeanVoP = false;
    bool meesVoP = false;

    //------------------------------------------------ Methods ------------------------------------------------//
    const OrbitalElements evaluate_two_body_dynamics(const OrbitalElements& state) const;
    const OrbitalElements evaluate_cowells_method(const OrbitalElements& state);
    const OrbitalElements evaluate_coes_vop(const OrbitalElements& state);
    const OrbitalElements evaluate_j2mean_coes_vop(const OrbitalElements& state);
    const OrbitalElements evaluate_mees_vop(const OrbitalElements& state);

    const OrbitalElements find_perts(const OrbitalElements& state);

    const OrbitalElements find_accel_oblateness(const OrbitalElements& state);
    const OrbitalElements find_accel_drag(const OrbitalElements& state);
    const OrbitalElements find_accel_lift(const OrbitalElements& state);
    const OrbitalElements find_accel_srp(const OrbitalElements& state);
    const OrbitalElements find_accel_n_body(const OrbitalElements& state);

    void assign_legendre(const double latitude);
    const double find_atmospheric_density(const OrbitalElements& state);
};

