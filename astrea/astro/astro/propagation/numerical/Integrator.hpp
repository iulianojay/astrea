/**
 * @file Integrator.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Numerical integrator for orbital mechanics propagation
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
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

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/numerical/rk_constants.h> // RK Butcher Tableau
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/time/Interval.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Integrator class for numerical propagation of orbital mechanics problems.
 *
 * This class implements various Runge-Kutta methods for integrating the equations of motion
 * of a vehicle in space. It allows for variable step sizes, error control, and event handling.
 */
class Integrator {

  public:
    /**
     * @brief Enumeration for different Runge-Kutta stepper methods.
     */
    enum odeStepper {
        RK45,  //!< Traditional Runge-Kutta 4(5)th order 6 stage method
        RKF45, //!< Runge-Kutta-Fehlberg 4(5)th order 6 stage method
        RKF78, //!< Runge-Kutta-Fehlberg 7(8)th order 13 stage method
        DOP45, //!< Dormand-Prince Runge-Kutta 4(5)th 7-6 stage method. This is the method Matlab's ode45 uses
        DOP78, //!< Dormand-Prince Runge-Kutta 7(8)th 13-12 stage method.
    };

    static inline Interval defaultInterval{ 0.0 * mp_units::non_si::day, 1.0 * mp_units::non_si::day }; //!< Default time interval for propagation

    /**
     * @brief Default constructor for the Integrator class.
     */
    Integrator() = default;

    /**
     * @brief Default destructor for the Integrator class.
     */
    ~Integrator() = default;

    /**
     * @brief Propagate the state of a vehicle over a specified time interval using the given equations of motion.
     *
     * @param epoch The initial epoch (start time) for the propagation.
     * @param interval The time interval over which to propagate the state.
     * @param eom The equations of motion to use for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     * @param store Whether to store the state history during propagation. Default is false.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory propagate(
        const Date& epoch,
        const Interval& interval,
        const EquationsOfMotion& eom,
        Vehicle& vehicle,
        bool store                = false,
        std::vector<Event> events = {}
    );

    /**
     * @brief Propagate the state of a vehicle from an initial time to a final time using the given equations of motion.
     *
     * @param epoch The initial epoch (start time) for the propagation.
     * @param timeInitial The initial time for propagation.
     * @param timeFinal The final time for propagation.
     * @param eom The equations of motion to use for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     * @param store Whether to store the state history during propagation. Default is false.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory propagate(
        const Date& epoch,
        const Time& timeInitial,
        const Time& timeFinal,
        const EquationsOfMotion& eom,
        Vehicle& vehicle,
        bool store                = false,
        std::vector<Event> events = {}
    );

    /**
     * @brief Set the absolute tolerance for the integrator.
     *
     * @param absTol The absolute tolerance value to set.
     */
    void set_abs_tol(Unitless absTol);

    /**
     * @brief Set the relative tolerance for the integrator.
     *
     * @param relTol The relative tolerance value to set.
     */
    void set_rel_tol(Unitless relTol);

    /**
     * @brief Set the maximum number of iterations for the integrator.
     *
     * @param itMax The maximum number of iterations to set.
     */
    void set_max_iter(int itMax);

    /**
     * @brief Switch the printing of integration details on or off.
     *
     * @param onOff Boolean flag to turn printing on (true) or off (false).
     */
    void switch_print(bool onOff);

    /**
     * @brief Switch the timer for measuring integration performance on or off.
     *
     * @param onOff Boolean flag to turn the timer on (true) or off (false).
     */
    void switch_timer(bool onOff);

    /**
     * @brief Set the step method for the integrator.
     *
     * @param stepMethod The name of the step method to use (e.g., "RK45", "RKF45", etc.).
     */
    void set_step_method(std::string stepMethod);

    /**
     * @brief Set the initial timestep for the integrator.
     *
     * @param dt0 The initial timestep to set.
     */
    void set_initial_timestep(Time dt0);

    /**
     * @brief Switch the fixed timestep mode on or off.
     *
     * @param onOff Boolean flag to turn fixed timestep mode on (true) or off (false).
     */
    void switch_fixed_timestep(bool onOff);

    /**
     * @brief Set the fixed timestep for the integrator.
     *
     * @param fixedTimeStep The fixed timestep to set.
     */
    void switch_fixed_timestep(bool onOff, Time fixedTimeStep);

    /**
     * @brief Set the fixed timestep for the integrator.
     *
     * @param fixedTimeStep The fixed timestep to set.
     */
    void set_timestep(Time fixedTimeStep);

    /**
     * @brief Get the current timestep used by the integrator.
     *
     * @return Time The current timestep.
     */
    int n_func_evals() { return functionEvaluations; }

  private:
    // Integrator constants
    const Unitless epsilon             = 0.8;    //!< Relative local step error tolerance usually 0.8 or 0.9.
    const Unitless minErrorCatch       = 2.0e-4; //!< If maximum error is less than this,
    const Unitless minErrorStepFactor  = 5.0;    //!< Increase step by this factor
    const Unitless minRelativeStepSize = 0.2;    //!< If the step size decreases by more than this factor, reduce the
                                                 //!< Relative step size to this value

    // Iteration variables
    unsigned long iteration             = 0;              //!< Outer loop iteration count
    unsigned long variableStepIteration = 0;              //!< Inner loop iteration count
    const unsigned long maxVariableStepIterations = 1000; //!< Max iterations for step sizing loop -> jj shouldn't get above ~10

    // Function evals
    int functionEvaluations = 0; //!< Number of function evaluations during integration

    // Number of states
    static const std::size_t maxStates = 10; //!< Maximum number of states in the orbital elements

    // Time variables
    bool forwardTime = true; //!< Direction of time propagation
    Time timeStepPrevious;   //!< Previous time step used in the integration

    // Error variables
    bool stepSuccess = false;  //!< Flag indicating if the last step was successful
    Unitless maxErrorPrevious; //!< Maximum error from the previous step

    // Butcher Tablaeu
    std::size_t nStages{}; //!< Number of stages in the Butcher tableau for the current step method
    static const std::size_t maxStages                       = 13; //!< Maximum number of stages in the Butcher tableau
    std::array<std::array<Unitless, maxStages>, maxStages> a = {}; //!< Coefficients for the Butcher tableau
    std::array<Unitless, maxStages> b                        = {}; //!< Weights for the Butcher tableau
    std::array<Unitless, maxStages> bhat                     = {}; //!< Modified weights for the Butcher tableau
    std::array<Unitless, maxStages> db = {}; //!< Derivative of the weights for the Butcher tableau
    std::array<Unitless, maxStages> c  = {}; //!< Nodes for the Butcher tableau

    // ith order steps
    std::array<OrbitalElements, maxStages> kMatrix = {}; //!< Matrix of intermediate steps for the Runge-Kutta method
    OrbitalElements statePlusKi;                         //!< State vector plus the ith order step
    OrbitalElementPartials YFinalPrevious;               //!< Previous final state vector for the Runge-Kutta method

    // Clock variables
    clock_t startClock{}; //!< Start time for the timer
    clock_t endClock{};   //!< End time for the timer

    // Error Messages
    const std::string underflowErrorMessage = "Integration Error: Stepsize underflow. \n\n"; //!< Error message for stepsize underflow
    const std::string innerLoopStepOverflowErrorMessage =
        "Integration Error: Max iterations exceeded. Unable to find stepsize within tolerance. \n\n"; //!< Error message for inner loop step overflow
    const std::string outerLoopStepOverflowErrorMessage =
        "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try again. \n\n"; //!< Error message for outer loop step overflow
    const std::string crashMessage = "Note: Object crashed into central body. \n\n"; //!< Error message for crash into central body

    // Print variables
    int checkDay = 0; //!< Day counter for printing state information

    // Tolerances
    Unitless absoluteTolerance = 1.0e-13; //!< Absolute tolerance for the integrator
    Unitless relativeTolerance = 1.0e-13; //!< Relative tolerance for the integrator

    // Initial step size
    Time timeStepInitial = 300.0 * mp_units::si::unit_symbols::s; //!< Initial time step for the integrator

    // Iteration variables - absurdly high so it doesn't interfere with integration
    unsigned long iterMax = 1e8; //!< Maximum number of iterations for the integrator

    // Run options
    bool printOn = false; //!< Flag to control printing of integration details
    bool timerOn = false; //!< Flag to control timing of integration performance

    odeStepper stepMethod = DOP45; //!< Step method to use for the integration (default is Dormand-Prince RK4(5))

    // Fake fixed step
    bool useFixedStep  = false;                               //!< Flag to indicate if a fixed step size should be used
    Time fixedTimeStep = 1.0 * mp_units::si::unit_symbols::s; //!< Fixed time step size to use if fixed step is enabled

    // Events
    EventDetector eventDetector;

    /**
     * @brief Find the state derivative at a given time using the equations of motion.
     *
     * @param time The time at which to evaluate the state derivative.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the evaluation.
     * @param vehicle The vehicle whose state is being evaluated.
     * @return OrbitalElementPartials The derivatives of the orbital elements with respect to time.
     */
    OrbitalElementPartials
        find_state_derivative(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Set up the stepper method based on the selected step method.
     */
    void setup_stepper();

    /**
     * @brief Perform a single step of the integration using the selected Runge-Kutta method.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     */
    void try_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Check the error of the current step and adjust the time step accordingly.
     *
     * @param maxError The maximum allowable error for the step.
     * @param stateNew The new state after the step.
     * @param stateError The error in the state after the step.
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     */
    void check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state);

    /**
     * @brief Print the current iteration details including time, state, and performance metrics.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param timeFinal The final time for the integration.
     * @param stateInitial The initial state of the vehicle at the start of the integration.
     */
    void print_iteration(const Time& time, const OrbitalElements& state, const Time& timeFinal, const OrbitalElements& stateInitial);

    /**
     * @brief Print the performance metrics of the integration including total time, function evaluations, and iterations.
     */
    void print_performance() const;

    /**
     * @brief Start the timer for measuring integration performance.
     */
    void startTimer()
    {
        if (timerOn) { startClock = clock(); }
    };

    /**
     * @brief End the timer for measuring integration performance.
     */
    void endTimer()
    {
        if (timerOn) { endClock = clock(); }
    }

    /**
     * @brief Check for events during the integration, such as collisions or specific conditions.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     */
    bool check_event(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);
};

} // namespace astro
} // namespace astrea