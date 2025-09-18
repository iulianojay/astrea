#include <astro/propagation/numerical/Integrator.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

// mp-units
#include <mp-units/math.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/time/Interval.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/propagation/numerical/butcher_tableau.hpp> // RK Butcher Tableau
#include <astro/state/orbital_elements/orbital_elements.hpp>

using namespace mp_units;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

Integrator::Integrator(
    const Unitless& absTol,
    const Unitless& relTol,
    const StepMethod& stepMethod,
    const Time& initialTimeStep,
    const int& maxIterations,
    const bool& useFixedTimeStep,
    const Time& fixedTimeStep,
    const std::vector<Event>& events
) :
    _absTol(absTol),
    _relTol(relTol),
    _stepMethod(stepMethod),
    _timeStepInitial(initialTimeStep),
    _maxIterations(maxIterations),
    _useFixedStep(useFixedTimeStep),
    _fixedTimeStep(fixedTimeStep),
    _eventDetector(events)
{
}

StateHistory Integrator::propagate(const Date& epoch, const Interval& interval, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    return propagate(epoch, interval.start, interval.end, eom, vehicle, store);
}

StateHistory Integrator::propagate(const Date& endEpoch, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    const Date startEpoch = vehicle.get_state().get_epoch();
    const Time propTime   = endEpoch - startEpoch;
    return propagate(startEpoch, 0.0 * s, propTime, eom, vehicle, store);
}

StateHistory Integrator::propagate(const Time& propTime, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    return propagate(vehicle.get_state().get_epoch(), 0.0 * s, propTime, eom, vehicle, store);
}

StateHistory
    Integrator::propagate(const Date& epoch, const Time& startTime, const Time& endTime, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    // Time
    Time time              = startTime;
    const bool forwardTime = (endTime > startTime);

    Time timeStep = (_useFixedStep) ? _fixedTimeStep : _timeStepInitial;
    if (timeStep > abs(endTime - startTime)) { timeStep = abs(endTime - startTime); }
    if (!forwardTime) { timeStep = -timeStep; }

    // States
    const OrbitalElements state0 = get_initial_state(epoch, eom, vehicle);
    OrbitalElements state        = state0;

    // Setup
    setup();
    _eomPtr = &eom;

    // Fruit Loop
    const auto& sys = eom.get_system();
    StateHistory stateHistory;
    if (store) { stateHistory[epoch + time] = State({ state, epoch, sys }); }
    while (_iteration < _maxIterations) {

        // Check for event
        const bool terminalEvent = check_event(time, state, vehicle);
        state                    = vehicle.get_state().get_elements();
        if (terminalEvent) {
            print_iteration(time, state, endTime, state0);

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
            take_fixed_step(time, timeStep, state, vehicle);
        }
        else { // Variable time step
            // Loop to find step size that meets tolerance
            _variableStepIteration = 0;
            while (_variableStepIteration < _MAX_VAR_STEP_ITER) {
                // Try to step
                const bool stepSuccess = try_step(time, timeStep, state, vehicle);

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
        vehicle.update_state({ state, epoch + time, sys });
        if (store) { stateHistory[epoch + time] = vehicle.get_state(); }

        // Ensure last step goes to exact final time
        if ((forwardTime && time + timeStep > endTime && time < endTime) ||
            (!forwardTime && time + timeStep < endTime && time > endTime)) {
            timeStep = endTime - time;
        }
        // Break if final time is reached
        else if (time == endTime) {
            break;
        }

        // Print time and state
        print_iteration(time, state, endTime, state0);

        // Step iteration
        ++_iteration;
    }

    // Store last state if not already stored
    if (!store) { stateHistory[epoch + time] = vehicle.get_state(); }

    // Store event times
    if (!_eventDetector.empty()) { stateHistory.set_event_times(_eventDetector.get_event_times(epoch)); }

    teardown();

    return stateHistory;
}

OrbitalElementPartials Integrator::find_state_derivative(const Time& time, const OrbitalElements& state, Vehicle& vehicle)
{
    // Count fevals
    ++_functionEvaluations;

    // Ask eom object to evaluate
    return _eomPtr->operator()(state, vehicle); // TODO: Enforce returned element matches the partial of the expected set
}

void Integrator::setup()
{
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
    if (_iteration >= _maxIterations) {
        std::cout << "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try "
                     "again. \n\n";
    }
}


OrbitalElements Integrator::get_initial_state(const Date& epoch, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Propagate vehicle to initial time without storing
    const Date vehicleEpoch = vehicle.get_state().get_epoch();
    if (epoch != vehicleEpoch) {
        const Time propTime = epoch - vehicleEpoch;
        propagate(vehicleEpoch, 0.0 * s, propTime, eom, vehicle, false); // TODO: I think this is correct but it is causing slowdowns of ~O(100)
    }

    // Need to check input elements match expected for EOMS
    const auto& sys                 = eom.get_system();
    const std::size_t expectedSetId = eom.get_expected_set_id();
    OrbitalElements state0          = vehicle.get_state().get_elements();
    if (state0.index() != expectedSetId) {
        state0 = state0.convert_to_set(expectedSetId, sys);
        // state0.convert_to_set<expectedSetId>(sys); // Can't make get expected set id static :(
        vehicle.update_state({ state0, epoch, sys });
    }
    // TODO: Should the integration function be templated? Should EOM have a different architecture? Ugh.

    return state0;
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
            throw std::invalid_argument(
                "Integration Error: Stepping method not found. Options are {RK45, RKF45, "
                "RKF78, DOP45, DOP78}."
            );
    }
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
std::pair<OrbitalElements, OrbitalElements>
    Integrator::take_step(const Time& time, const Time& timeStep, const OrbitalElements& state, Vehicle& vehicle)
{
    // Find k values: ki = timeStep*find_state_derivative(time + c[i]*stepSize, state + sum_(j=0)^(i+1) k_j a[i+1][j])
    for (std::size_t iStage = 0; iStage < _nStages; ++iStage) {
        // Find derivative
        OrbitalElementPartials partial;
        if (iStage == 0) {
            if (_stepMethod == StepMethod::RK45 || _stepMethod == StepMethod::RKF45 || _stepMethod == StepMethod::RKF78) {
                partial = find_state_derivative(time, state, vehicle);
            }
            else if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
                partial = (_iteration == 0) ? find_state_derivative(time, state, vehicle) : _YFinalPrevious;
            }
        }
        else {
            partial = find_state_derivative(time + _c[iStage] * timeStep, _statePlusKi, vehicle);
        }
        _statePlusKi = state;

        // Correct k value
        _kMatrix[iStage] = partial * timeStep;

        // Get k next step
        for (std::size_t jStage = 0; jStage < iStage + 1; ++jStage) {
            _statePlusKi += _kMatrix[jStage] * _a[iStage + 1][jStage];
        }
    }

    // Get new state and state error
    OrbitalElements stateNew   = state + _kMatrix[0] * _b[0];
    OrbitalElements stateError = _kMatrix[0] * _db[0];
    for (std::size_t iStage = 1; iStage < _nStages; ++iStage) {
        stateNew += _kMatrix[iStage] * _b[iStage];
        stateError += _kMatrix[iStage] * _db[iStage];
    }

    return { stateNew, stateError };
}

Unitless Integrator::find_max_error(const OrbitalElements& stateNew, const OrbitalElements& stateError) const
{
    // Find max error from step
    Unitless maxError           = 0.0;
    const auto stateErrorScaled = stateError.to_vector();
    const auto stateNewScaled   = stateNew.to_vector();
    for (std::size_t ii = 0; ii < stateErrorScaled.size(); ++ii) {
        // Error
        const auto err = mp_units::abs(stateErrorScaled[ii]) / (_absTol + mp_units::abs(stateNewScaled[ii]) * _relTol);
        if (err > maxError) { maxError = err; }

        // Catch huge steps
        /* There has to be a better way to do this. It's still possible for the integration to
           pass through a singularity without a huge step */
        if (mp_units::abs(stateNewScaled[ii] - stateErrorScaled[ii]) > 1.0e6 * astrea::detail::unitless ||
            mp_units::isinf(stateNewScaled[ii]) || mp_units::isnan(stateNewScaled[ii])) {
            /* 1e6 is arbitrily chosen but is a safe bet for orbital calculations.
               If the step is legitimate, but just very large, this will just force
               it to lower the step slightly and try again without killing the run */
            maxError = 2.0; // Force step failure
        }
    }

    return maxError;
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
bool Integrator::try_step(Time& time, Time& timeStep, OrbitalElements& state, Vehicle& vehicle)
{
    // Take step
    const auto [stateNew, stateError] = take_step(time, timeStep, state, vehicle);

    // Find max error
    const auto maxError = find_max_error(stateNew, stateError);

    // Check error of step
    return check_error(maxError, stateNew, stateError, time, timeStep, state);
}


void Integrator::take_fixed_step(Time& time, Time& timeStep, OrbitalElements& state, Vehicle& vehicle)
{
    // Take step
    const auto [stateNew, stateError] = take_step(time, timeStep, state, vehicle);

    // Step time
    time += timeStep;

    // Adding the state error improves the next guess (???)
    state = stateNew + stateError;

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

bool Integrator::check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state)
{
    if (maxError <= 1.0) { // Step succeeded
        // Step
        time += timeStep;
        state = stateNew;

        store_final_func_eval(timeStep);

        // Store step and error
        _timeStepPrevious = timeStep;
        _maxErrorPrevious = maxError;

        // Get new step after stepping time
        if (_iteration == 0) {
            timeStep *= (maxError < _MIN_ERROR_TO_CATCH) ? _MIN_ERROR_STEP_FACTOR : pow<1, 5>(_EPSILON / maxError);
        }
        else {
            // Predicted relative step size
            Unitless relativeTimeStep = 1.0 * mp_units::one;
            if (maxError == 0.0 * astrea::detail::unitless && _maxErrorPrevious == 0.0 * astrea::detail::unitless) { // TODO: Check more closely why we're getting 0 error
                // std::cout << "Integrator Error: Max error is zero. This should not happen." << std::endl;
            }
            else {
                relativeTimeStep = abs(timeStep / _timeStepPrevious) * pow<2, 25>(_EPSILON / maxError) *
                                   pow<3, 50>(maxError / _maxErrorPrevious);
            }

            // New step size
            timeStep *= relativeTimeStep;
        }

        // Go to next step
        return true;
    }

    // Error is too large. Truncate stepsize
    // Predicted relative step size
    const Unitless relativeTimeStep = pow<1, 5>(_EPSILON / maxError);

    // Keep step from getting too small too fast
    timeStep *= (relativeTimeStep < _MIN_REL_STEP_SIZE) ? _MIN_REL_STEP_SIZE : relativeTimeStep;

    return false;
}


void Integrator::print_iteration(const Time& time, const OrbitalElements& state, const Time& endTime, const OrbitalElements& state0)
{
    // This message is not lined up with iteration since ti and statei are advanced before this but it's okay
    if (_printOn) {
        if (_iteration == 0) {
            std::cout << "Run Conditions:" << std::endl << std::endl;
            std::cout << "Initial Time = " << 0.0 << std::endl;
            std::cout << "Final Time =  " << endTime << std::endl;
            std::cout << "Initial State = " << state0 << std::endl;
            std::cout << "Integration Tolerance: " << _relTol << std::endl << std::endl;
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

bool Integrator::check_event(const Time& time, const OrbitalElements& state, Vehicle& vehicle)
{
    return _eventDetector.detect_events(time, state, vehicle);
}

bool Integrator::validate_state_and_time(const Time& time, const OrbitalElements& state) const
{
    if (isinf(abs(time)) || isnan(abs(time))) { return false; }
    for (const auto& x : state.to_vector()) {
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
void Integrator::set_abs_tol(const Unitless& absTol) { _absTol = absTol; }

void Integrator::set_rel_tol(const Unitless& relTol) { _relTol = relTol; }

void Integrator::set_max_iter(const int& itMax) { _maxIterations = itMax; }

void Integrator::switch_print(const bool& onOff) { _printOn = onOff; }

void Integrator::switch_timer(const bool& onOff) { _timerOn = onOff; }

void Integrator::set_initial_timestep(const Time& initialTimeStep) { _timeStepInitial = initialTimeStep; }

void Integrator::switch_fixed_timestep(const bool& onOff) { _useFixedStep = onOff; }

void Integrator::switch_fixed_timestep(const bool& onOff, const Time& fixedTimeStep)
{
    _useFixedStep  = onOff;
    _fixedTimeStep = fixedTimeStep;
}

void Integrator::set_timestep(const Time& fixedTimeStep) { _fixedTimeStep = fixedTimeStep; }

void Integrator::set_step_method(const StepMethod& stepMethod) { _stepMethod = stepMethod; }

void Integrator::set_events(const std::vector<Event>& events) { _eventDetector.set_events(events); }

} // namespace astro
} // namespace astrea