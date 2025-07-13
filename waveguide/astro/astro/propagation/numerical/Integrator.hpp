
#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/numerical/rk_constants.h> // RK Butcher Tableau
#include <astro/state/StateHistory.hpp>
#include <astro/time/Interval.hpp>
#include <astro/units/units.hpp>

namespace astro {

class Integrator {

  public:
    // Stepper
    enum odeStepper {
        RK45,  // Traditional Runge-Kutta 4(5)th order 6 stage method
        RKF45, // Runge-Kutta-Fehlberg 4(5)th order 6 stage method
        RKF78, // Runge-Kutta-Fehlberg 7(8)th order 13 stage method
        DOP45, // Dormand-Prince Runge-Kutta 4(5)th 7-6 stage method. This is the method Matlab's ode45 uses
        DOP78, // Dormand-Prince Runge-Kutta 7(8)th 13-12 stage method.
    };

    static inline Interval defaultInterval{ 0.0 * mp_units::non_si::day, 1.0 * mp_units::non_si::day };

    //------------------------------------------------ Methods ------------------------------------------------//

    // Constructor and destructor
    Integrator()  = default;
    ~Integrator() = default;

    // Integrate
    StateHistory propagate(const Date& epoch, const Interval& interval, const EquationsOfMotion& eom, Vehicle& vehicle, bool store = false);
    StateHistory
        propagate(const Date& epoch, const Time& timeInitial, const Time& timeFinal, const EquationsOfMotion& eom, Vehicle& vehicle, bool store = false);

    //---------------------------------------Integrator property setters---------------------------------------//

    // Function: Set absolute tolerance of Integrator
    // Inputs: absolute tolerance
    void set_abs_tol(Unitless absTol);

    // Function: Set relative tolerance of Integrator
    // Inputs: relative tolerance
    void set_rel_tol(Unitless relTol);

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
    // Inputs: "RK45"  for Runge-Kutta 4(5) method
    //         "RKF45" for Runge-Kutta-Felberg 4(5) method
    //         "RKF78" for Runge-Kutta-Felberg 7(8) method
    //         "DOP45" for Dormand-Prince 4(5) method
    //         "DOP78" for Dormand-Prince 7(8) method
    void set_step_method(std::string stepMethod);

    // Function: Set initial timestep taken by the integrator. Only works with variable timesteps
    // Inputs: initial timestep (s)
    void set_initial_timestep(Time dt0);

    // Function: Switch whether or not to use a fixed timestep
    // Inputs: true -> on, false -> off
    void switch_fixed_timestep(bool onOff);

    // Function: Switch whether or not to use a fixed timestep and declare that timestep
    // Inputs: true -> on, false -> off
    //         timestep (s)
    void switch_fixed_timestep(bool onOff, Time fixedTimeStep);

    // Function: Set fixed timestep. Does not affect variable timestep
    // Inputs: timestep (s)
    void set_timestep(Time fixedTimeStep);

    int n_func_evals() { return functionEvaluations; }

  private:
    // Integrator constants
    const Unitless epsilon             = 0.8;    // relative local step error tolerance usually 0.8 or 0.9.
    const Unitless minErrorCatch       = 2.0e-4; // if maximum error is less than this,
    const Unitless minErrorStepFactor  = 5.0;    // increase step by this factor
    const Unitless minRelativeStepSize = 0.2;    // if the step size decreases by more than this factor, reduce the
                                                 // relative step size to this value

    // Iteration variables
    unsigned long iteration                       = 0;
    unsigned long variableStepIteration           = 0; // Inner loop iteration count
    const unsigned long maxVariableStepIterations = 1000; // max iterations for step sizing loop -> jj shouldn't get above ~10

    // Function evals
    int functionEvaluations = 0;

    // Number of states
    static const std::size_t maxStates = 10;

    // Time variables
    bool forwardTime = true;
    Time timeStepPrevious;

    // Error variables
    bool stepSuccess  = false;
    bool eventTrigger = false;
    Unitless maxErrorPrevious;

    // Butcher Tablaeu
    std::size_t nStages{};
    static const std::size_t maxStages                       = 13;
    std::array<std::array<Unitless, maxStages>, maxStages> a = {};
    std::array<Unitless, maxStages> b                        = {};
    std::array<Unitless, maxStages> bhat                     = {};
    std::array<Unitless, maxStages> db                       = {};
    std::array<Unitless, maxStages> c                        = {};

    // ith order steps
    std::array<OrbitalElements, maxStages> kMatrix = {};
    OrbitalElements statePlusKi;
    OrbitalElementPartials YFinalPrevious;

    // Clock variables
    clock_t startClock{};
    clock_t endClock{};

    // Error Messages
    const std::string underflowErrorMessage = "Integration Error: Stepsize underflow. \n\n";
    const std::string innerLoopStepOverflowErrorMessage =
        "Integration Error: Max iterations exceeded. Unable to find stepsize within tolerance. \n\n";
    const std::string outerLoopStepOverflowErrorMessage =
        "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try again. \n\n";
    const std::string crashMessage = "Note: Object crashed into central body. \n\n";

    // Print variables
    int checkDay = 0;

    // Tolerances
    Unitless absoluteTolerance = 1.0e-13;
    Unitless relativeTolerance = 1.0e-13;

    // Initial step size
    Time timeStepInitial = 100.0 * mp_units::si::unit_symbols::s;

    // Iteration variables
    unsigned long iterMax = 1e8; // absurdly high so it doesn't interfere with integration

    // Run options
    bool printOn = false;
    bool timerOn = false;

    odeStepper stepMethod = DOP45;

    // Fake fixed step
    bool useFixedStep  = false;
    Time fixedTimeStep = 1.0 * mp_units::si::unit_symbols::s;

    //------------------------------------------------ Methods ------------------------------------------------//

    // Equations of motion
    OrbitalElementPartials
        find_state_derivative(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    // Stepping methods
    void setup_stepper();
    void try_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    // Error Methods
    void check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state);

    // Print details
    void print_iteration(const Time& time, const OrbitalElements& state, const Time& timeFinal, const OrbitalElements& stateInitial);
    void print_performance() const;

    // Timer
    void startTimer()
    {
        if (timerOn) { startClock = clock(); }
    };
    void endTimer()
    {
        if (timerOn) { endClock = clock(); }
    }

    // Event Function
    void check_event(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);
};

} // namespace astro