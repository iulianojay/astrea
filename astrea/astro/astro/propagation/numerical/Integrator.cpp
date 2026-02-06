/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/numerical/Integrator.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

#include <math/math.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/numerical/butcher_tableau.hpp> // RK Butcher Tableau
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/orbital_elements.hpp>
#include <astro/time/Interval.hpp>
#include <astro/types/typedefs.hpp>

using namespace mp_units;
using mp_units::si::unit_symbols::ms;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

StateHistory
    Integrator::propagate(const State& state0, const Date& endEpoch, const EquationsOfMotion& eom, Vehicle vehicle, bool store, std::vector<Event> events)
{
    const Time propTime = endEpoch - state0.get_epoch();
    return propagate(state0, propTime, eom, vehicle, store, events);
}

StateHistory
    Integrator::propagate(const State& state0, const Time& propTime, const EquationsOfMotion& eom, Vehicle vehicle, bool store, std::vector<Event> events)
{
    // Time
    Time time     = 0.0 * s;
    Time timeStep = (_useFixedStep) ? _fixedTimeStep : _timeStepInitial;
    if (timeStep > propTime) { timeStep = propTime; }

    const bool forwardTime = (propTime > 0.0 * s);
    if (!forwardTime) { timeStep = -timeStep; }

    // State
    _epoch0     = state0.get_epoch();
    State state = state0.convert_to_set(eom.get_expected_set_id());

    // Setup
    setup(events);

    // Fruit Loop
    StateHistory stateHistory;
    if (store) { stateHistory.insert(state); }
    while (_iteration < _MAX_ITER) {

        // Check for event
        const bool terminalEvent = check_event(time, state, vehicle);
        if (terminalEvent) {
            print_iteration(time, state, propTime, state0);

            std::cout << "Warning: Terminal conditions detected.";
            return stateHistory;
        }

        // Make sure state and time are valid
        if (!validate_state_and_time(time, state)) {
            std::cout << "Integration Error: Invalid state or time (NaN or Inf). \n\n";
            return stateHistory;
        }

        // Step
        if (_useFixedStep) {
            // Step without error correction
            // I think an interesting choice would allow the user to use the fixed timestep but the
            // Integrator would use variable stepper to each fixed timestep. This would give the
            // desired output with the ensured accuracy of the variable stepper
            take_fixed_step(time, timeStep, state, eom, vehicle);
        }
        else { // Variable time step
            // Loop to find step size that meets tolerance
            _variableStepIteration = 0;
            while (_variableStepIteration < _MAX_VAR_STEP_ITER) {
                // Try to step
                const bool stepSuccess = try_step(time, timeStep, state, eom, vehicle);

                // Catch underflow
                if (time + timeStep == time) {
                    std::cout << "Integration Error: Stepsize underflow. \n\n";
                    return stateHistory;
                }

                // Break if step succeeded
                if (stepSuccess) { break; }

                // Inner Loop Iteration
                ++_variableStepIteration;
            }

            // Exceeded max inner loop iterations
            if (_variableStepIteration >= _MAX_VAR_STEP_ITER) {
                std::cout
                    << "Integration Error: Max iterations exceeded. Unable to find stepsize within tolerance. \n\n";
                return stateHistory;
            }
        }

        // Successful event
        if (store) { stateHistory.insert(state); }

        // Ensure last step goes to exact final time
        if ((forwardTime && time + timeStep > propTime && time < propTime) ||
            (!forwardTime && time + timeStep < propTime && time > propTime)) {
            timeStep = propTime - time;
        }
        // Break if final time is reached
        else if (time == propTime) {
            break;
        }

        // Print time and state
        print_iteration(time, state, propTime, state0);

        // Step iteration
        ++_iteration;
    }

    // Store last state if not already stored
    if (!store) { stateHistory.insert(state); }

    // Store event times
    if (!events.empty()) { stateHistory.set_event_times(_eventDetector.get_event_times(_epoch0)); }

    teardown();

    return stateHistory;
}

void Integrator::setup(const std::vector<Event>& events)
{
    // Set events
    _eventDetector.set_events(events);

    // Ensure counts restart
    _functionEvaluations = 0;
    _iteration           = 0;

    // Setup stepper
    setup_butcher_tableau();

    // Start timer
    startTimer();
}

void Integrator::teardown()
{
    // Stop timer
    endTimer();

    // Performance
    print_performance();

    // Exceeded max outer loop iterations
    if (_iteration >= _MAX_ITER) {
        std::cout << "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try "
                     "again. \n\n";
    }
}


void Integrator::setup_butcher_tableau()
{
    // Get Butcher Tableau
    switch (_stepMethod) {

        case (StepMethod::RK45): {

            _nStages = RK45::nStages;
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = RK45::a[ii][jj];
                }
                _b[ii]    = RK45::b[ii];
                _bhat[ii] = RK45::bhat[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = RK45::c[ii];
            }
            break;
        }
        case (StepMethod::RKF45): {

            _nStages = RKF45::nStages;
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = RKF45::a[ii][jj];
                }
                _b[ii]    = RKF45::b[ii];
                _bhat[ii] = RKF45::bhat[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = RKF45::c[ii];
            }
            break;
        }
        case (StepMethod::RKF78): {

            _nStages = RKF78::nStages;
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = RKF78::a[ii][jj];
                }
                _b[ii]    = RKF78::b[ii];
                _bhat[ii] = RKF78::bhat[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = RKF78::c[ii];
            }
            break;
        }
        case (StepMethod::DOP45): {

            _nStages = DOP45::nStages;
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = DOP45::a[ii][jj];
                }
                _b[ii]    = DOP45::b[ii];
                _bhat[ii] = DOP45::bhat[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = DOP45::c[ii];
            }
            break;
        }
        case (StepMethod::DOP78): {

            _nStages = DOP78::nStages;
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = DOP78::a[ii][jj];
                }
                _b[ii]    = DOP78::b[ii];
                _bhat[ii] = DOP78::bhat[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = DOP78::c[ii];
            }
            break;
        }
        default:
            throw std::invalid_argument("Integration Error: Stepping method not found. Options are {RK45, RKF45, "
                                        "RKF78, DOP45, DOP78}.");
    }
}

StatePartial Integrator::find_state_derivative(const Time& time, const State& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Count fevals
    ++_functionEvaluations;

    // Ask eom object to evaluate
    State stateTemp = state;
    stateTemp.set_epoch(_epoch0 + time);

    const OrbitalElementPartials orbitalElementPartials = eom(stateTemp, vehicle);

    return { orbitalElementPartials, stateTemp.get_epoch(), state.get_system() };
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
std::pair<State, State>
    Integrator::take_step(const Time& time, const Time& timeStep, const State& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Find k values: ki = timeStep*find_state_derivative(time + c[i]*stepSize, state + sum_(j=0)^(i-1) k_j a[i][j])
    for (std::size_t iStage = 0; iStage < _nStages; ++iStage) {
        // Calculate intermediate state for current stage (except stage 0)
        _statePlusKi = state;
        if (iStage > 0) {
            for (std::size_t jStage = 0; jStage < iStage; ++jStage) {
                _statePlusKi += _kMatrix[jStage] * _a[iStage][jStage];
            }
        }

        // Find derivative at the intermediate state
        StatePartial partial;
        if (iStage == 0) {
            if (_stepMethod == StepMethod::RK45 || _stepMethod == StepMethod::RKF45 || _stepMethod == StepMethod::RKF78) {
                partial = find_state_derivative(time, _statePlusKi, eom, vehicle);
            }
            else if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
                if (_iteration == 0) { partial = find_state_derivative(time, _statePlusKi, eom, vehicle); }
                else {
                    partial = _YFinalPrevious;
                }
            }
        }
        else {
            partial = find_state_derivative(time + _c[iStage] * timeStep, _statePlusKi, eom, vehicle);
        }

        // Store k value
        _kMatrix[iStage] = partial * timeStep;
    }

    // Get new state and state error
    State stateNew   = state + _kMatrix[0] * _b[0];
    State stateError = _kMatrix[0] * _db[0];
    for (std::size_t iStage = 1; iStage < _nStages; ++iStage) {
        stateNew += _kMatrix[iStage] * _b[iStage];
        stateError += _kMatrix[iStage] * _db[iStage];
    }

    return { stateNew, stateError };
}

Unitless Integrator::find_max_error(const State& stateNew, const State& stateError) const
{
    using mp_units::abs;
    using mp_units::isinf;
    using mp_units::isnan;

    // Find max error from step
    Unitless maxError           = 0.0 * astrea::detail::unitless;
    const auto stateErrorScaled = stateError.force_to_vector();
    const auto stateNewScaled   = stateNew.force_to_vector();
    for (std::size_t ii = 0; ii < stateErrorScaled.size(); ++ii) {
        // Error
        const auto err = abs(stateErrorScaled[ii]) / (_ABS_TOL + abs(stateNewScaled[ii]) * _REL_TOL);
        if (err > maxError) { maxError = err; }

        // Catch NaN/Inf values and unreasonably large error estimates
        if (isinf(stateNewScaled[ii]) || isnan(stateNewScaled[ii]) || isinf(stateErrorScaled[ii]) ||
            isnan(stateErrorScaled[ii]) || abs(stateErrorScaled[ii]) > 1.0e6 * astrea::detail::unitless) {
            /* 1e6 is arbitrily chosen but is a safe bet for orbital calculations.
               If the step is legitimate, but just very large, this will just force
               it to lower the step slightly and try again without killing the run */
            maxError = 2.0 * astrea::detail::unitless; // Force step failure
        }
    }

    return maxError;
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
bool Integrator::try_step(Time& time, Time& timeStep, State& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Take step
    const auto [stateNew, stateError] = take_step(time, timeStep, state, eom, vehicle);

    // Find max error
    const auto maxError = find_max_error(stateNew, stateError);

    // Check error of step
    return check_error(maxError, stateNew, stateError, time, timeStep, state);
}


void Integrator::take_fixed_step(Time& time, Time& timeStep, State& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Take step
    const auto [stateNew, stateError] = take_step(time, timeStep, state, eom, vehicle);

    time += timeStep;
    state = stateNew;
    state.set_epoch(_epoch0 + time);

    // Store final function eval for Dormand-Prince methods
    store_final_func_eval(timeStep);
}

void Integrator::store_final_func_eval(const Time& timeStep)
{
    // Store final function eval for Dormand-Prince methods
    if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
        _YFinalPrevious = _kMatrix[_nStages - 1] / timeStep;
    }
}

Unitless Integrator::get_relative_step_size(const Unitless& maxError) const
{
    // stupid function for stupid people

    // Don't scale if error is zero
    if (maxError == 0.0 * astrea::detail::unitless || (_iteration > 0 && _maxErrorPrevious == 0.0 * astrea::detail::unitless)) {
        return 1.0 * astrea::detail::unitless;
    }

    // Ignore pi controller on first iteration or if error is large
    const bool ignorePiController = (_iteration == 0 || maxError > 1.0 * astrea::detail::unitless);
    const bool isFourthOrderMethod =
        (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::RKF45 || _stepMethod == StepMethod::RK45);

    // Get controller value
    Unitless relativeTimeStep{};
    if (isFourthOrderMethod) {
        relativeTimeStep = pow<1, 5>(_EPSILON / maxError);
        if (!ignorePiController) { relativeTimeStep *= pow<7, 50>(maxError / _maxErrorPrevious); }
    }
    else {
        relativeTimeStep = pow<1, 8>(_EPSILON / maxError);
        if (!ignorePiController) { relativeTimeStep *= pow<7, 80>(maxError / _maxErrorPrevious); }
    }
    return relativeTimeStep;
}

bool Integrator::check_error(const Unitless& maxError, const State& stateNew, const State& stateError, Time& time, Time& timeStep, State& state)
{
    const Unitless relativeStepSize = get_relative_step_size(maxError);
    if (maxError <= 1.0) { // Step succeeded
        // Step
        time += timeStep;
        state = stateNew;
        state.set_epoch(_epoch0 + time);

        store_final_func_eval(timeStep);

        // Store step and error
        _timeStepPrevious = timeStep;
        _maxErrorPrevious = maxError;

        // Get new step after stepping time
        if (_iteration == 0) {
            timeStep *= (maxError < _MIN_ERROR_TO_CATCH) ? _MIN_ERROR_STEP_FACTOR : relativeStepSize;
        }
        else {
            // New step size
            timeStep *= relativeStepSize;
        }

        // Go to next step
        return true;
    }

    // Error is too large. Truncate stepsize
    // Keep step from getting too small too fast
    timeStep *= (relativeStepSize < _MIN_REL_STEP_SIZE) ? _MIN_REL_STEP_SIZE : relativeStepSize;

    return false;
}


void Integrator::print_iteration(const Time& time, const State& state, const Time& endTime, const State& state0)
{
    // This message is not lined up with iteration since ti and statei are advanced before this but it's okay
    if (_printOn) {
        if (_iteration == 0) {
            std::cout << "Run Conditions:" << std::endl << std::endl;
            std::cout << "Initial Time = " << 0.0 << std::endl;
            std::cout << "Final Time =  " << endTime << std::endl;
            std::cout << "Initial State = " << state0 << std::endl;
            std::cout << "Integration Tolerance: " << _REL_TOL << std::endl << std::endl;
            std::cout << "Run:" << std::endl << std::endl;
        }
        else {
            std::cout << "Iteration: " << _iteration + 1 << std::endl;
            std::cout << "time = " << time << std::endl;
            std::cout << "state = " << state << std::endl << std::endl;
        }
        if (time == endTime) { std::cout << "Run Completed." << std::endl << std::endl; }
    }
}

void Integrator::print_performance() const
{
    if (_printOn) {
        std::cout << "Number of Steps:                " << _iteration << " iter" << std::endl;
        std::cout << "Number of Function Evaluations: " << _functionEvaluations << " fval" << std::endl;

        double runtime{};
        if (_timerOn) {
            runtime = ((double)_endClock - (double)_startClock) / ((double)CLOCKS_PER_SEC);
            std::cout << "Runtime:                        " << runtime << " s" << std::endl;
        }

        std::cout << "\nAverage Function Evaluations per Step:   " << (double)_functionEvaluations / (double)_iteration
                  << " fval/iter" << std::endl;

        if (_timerOn) {
            std::cout << "Average Runtime per Step:                " << runtime / (double)_iteration << " s/iter" << std::endl;
            std::cout << "Average Runtime per Function Evaluation: " << runtime / (double)_functionEvaluations
                      << " s/fval" << std::endl
                      << std::endl;
        }
    }
}

bool Integrator::check_event(const Time& time, State& state, Vehicle& vehicle)
{
    return _eventDetector.detect_events(time, state, vehicle);
}

bool Integrator::validate_state_and_time(const Time& time, const State& state) const
{
    if (isinf(abs(time)) || isnan(abs(time))) { return false; }
    for (const auto& x : state.force_to_vector()) {
        if (isinf(abs(x)) || isnan(abs(x))) { return false; }
    }
    return true;
}

void Integrator::startTimer()
{
    if (_timerOn) { _startClock = clock(); }
}

void Integrator::endTimer()
{
    if (_timerOn) { _endClock = clock(); }
}


// Integrator Properties
void Integrator::set_abs_tol(const Unitless& absTol) { _ABS_TOL = absTol; }
void Integrator::set_rel_tol(const Unitless& relTol) { _REL_TOL = relTol; }
void Integrator::set_max_iter(const int& itMax) { _MAX_ITER = itMax; }

void Integrator::switch_print(const bool& onOff) { _printOn = onOff; }
void Integrator::switch_timer(const bool& onOff) { _timerOn = onOff; }

void Integrator::set_initial_timestep(const Time& dt0) { _timeStepInitial = dt0; }
void Integrator::switch_fixed_timestep(const bool& onOff) { _useFixedStep = onOff; }
void Integrator::switch_fixed_timestep(const bool& onOff, const Time& fixedTimeStep)
{
    _useFixedStep  = onOff;
    _fixedTimeStep = fixedTimeStep;
}
void Integrator::set_timestep(const Time& fixedTimeStep) { _fixedTimeStep = fixedTimeStep; }

void Integrator::set_step_method(const StepMethod& stepMethod) { _stepMethod = stepMethod; }

} // namespace astro
} // namespace astrea