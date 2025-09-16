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

#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/time/Interval.hpp>
#include <astro/types/typedefs.hpp>

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
    enum class StepMethod : EnumType {
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
     * @brief Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion.
     *
     * @param endEpoch The final epoch (end time) for the propagation.
     * @param eom The equations of motion to use for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     * @param store Whether to store the state history during propagation. Default is false.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory
        propagate(const Date& endEpoch, const EquationsOfMotion& eom, Vehicle& vehicle, bool store = false, std::vector<Event> events = {});

    /**
     * @brief Propagate the state of a vehicle from its current epoch for a specified time using the given equations of motion.
     *
     * @param propTime Total propagation time after vehicle epoch.
     * @param eom The equations of motion to use for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     * @param store Whether to store the state history during propagation. Default is false.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory
        propagate(const Time& propTime, const EquationsOfMotion& eom, Vehicle& vehicle, bool store = false, std::vector<Event> events = {});

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
    void set_abs_tol(const Unitless& absTol);

    /**
     * @brief Set the relative tolerance for the integrator.
     *
     * @param relTol The relative tolerance value to set.
     */
    void set_rel_tol(const Unitless& relTol);

    /**
     * @brief Set the maximum number of iterations for the integrator.
     *
     * @param itMax The maximum number of iterations to set.
     */
    void set_max_iter(const int& itMax);

    /**
     * @brief Switch the printing of integration details on or off.
     *
     * @param onOff Boolean flag to turn printing on (true) or off (false).
     */
    void switch_print(const bool& onOff);

    /**
     * @brief Switch the timer for measuring integration performance on or off.
     *
     * @param onOff Boolean flag to turn the timer on (true) or off (false).
     */
    void switch_timer(const bool& onOff);

    /**
     * @brief Set the step method for the integrator.
     *
     * @param stepMethod The name of the step method to use (e.g., "RK45", "RKF45", etc.).
     */
    void set_step_method(const StepMethod& stepMethod);

    /**
     * @brief Set the initial timestep for the integrator.
     *
     * @param dt0 The initial timestep to set.
     */
    void set_initial_timestep(const Time& dt0);

    /**
     * @brief Switch the fixed timestep mode on or off.
     *
     * @param onOff Boolean flag to turn fixed timestep mode on (true) or off (false).
     */
    void switch_fixed_timestep(const bool& onOff);

    /**
     * @brief Set the fixed timestep for the integrator.
     *
     * @param fixedTimeStep The fixed timestep to set.
     */
    void switch_fixed_timestep(const bool& onOff, const Time& fixedTimeStep);

    /**
     * @brief Set the fixed timestep for the integrator.
     *
     * @param fixedTimeStep The fixed timestep to set.
     */
    void set_timestep(const Time& fixedTimeStep);

    /**
     * @brief Get the current timestep used by the integrator.
     *
     * @return Time The current timestep.
     */
    int n_func_evals() { return _functionEvaluations; }

  private:
    // Integrator constants
    const Unitless _EPSILON               = 0.8;    //!< Relative local step error tolerance usually 0.8 or 0.9.
    const Unitless _MIN_ERROR_TO_CATCH    = 2.0e-4; //!< If maximum error is less than this,
    const Unitless _MIN_ERROR_STEP_FACTOR = 5.0;    //!< Increase step by this factor
    const Unitless _MIN_REL_STEP_SIZE     = 0.2;    //!< If the step size decreases by more than this factor, reduce the
                                                    //!< Relative step size to this value

    // Iteration variables
    unsigned long _iteration          = 0;   //!< Outer loop iteration count
    unsigned _variableStepIteration   = 0;   //!< Inner loop iteration count
    unsigned long _MAX_ITER           = 1e8; //!< Maximum number of iterations for the integrator
    const unsigned _MAX_VAR_STEP_ITER = 1e3; //!< Max iterations for step sizing loop -> jj shouldn't get above ~10

    // Function evals
    int _functionEvaluations = 0; //!< Number of function evaluations during integration

    // Time variables
    Time _timeStepPrevious; //!< Previous time step used in the integration

    // Error variables
    Unitless _maxErrorPrevious; //!< Maximum error from the previous step

    // Butcher Tableau
    std::size_t _nStages{};                    //!< Number of stages in the Butcher tableau for the current step method
    static const std::size_t _MAX_STAGES = 13; //!< Maximum number of stages in the Butcher tableau
    std::array<std::array<Unitless, _MAX_STAGES>, _MAX_STAGES> _a = {}; //!< Coefficients for the Butcher tableau
    std::array<Unitless, _MAX_STAGES> _b                          = {}; //!< Weights for the Butcher tableau
    std::array<Unitless, _MAX_STAGES> _bhat                       = {}; //!< Modified weights for the Butcher tableau
    std::array<Unitless, _MAX_STAGES> _db = {}; //!< Derivative of the weights for the Butcher tableau
    std::array<Unitless, _MAX_STAGES> _c  = {}; //!< Nodes for the Butcher tableau

    // ith order steps
    std::array<OrbitalElements, _MAX_STAGES> _kMatrix = {}; //!< Matrix of intermediate steps for the Runge-Kutta method
    OrbitalElements _statePlusKi;                           //!< State vector plus the ith order step
    OrbitalElementPartials _YFinalPrevious;                 //!< Previous final state vector for the Runge-Kutta method

    // Clock variables
    clock_t _startClock{}; //!< Start time for the timer
    clock_t _endClock{};   //!< End time for the timer

    // Tolerances
    Unitless _ABS_TOL = 1.0e-13; //!< Absolute tolerance for the integrator
    Unitless _REL_TOL = 1.0e-13; //!< Relative tolerance for the integrator

    // Initial step size
    Time _timeStepInitial = 300.0 * mp_units::si::unit_symbols::s; //!< Initial time step for the integrator

    // Run options
    bool _printOn = false; //!< Flag to control printing of integration details
    bool _timerOn = false; //!< Flag to control timing of integration performance

    StepMethod _stepMethod = StepMethod::DOP45; //!< Step method to use for the integration (default is Dormand-Prince RK4(5))

    // Fake fixed step
    bool _useFixedStep  = false;                               //!< Flag to indicate if a fixed step size should be used
    Time _fixedTimeStep = 1.0 * mp_units::si::unit_symbols::s; //!< Fixed time step size to use if fixed step is enabled

    // Events
    EventDetector _eventDetector;

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
     * @brief Set up the main integration loop
     *
     * @param events The events to be tracked during propagation.
     */
    void setup(const std::vector<Event>& events);

    /**
     * @brief Teardown after the main integration loop
     */
    void teardown();

    /**
     * @brief Set up the stepper method based on the selected step method.
     */
    void setup_butcher_tableau();

    /**
     * @brief Get the initial state of the vehicle at the specified epoch.
     *
     * @param epoch The epoch at which to get the initial state.
     * @param eom The equations of motion to use for the evaluation.
     * @param state0 The initial state of the vehicle before propagation.
     * @param vehicle The vehicle whose state is being evaluated.
     * @param events The events to be tracked during propagation.
     * @return OrbitalElements The state of the vehicle at the specified epoch.
     */
    OrbitalElements get_initial_state(const Date& epoch, const EquationsOfMotion& eom, Vehicle& vehicle, std::vector<Event> events);

    /**
     * @brief Perform a single step of the integration using the selected Runge-Kutta method.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     * @return bool True if the step was successful, false otherwise.
     */
    bool try_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Find the maximum error between the new and error states.
     *
     * @param stateNew The new state after the step.
     * @param stateError The error in the state after the step.
     * @return Unitless The maximum error found.
     */
    Unitless find_max_error(const OrbitalElements& stateNew, const OrbitalElements& stateError) const;

    /**
     * @brief Take a fixed step in the integration.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     */
    void take_fixed_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Take a step in the integration.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     * @return std::pair<OrbitalElements, OrbitalElements> The new state and the error state after the step.
     */
    std::pair<OrbitalElements, OrbitalElements>
        take_step(const Time& time, const Time& timeStep, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Check the error of the current step and adjust the time step accordingly.
     *
     * @param maxError The maximum allowable error for the step.
     * @param stateNew The new state after the step.
     * @param stateError The error in the state after the step.
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @return bool True if the step was accepted, false if it needs to be retried with a smaller step size.
     */
    bool check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state);

    /**
     * @brief Store the most recent function evaluation results for Dormand-Prince methods.
     *
     * @param timeStep The current time step used for the integration.
     */
    void store_final_func_eval(const Time& timeStep);

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
    void startTimer();

    /**
     * @brief End the timer for measuring integration performance.
     */
    void endTimer();

    /**
     * @brief Check for events during the integration, such as collisions or specific conditions.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param eom The equations of motion to use for the integration.
     * @param vehicle The vehicle whose state is being integrated.
     */
    bool check_event(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle);

    /**
     * @brief Validate the current state and time to ensure they are not NaN or infinite.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @return true If the state and time are valid.
     * @return false If the state or time are invalid (NaN or infinite).
     */
    bool validate_state_and_time(const Time& time, const OrbitalElements& state) const;
};

} // namespace astro
} // namespace astrea