#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <vector>

#include "astronomical_constants.h"	// my tables of constants
#include "math_constants.h"         // my common math constants
#include "math_c.hpp"

#include "Spacecraft.hpp"
#include "GravitationalBody.hpp"
#include "AstrodynamicsSystem.hpp"

class EquationsOfMotion
{

public:
    //------------------------------------------------ Methods ------------------------------------------------//
    // Constructors and destructor
    EquationsOfMotion();
    ~EquationsOfMotion();

    // Derivative eval
    void evaluate_state_derivative(double time, double* state, Spacecraft* sc, double* stateDerivative);

    // Event check
    bool check_crash(double* state);

    // Initialize Cnm and Snm for oblateness pert
    void get_oblateness_coefficients(int N, int M);

    // Setters

    // Getters
    double get_atmospheric_density(double time, double* state);

    double* get_accel_gravity();
    double* get_accel_oblateness();
    double* get_accel_drag();
    double* get_accel_lift();
    double* get_accel_srp();
    double* get_accel_nBody();

    double* get_net_accel();
    double* get_coes_rates();

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
    AstrodynamicsSystem* system;

    // Central Body properties
    int planetId{}, moonId{};
    double equitorialR{};
    double polarR{};
    double j2{};
    double bodyRotationRate{};

    // Time
    double t{};

    // Cartesian elements
    double x{}, y{}, z{}, vx{}, vy{}, vz{};
    double dxdt{}, dydt{}, dzdt{}, dvxdt{}, dvydt{}, dvzdt{};
    double R{}, V{};

    double radius[3] = {};
    double velocity[3] = {};
    double rBCBF[3] = {};
    double lla[3] = {};

    double initialJulianDate{};
    double** radiusSunToCentralBody = {};

    int index{};
    double tempA{}, tempB{}, tempC{}, tempD{};

    // COEs VoP Variables
    double h{};     // angular momentum / 4th equinoctial element
    double ecc{};   // eccentricity
    double inc{};   // inclination
    double w{};     // argument of perigee 
    double raan{};  // right ascension of ascending node 
    double theta{}; // true anomaly
    double u{};     // argument of latitude

    double coes[6] = {};
    double cosTA{}, sinTA{}, cosU{}, sinU{}, h_2{}, hOverR_2{};

    double dhdt{}, deccdt{}, dincdt{}, dthetadt{}, draandt{}, dwdt{};

    // Equinoctial elements
    double p{}, f{}, g{}, k{}, L{};
    double dpdt{}, dfdt{}, dgdt{}, dkdt{}, dLdt{};

    double cosL{}, sinL{}, s_2{};

    // VoP Variables
    bool checkflag = false;

    double Rhat[3] = {};
    double Nhat[3] = {};
    double That[3] = {};

    double Tv[3] = {};
    double normTv{};

    double radialPert{}, normalPert{}, tangentialPert{};

    // Gravity
    double muOverRadiusCubed{};

    // Oblateness
    double oneOverRadiusSquared{}, zSquaredTimes5OverRadiusSquared{};

    double xBCBF{}, yBCBF{};
    double nn{}, mm{};
    double cosLat{}, sinLat{}, tanLat{}, alpha{}, beta{}, gamma{}, tau{}, cosLongM{}, sinLongM{}, rRatio{};
    double dVdr{}, dVdlat{}, dVdlong{}, dVdrInnerSum{}, dVdlatInnerSum{}, dVdlongInnerSum{};

    double** P = {};
    double** C = {};
    double** S = {};

    double nMinusMFactorial{}, nPlusMFactorial{}, Nnm{};

    double drdrBCBF[3] = {};
    double dlatdrBCBF[3] = {};
    double dlongdrBCBF[3] = {};
    double accelOblatenessBCBF[3] = {};

    // Drag
    double relativeVelocity[3] = { 0.0, 0.0, 0.0 };
    double dragMagnitude{}, relativeVelocityMagnitude{};
    double altitude{};
    double atmosphericDensity{}, referenceDensity{}, referenceAltitude{}, scaleHeight{};
    double denWatch = {};
    double doEstimateAltitude = false;

    // ECEF and LLA conversions
    double julianDate{};
    double latitude{}, longitude{};

    // Lift
    double radialVelcityMagnitude{};

    // SRP
    int sizeOfDateArray = 1000000; // Enough for 3000 years if there's one point per day -> gets overwritten anyway

    double solarRadiationPressure{}, fractionOfRecievedSunlight{};
    double referenceAngle{}, referenceAngle1{}, referenceAngle2{};

    double rP[3] = {};
    double rPs[3] = {};
    double normRP{}, normRPs{};

    double Xu{}, alphaps{};

    double radiusSpacecraftToSun[3] = { 0.0, 0.0, 0.0 };
    double radiusCentralBodyToSun[3] = { 0.0, 0.0, 0.0 };
    double radialMagnitudeCentralBodyToSun{}, radialMagnitudeSpacecraftToSun{};

    // N Body
    int numberOfBodies{};
    double radiusCentralBodyToNbody[3] = { 0.0, 0.0, 0.0 };
    double radiusSpacecraftToNbody[3] = { 0.0, 0.0, 0.0 };
    double radiusSpacecraftToNbodyMagnitude{}, radiusCentralToNbodyMagnitude{};

    double* nBodyGravitationalParameter{};
    double** radiusSunToNbody{};

    // Acceleration arrays
    double accelOblateness[3] = { 0.0, 0.0, 0.0 };
    double accelDrag[3] = { 0.0, 0.0, 0.0 };
    double accelLift[3] = { 0.0, 0.0, 0.0 };
    double accelSRP[3] = { 0.0, 0.0, 0.0 };
    double accelNBody[3] = { 0.0, 0.0, 0.0 };
    double accelPerts[3] = { 0.0, 0.0, 0.0 };

    // JPL Dust heating stuff
    double aalpha = 1.257;
    double bbeta = 0.4;
    double ggamma = 1.1;

    double dAir = 0.36e-12; 
    double diam = {};
    double RAir = 287.0;
    double kB = 1.3806e-23;

    double nInf = {};
    double llambda = {};
    double Kn = {};

    double CKnPrevious = {};
    double CKn = {};

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

    // Allows for manually changing mu
    double mu{};

    // Atmospheric Model
    std::string epoch = "2000-01-01 00:00:00";

    // Equation set
    bool twoBody = false;
    bool cowellsMethod = true;
    bool coesVoP = false;
    bool j2MeanVoP = false;
    bool meesVoP = false;

    //------------------------------------------------ Methods ------------------------------------------------//
    void evaluate_two_body_dynamics();
    void evaluate_cowells_method();
    void evaluate_coes_vop();
    void evaluate_j2mean_coes_vop();
    void evaluate_mees_vop();

    void find_perts();

    void find_accel_oblateness();
    void find_accel_drag();
    void find_accel_lift();
    void find_accel_srp();
    void find_accel_n_body();

    void assign_legendre();
    void find_atmospheric_density();
};

