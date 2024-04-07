
#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>					// reading/writing to files
#include <math.h>

#include "rk_constants.h"			// RK Butcher Tableau

#include "EquationsOfMotion.hpp"

class Integrator
{
public:
	// Stepper
	enum odeStepper {
        rk45,	// Traditional Runge-Kutta 4(5)th order 6 stage method
        rkf45,	// Runge-Kutta-Fehlberg 4(5)th order 6 stage method
        rkf78,	// Runge-Kutta-Fehlberg 7(8)th order 13 stage method

        dop45,	// Dormand-Prince Runge-Kutta 4(5)th 7-6 stage method. This is the method Matlab's ode45 uses
        dop78,	// Dormand-Prince Runge-Kutta 7(8)th 13-12 stage method.
	};

private:
	//----------------------------------------------- Variables -----------------------------------------------//

	// Integrator constants
	const double epsilon = 0.8;				// relative local step error tolerance usually 0.8 or 0.9. 

	const double minErrorCatch = 2.0e-4;	// if maximum error is less than this,
	const double minErrorStepFactor = 5.0;  // increase step by this factor

	const double minRelativeStepSize = 0.2; // if the step size decreases by more than this factor, reduce the relative 
										    // step size to this value

	// Iteration variables
    int iteration = 0;
	int variableStepIteration = 0;				// Inner loop iteration count
	const int maxVariableStepIterations = 1000; // max iterations for step sizing loop -> jj shouldn't get above ~10

    // Function evals
    int functionEvaluations = 0;

	// Number of states
	static const int numberOfStates = 6;

	// Time variables
	double time{};
	double timeStep{};                      // initial timestep
	double timeStepPrevious{};			    // store for IP step controller
	double relativeTimeStep{};			    // predicted relative change in step size
    bool forwardTime = true;

	// State variables
	double state[numberOfStates] = {};		// state at current iteration
	double stateNew[numberOfStates] = {};
	double stateError[numberOfStates] = {};

	// Error variables
    double error{};
	double errorMax{};
	double errorMaxPrevious{};

	bool stepSuccess = false;
    bool eventTrigger = false;

    // Butcher Tablaeu
    int numberOfStages{};
    static const int maxNumberOfStages = 13;
    double a[maxNumberOfStages][maxNumberOfStages] = {};
    double b[maxNumberOfStages] = {};
    double bhat[maxNumberOfStages] = {};
    double db[maxNumberOfStages] = {};
    double c[maxNumberOfStages] = {};

	// ith order steps
    double kMatrix[maxNumberOfStages][numberOfStates] = {};
	double statePlusKi[numberOfStates] = {};
	double YFinalPrevious[numberOfStates] = {};

	// Clock variables
	clock_t startClock{};
	clock_t endClock{};

	// Error Messages
	const std::string underflowErrorMessage = "Error: Stepsize underflow. \n\n";
	const std::string innerLoopStepOverflowErrorMessage = "Error: Max iterations exceeded. Unable to find stepsize within tolerance. \n\n";
	const std::string outerLoopStepOverflowErrorMessage = "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try again. \n\n";
    const std::string crashMessage = "Note: Object crashed into central body. \n\n";

    // Print variables
    int day = 1;
    int checkDay = 0;

	// Tolerances
	double absoluteTolerance = 1.0e-8;
	double relativeTolerance = 1.0e-8;

	// Initial step size
	double timeStepInitial = 100.0;

	// Iteration variables
	int iterMax = 1e8; // absurdly high so it doesn't interfere with integration

	// Run options
	bool printOn = false;
	bool timerOn = false;

	odeStepper stepMethod = dop45;
    
    // Fake fixed step
    bool useFixedStep = false;
    double fixedTimeStep = 1.0;

    // Equations of Motion
    EquationsOfMotion equationsOfMotion;
	
	// Time and state vectors
	std::vector<double> timeVector{};
	std::vector<double> stateVectorOne{};
	std::vector<double> stateVectorTwo{};
	std::vector<double> stateVectorThree{};
	std::vector<double> stateVectorFour{};
	std::vector<double> stateVectorFive{};
    std::vector<double> stateVectorSix{};

    std::vector<double> extraVector{};
    std::vector<double> extraVector2{};

	//------------------------------------------------ Methods ------------------------------------------------//

	// Equations of motion
    void find_state_derivative(double time, double* state, double* stateDerivative);
    void evaluate_custom_state_derivative(double time, double* state, double* stateDerivative);

	// Vector utilities
	void reserve_space(int N);
	void store_iteration();
    void cleanup();

	// Stepping methods
    void setup_stepper();
    void try_step();

	// Error Methods
	void check_error();

	// Print details
	void print_iteration(double timeFinal, double* stateInitial);
	void print_performance();

	// Timer
	void startTimer() { if (timerOn) { startClock = clock(); } };
	void endTimer() { if (timerOn) { endClock = clock(); } }

    // Event Function
    void check_event();

public:

	//------------------------------------------------ Methods ------------------------------------------------//

    // Constructor and destructor
    Integrator();
    ~Integrator();

	// Integrate
    void integrate(double timeInitial, double timeFinal, double* stateInitial);
     
	// Save Results
	void save();
	void save(std::string filename);

    // Function: Get total number of steps taken during integration
    // Outputs: number of steps taken
    int get_state_history_size();

    // Function: Get all states during integration
    // Inputs: Matrix to write state history too
    void get_state_history(double** stateHistory);

    // Get final state
    void copy_final_state(double* state);

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
};