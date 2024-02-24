#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>

#include "astronomical_constants.h"	// my tables of constants
#include "math_constants.h"         // my common math constants
#include "convert.hpp"
#include "GravitationalBody.hpp"

class EquationsOfMotion
{
private:
    //----------------------------------------------- Variables -----------------------------------------------//

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

public:
    //----------------------------------------------- Variables -----------------------------------------------//

    // Perturbation toggles
    bool oblateness = false;
    int N = 2, M = 0;

    bool NxMOblateness = false;
    bool drag = false;
    bool lift = false;
    bool srp = false;
    bool nbody = false;

    // Allows for chaning mu
    double mu{};

    // Atmospheric Model
    std::string epoch = "2000-01-01 00:00:00";
    bool useEarthGRAM = false;

    // Spacecraft properties
    double mass = 1000;
    double coefficientOfDrag = 2.2;
    double coefficientOfLift = 0.9;
    double coefficientOfReflectivity = 1.1;
    double areaRam[3] = { 0.01, 0.0, 0.0 };
    double areaSun[3] = { 0.01, 0.0, 0.0 };
    double areaLift[3] = { 0.01, 0.0, 0.0 };

    // Equation set
    bool twoBody = false;
    bool cowellsMethod = true;
    bool coesVoP = false;
    bool j2MeanVoP = false;
    bool meesVoP = false;

    //------------------------------------------------ Methods ------------------------------------------------//
    // Constructors and destructor
    EquationsOfMotion();
    ~EquationsOfMotion();

    // Property assignment
    void assign_eom_properties(GravitationalBody &centralBody);

    // Derivative eval
    void evaluate_state_derivative(double time, double* state, double* stateDerivative);

    // Event check
    bool check_crash(double* state);
    double crashRadius = 0.0;
    double crashVelocity = 0.0;

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
};

