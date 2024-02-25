#pragma once

#include "Integrator.hpp"
#include "GravitationalBody.hpp"
#include "LambertSolver.hpp"

class Spacecraft
{
private:
    //---------------------------------------------------------------------------------------------------------//
    //---------------------------------------------- Variabless -----------------------------------------------//
    //---------------------------------------------------------------------------------------------------------//

    // Spacecraft properties
    double mass = 1000.0;
    double coefficientOfDrag = 2.2;
    double coefficientOfLift = 0.9;
    double coefficientOfReflectivity = 1.1;
    double areaRam[3] = { 0.01, 0.0, 0.0 };
    double areaSun[3] = { 0.01, 0.0, 0.0 };
    double areaLift[3] = { 0.01, 0.0, 0.0 };

    // Epoch variables
    std::string epoch = "2000-01-01 12:00:00";
    double epochJulianDate = J2000;

    // Subclasses
    GravitationalBody centralBody;
    Integrator integrator;
    LambertSolver lambertSolver;

public:
    //---------------------------------------------------------------------------------------------------------//
    //------------------------------------------------ Methods ------------------------------------------------//
    //---------------------------------------------------------------------------------------------------------//

    // Constructor
    Spacecraft();
    
    // Destructor
    ~Spacecraft();

    //---------------------------------------Spacecraft property setters---------------------------------------//

    // Function: Set spacecraft mass
    // Inputs: mass (kg)
    void set_mass(double m);

    // Function: Set spacecraft coefficient of drag
    // Inputs: coefficient of drag (--)
    void set_coefficient_of_drag(double Cd);

    // Function: Set spacecraft coefficient of lift
    // Inputs: coefficient of lift (--)
    void set_coefficient_of_lift(double Cl);

    // Function: Set spacecraft coefficient of reflectivity
    // Inputs: coefficient of reflectivity (--)
    void coefficient_of_reflectivity(double Cr);

    // Function: Set spacecraft ram-facing area
    // Inputs: net ram-facing area (m^2)
    void set_ram_area(double aRam);

    // Function: Set spacecraft ram-facing areas
    // Inputs: array of areas (m^2)
    void set_ram_area(double* aRam);

    // Function: Set spacecraft sun-facing area
    // Inputs: net sun-facing area (m^2)
    void set_sun_area(double aSun);

    // Function: Set spacecraft sun-facing areas
    // Inputs: array of areas (m^2)
    void set_sun_area(double* aSun);

    // Function: Set spacecraft earth-facing area
    // Inputs: net earth-facing area (m^2)
    void set_lift_area(double aLift);

    // Function: Set spacecraft earth-facing areas
    // Inputs: array of areas (m^2)
    void set_lift_area(double* aLift);

    //---------------------------------------Spacecraft property getters---------------------------------------//

    // Function: Get spacecraft mass
    // Outputs: mass (kg)
    double get_mass();

    // Function: Get spacecraft coefficient of drag
    // Outputs: coefficient of drag (--)
    double get_coefficient_of_drag();

    // Function: Get spacecraft coefficient of lift
    // Outputs: coefficient of lift (--)
    double get_coefficient_of_lift();

    // Function: Get spacecraft coefficient of reflectivity
    // Outputs: coefficient of reflectivity (--)
    double get_coefficient_of_reflectivity();

    // Function: Get spacecraft ram-facing area
    // Outputs: net ram-facing area / array of areas (m^2)
    double* get_ram_area();

    // Function: Get spacecraft sun-facing area
    // Outputs: net sun-facing area / array of areas (m^2)
    double* get_sun_area();

    // Function: Get spacecraft earth-facing area
    // Outputs: net earth-facing area / array of areas (m^2)
    double* get_lift_area();

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

    //-------------------------------------------Gravitational Body--------------------------------------------//

    // Function: Set the gravitational parameter used for integration. This does not effect the properties of the central body
    // Inputs: gravitational parameter, mu (km^3/s^2)
    void set_mu(double mu);

    // Function: Set the central body
    // Inputs: Name of central body
    void set_central_body(std::string inputCentralBody);

    // Function: Set initial epoch of integration
    // Inputs: Initial epoch string in the format: "MON-DY-YEAR HH:MM:SS.SS"
    void set_epoch(std::string inputEpoch);

    // Function: Set n-bodies to be considered for pertubation calculations
    // Inputs: array of n-body names
    //         integer number of input bodies
    void set_n_bodies(std::string* bodyNames, int numberOfBodies);

    // Function: Set radius at which the satellite will crash
    // Inputs: Crash Radius (km)
    void set_crash_radius(double crashRadius);

    // Function: Set velocity at which the satellite will crash
    // Inputs: Crash Velocity (km)
    void set_crash_velocity(double crashVelocity);

    // Function: Get the gravitational parameter used for integration. This is not the value of the graviational parameter for the central body
    // Outputs: gravitational parameter, mu (km^3/s^2)
    double get_mu();

    //---------------------------------------Integrator property setters---------------------------------------//

    // Function: Set absolute tolerance of Integrator
    // Inputs: absolute tolerance
    void set_abs_tol(double absTol);

    // Function: Set relative tolerance of Integrator
    // Inputs: relative tolerance
    void set_rel_tol(double relTol);

    // Function: Set max number of steps Integrator is allowed to take before exiting
    // Inputs: maximum number of steps
    void set_max_iter(int itMax);

    // Function: Turn output display on or off for Integrator
    // Inputs: true -> on, false -> off
    void switch_print(bool onOff);

    // Function: Turn timer on or off for Integrator
    // Inputs: true -> on, false -> off
    void switch_timer(bool onOff);

    // Function: Change Integrator internal stepping method
    // Inputs: "rk45"  for Runge-Kutta 4(5) method
    //         "rkf45" for Runge-Kutta-Felberg 4(5) method
    //         "rkf78" for Runge-Kutta-Felberg 7(8) method
    //         "dop45" for Dormand-Prince 4(5) method
    //         "dop78" for Dormand-Prince 7(8) method
    void set_step_method(std::string stepMethod);

    // Function: Switch whether or not to use custom equations of motion. Custom EOMs can be modified inside the EquationsOfMotion class
    // Inputs: true -> on, false -> off
    void switch_custom_eom(bool onOff);

    // Function: Set initial timestep taken by the integrator. Only works with variable timesteps
    // Inputs: initial timestep (s)
    void set_initial_timestep(double dt0);

    // Function: Switch whether or not to use a fixed timestep
    // Inputs: true -> on, false -> off
    void switch_fixed_timestep(bool onOff);

    // Function: Switch whether or not to use a fixed timestep and declare that timestep
    // Inputs: true -> on, false -> off
    //         timestep (s)
    void switch_fixed_timestep(bool onOff, double fixedTimeStep);

    // Function: Set fixed timestep. Does not affect variable timestep
    // Inputs: timestep (s)
    void set_timestep(double fixedTimeStep);

    //---------------------------------------Integrator property getters---------------------------------------//

    // Function: Get total number of steps taken during integration
    // Outputs: number of steps taken
    int get_state_history_size();

    // Function: Get all states during integration
    // Inputs: Matrix to write state history too
    void get_state_history(double** stateHistory);

    // Function: Get final state from integration
    // Inputs: Array to write final state too
    void get_final_state(double* state);

    //----------------------------------------------Integration------------------------------------------------//

    // Function: Integrate a given state from one time to another.
    // Inputs: initial time (s)
    //         final time (s)
    //         array corresponding to initial state vector
    void integrate(double timeInitial, double timeFinal, double* stateInitial);

    // Function: Save results of integration to current working directory
    void save();

    // Function: Save results of integration
    // Inputs: filename string
    void save(std::string filename);

    // Function: Integrate an orbit using a Lambert solver
    // Inputs: initial time (s)
    //         final time (s)
    //         array of initial states ([km, km, km, km/s, km/s, km/s])
    //         array to write final states too ([km, km, km, km/s, km/s, km/s])
    void lambert(double timeInitial, double timeFinal, double* state0, double* statef);
};
