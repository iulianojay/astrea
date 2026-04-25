/**
 * @file Integrator.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Numerical integrator for orbital mechanics propagation
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <optional>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/Schedule.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Interval.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

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

struct IntegratorSettings {
    Unitless absTol       = 1.0e-13;                              //!< Absolute tolerance for the integrator
    Unitless relTol       = 1.0e-13;                              //!< Relative tolerance for the integrator
    int itMax             = 10000;                                //!< Maximum number of iterations for the integrator
    StepMethod stepMethod = StepMethod::RKF78;                    //!< Step method for the integrator
    Time initialTimeStep  = 1.0 * mp_units::si::unit_symbols::s;  //!< Initial timestep for the integrator
    bool useFixedStep     = false;                                //!< Flag to indicate whether to use a fixed timestep
    Time fixedTimeStep    = 30.0 * mp_units::si::unit_symbols::s; //!< Fixed timestep to use if useFixedStep is true
};

/**
 * @brief Integrator class for numerical propagation of orbital mechanics problems.
 *
 * This class implements various Runge-Kutta methods for integrating the equations of motion
 * of a vehicle in space. It allows for variable step sizes, error control, and event handling.
 */
class Integrator {

  public:
    /**
     * @brief Default constructor for the Integrator class.
     */
    Integrator() = default;

    /**
     * @brief Constructor for the Integrator class that takes an IntegratorSettings struct.
     *
     * @param settings The settings to configure the integrator.
     */
    Integrator(const IntegratorSettings& settings) :
        _ABS_TOL(settings.absTol),
        _REL_TOL(settings.relTol),
        _MAX_ITER(settings.itMax),
        _timeStepInitial(settings.initialTimeStep),
        _stepMethod(settings.stepMethod),
        _useFixedStep(settings.useFixedStep),
        _fixedTimeStep(settings.fixedTimeStep)
    {
    }

    /**
     * @brief Default destructor for the Integrator class.
     */
    ~Integrator() = default;

    /**
     * @brief Propagate the state of a vehicle over a specified time interval using the given equations of motion.
     *
     * @param state0 The initial state from which to start propagation.
     * @param propTime The total propagation time after the initial state epoch.
     * @param vehicle The vehicle whose state is to be propagated.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory propagate(const State& state0, const Time& propTime, Vehicle vehicle);

    /**
     * @brief Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion.
     *
     * @param state0 The initial state from which to start propagation.
     * @param endEpoch The final epoch (end time) for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory propagate(const State& state0, const Date& endEpoch, Vehicle vehicle);

    /**
     * @brief Propagate the state of a vehicle over a specified time interval without storing the state history.
     *
     * @param state0 The initial state from which to start propagation.
     * @param propTime The total propagation time after the initial state epoch.
     * @param vehicle The vehicle whose state is to be propagated.
     */
    void propagate_no_storage(const State& state0, const Time& propTime, Vehicle vehicle);

    /**
     * @brief Propagate the state of a vehicle from its current epoch to a specified end epoch without storing the state history.
     *
     * @param state0 The initial state from which to start propagation.
     * @param endEpoch The final epoch (end time) for the propagation.
     * @param vehicle The vehicle whose state is to be propagated.
     */
    void propagate_no_storage(const State& state0, const Date& endEpoch, Vehicle vehicle);

    /**
     * @brief Set the schedule of events to be tracked during propagation.
     *
     * @param schedule The Schedule object containing the events to be tracked.
     */
    void set_schedule(const Schedule& schedule);

    /**
     * @brief Clear the schedule of events, removing all scheduled events from the integrator.
     */
    void clear();

    /**
     * @brief Add an event to the integrator's event detector.
     *
     * @param event The Event object to be added to the integrator's event detector.
     */
    void add_event(const Event& event);

    /**
     * @brief Add multiple events to the integrator's event detector.
     *
     * @param events A vector of Event objects to be added to the integrator's event detector.
     */
    void add_events(const std::vector<Event>& events);

    /**
     * @brief Clear all events from the integrator's event detector.
     */
    void clear_events();

    /**
     * @brief Set the equations of motion to be used for propagation.
     *
     * @param eom The EquationsOfMotion object to be used for propagation.
     */
    template <typename T>
        requires(std::derived_from<T, EquationsOfMotion>)
    void set_equations_of_motion(const T& eom)
    {
        _eom = std::make_unique<T>(eom);
    }

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
    // Tolerances
    Unitless _ABS_TOL = 1.0e-13; //!< Absolute tolerance for the integrator
    Unitless _REL_TOL = 1.0e-13; //!< Relative tolerance for the integrator

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
    Date _epoch0;           //!< Initial epoch for the propagation

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
    std::array<State, _MAX_STAGES> _kMatrix = {}; //!< Matrix of intermediate steps for the Runge-Kutta method
    State _statePlusKi;                           //!< State vector plus the ith order step
    StatePartial _YFinalPrevious;                 //!< Previous final state vector for the Dormand-Prince method

    // Initial step size
    Time _timeStepInitial = 60.0 * astrea::detail::time_unit; //!< Initial time step for the integrator

    // Run options
    bool _printOn = false; //!< Flag to control printing of integration details
    bool _store   = true;  //!< Flag to control whether to store the state history during propagation

    StepMethod _stepMethod = StepMethod::DOP45; //!< Step method to use for the integration (default is Dormand-Prince RK4(5))
    std::unique_ptr<EquationsOfMotion> _eom; //!< Equations of motion to use for the integration

    // Fixed step
    bool _useFixedStep  = false;                           //!< Flag to indicate if a fixed step size should be used
    Time _fixedTimeStep = 1.0 * astrea::detail::time_unit; //!< Fixed time step size to use if fixed step is enabled

    // Events
    EventDetector _eventDetector;
    Schedule _schedule;

    /**
     * @brief Propagate the state of a vehicle from its current epoch to a specified end epoch using the given equations of motion.
     *
     * @param state0 The initial state from which to start propagation.
     * @param propTime The propagation time interval.
     * @param vehicle The vehicle whose state is to be propagated.
     * @return StateHistory The history of the vehicle's state over the propagated interval.
     */
    StateHistory propagate_impl(const State& state0, const Time& propTime, Vehicle vehicle);

    /**
     * @brief Find the state derivative at a given time using the equations of motion.
     *
     * @param time The time at which to evaluate the state derivative.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The vehicle whose state is being evaluated.
     * @return StatePartial The derivatives of the orbital elements with respect to time.
     */
    StatePartial find_state_derivative(const Time& time, const State& state, Vehicle& vehicle);

    /**
     * @brief Set up the main integration loop
     */
    void setup();

    /**
     * @brief Set up the stepper method based on the selected step method.
     */
    void setup_butcher_tableau();

    /**
     * @brief Perform a single step of the integration using the selected Runge-Kutta method.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The vehicle whose state is being integrated.
     * @return bool True if the step was successful, false otherwise.
     */
    bool try_step(Time& time, Time& timeStep, State& state, Vehicle& vehicle);

    /**
     * @brief Find the maximum error between the new and error states.
     *
     * @param stateNew The new state after the step.
     * @param stateError The error in the state after the step.
     * @return Unitless The maximum error found.
     */
    Unitless find_max_error(const State& stateNew, const State& stateError) const;

    /**
     * @brief Take a fixed step in the integration.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The vehicle whose state is being integrated.
     */
    void take_fixed_step(Time& time, Time& timeStep, State& state, Vehicle& vehicle);

    /**
     * @brief Take a step in the integration.
     *
     * @param time The current time in the integration.
     * @param timeStep The current time step to use for the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The vehicle whose state is being integrated.
     * @return std::pair<State, State> The new state and the error state after the step.
     */
    std::pair<State, State> take_step(const Time& time, const Time& timeStep, const State& state, Vehicle& vehicle);

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
    bool check_error(const Unitless& maxError, const State& stateNew, const State& stateError, Time& time, Time& timeStep, State& state);

    /**
     * @brief Get the relative step size based on the maximum error.
     *
     * @param maxError The maximum error from the current step.
     * @return Unitless The relative step size to adjust the time step.
     */
    Unitless get_relative_step_size(const Unitless& maxError) const;

    /**
     * @brief Store the most recent function evaluation results for Dormand-Prince methods.
     *
     * @param timeStep The current time step used for the integration.
     */
    void store_final_func_eval(const Time& timeStep);

    /**
     * @brief Check for events during the integration, such as collisions or specific conditions.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The vehicle whose state is being integrated.
     */
    bool check_event(const Time& time, State& state, Vehicle& vehicle);

    /**
     * @brief Validate the current state and time to ensure they are not NaN or infinite.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @return true If the state and time are valid.
     * @return false If the state or time are invalid (NaN or infinite).
     */
    bool validate_state_and_time(const Time& time, const State& state) const;
};

} // namespace astro
} // namespace astrea