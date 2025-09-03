#include <astro/propagation/numerical/Integrator.hpp>

#include <mp-units/math.h>

#include <astro/state/orbital_elements/orbital_elements.hpp>

using namespace mp_units;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {


OrbitalElementPartials
    Integrator::find_state_derivative(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Count fevals
    ++_functionEvaluations;

    // Ask eom object to evaluate
    return eom(state, vehicle);
}


StateHistory
    Integrator::propagate(const Date& epoch, const Interval& interval, const EquationsOfMotion& eom, Vehicle& vehicle, bool store, std::vector<Event> events)
{
    return propagate(epoch, interval.start, interval.end, eom, vehicle, store, events);
}

StateHistory Integrator::propagate(
    const Date& epoch,
    const Time& startTime,
    const Time& endTime,
    const EquationsOfMotion& eom,
    Vehicle& vehicle,
    bool store,
    std::vector<Event> events
)
{
    // Set events
    _eventDetector.set_events(events);

    // Propagate vehicle to initial time without storing
    const Date vehicleEpoch = vehicle.get_state().get_epoch();
    if (epoch != vehicleEpoch) {
        const Time propTime = epoch - vehicleEpoch;
        propagate(vehicleEpoch, 0.0 * s, propTime, eom, vehicle, false); // TODO: I think this is correct but it is causing slowdowns of ~O(100)
    }

    // Time
    Time time     = startTime;
    Time timeStep = (_useFixedStep) ? _fixedTimeStep : _timeStepInitial;

    if (endTime < startTime) {
        _forwardTime = false;
        timeStep     = -timeStep;
    }

    // States
    OrbitalElements state0 = vehicle.get_state().get_elements();

    // Need to check input elements match expected for EOMS
    //
    const auto& sys                 = eom.get_system();
    const std::size_t expectedSetId = eom.get_expected_set_id();
    if (state0.index() != expectedSetId) { // ooh boy we're fragile
        switch (expectedSetId) {
            case (OrbitalElements::get_set_id<Cartesian>()): {
                state0.convert<Cartesian>(sys);
                break;
            }
            case (OrbitalElements::get_set_id<Keplerian>()): {
                state0.convert<Keplerian>(sys);
                break;
            }
            case (OrbitalElements::get_set_id<Equinoctial>()): {
                state0.convert<Equinoctial>(sys);
                break;
            }
            default: throw std::runtime_error("Unrecognized element set requested.");
        }
        vehicle.update_state({ state0, epoch, sys });
    }
    OrbitalElements state = state0;
    // OrbitalElements state = state0.convert<expectedSetId>(sys); // Can't make get expected set id static :(
    // TODO: Should this function be templated? Should EOM have a different architecture? Ugh.

    // Ensure count restarts
    _functionEvaluations = 0;

    // Setup stepper
    setup_stepper();

    // Fruit Loop
    _iteration = 0;
    startTimer();
    StateHistory stateHistory;
    if (store) { stateHistory[epoch + time] = State({ state, epoch, sys }); }
    while (_iteration < _MAX_ITER) {

        // Check for event
        const bool terminalEvent = check_event(time, state, eom, vehicle);
        if (terminalEvent) {
            print_iteration(time, state, endTime, state0);

            std::cout << "Warning: Terminal conditions detected.";
            return stateHistory;
        }

        if (_useFixedStep) {
            // Step without error correction
            // I think an interesting choice would allow the user to use the fixed timestep but the
            // Integrator would use variable stepper to each fixed timestep. This would give the
            // desired output with the ensured accuracy of the variable stepper
            try_step(time, timeStep, state, eom, vehicle);
        }
        else { // Variable time step
            // Loop to find step size that meets tolerance
            _variableStepIteration = 0;
            _stepSuccess           = false;
            while (_variableStepIteration < _MAX_VAR_STEP_ITER) {
                // Try to step
                try_step(time, timeStep, state, eom, vehicle);

                // Catch underflow
                if (time + timeStep == time) {
                    std::cout << "Integration Error: Stepsize underflow. \n\n";
                    return stateHistory;
                }

                // Break if step succeeded
                if (_stepSuccess) { break; }

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

        vehicle.update_state({ state, epoch + time, sys });
        if (store) { stateHistory[epoch + time] = vehicle.get_state(); }

        // Ensure last step goes to exact final time
        if ((_forwardTime && time + timeStep > endTime && time < endTime) ||
            (!_forwardTime && time + timeStep < endTime && time > endTime)) {
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
    endTimer();

    // Exceeded max outer loop iterations
    if (_iteration >= _MAX_ITER) {
        std::cout << "Warning: Max iterations exceeded before final time reached. \nIncrease max iterations and try "
                     "again. \n\n";
    }

    // Performance
    print_performance();

    return stateHistory;
}

void Integrator::setup_stepper()
{
    switch (_stepMethod) {
        //----------------------------------- Runge-Kutta(-Fehlberg) Methods -----------------------------------//
        case StepMethod::RK45: // Traditional RK45

            // Delcare number of stages
            _nStages = 6;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = a_rk45[ii][jj];
                }
                _b[ii]    = b_rk45[ii];
                _bhat[ii] = bhat_rk45[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = c_rk45[ii];
            }
            break;

        case StepMethod::RKF45: // RKF 45 Method

            // Delcare number of stages
            _nStages = 6;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = a_rkf45[ii][jj];
                }
                _b[ii]    = b_rkf45[ii];
                _bhat[ii] = bhat_rkf45[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = c_rkf45[ii];
            }
            break;

        case StepMethod::RKF78: // Runge-Kutta-Felhlberg 78 Method

            // Delcare number of stages
            _nStages = 13;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = a_rkf78[ii][jj];
                }
                _b[ii]    = b_rkf78[ii];
                _bhat[ii] = bhat_rkf78[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = c_rkf78[ii];
            }
            break;

        //--------------------------------------- Dormand-Prince Methods ---------------------------------------//
        case StepMethod::DOP45: // Dormand-Prince 45 Method

            // Delcare number of stages
            _nStages = 7;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = a_dop45[ii][jj];
                }
                _b[ii]    = b_dop45[ii];
                _bhat[ii] = bhat_dop45[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = c_dop45[ii];
            }
            break;

        case StepMethod::DOP78: // Dormand-Prince 78 Method

            // Delcare number of stages
            _nStages = 13;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < _nStages; ++ii) {
                for (std::size_t jj = 0; jj < _nStages; ++jj) {
                    _a[ii][jj] = a_dop78[ii][jj];
                }
                _b[ii]    = b_dop78[ii];
                _bhat[ii] = bhat_dop78[ii];
                _db[ii]   = _b[ii] - _bhat[ii];
                _c[ii]    = c_dop78[ii];
            }
            break;

        default:
            throw std::invalid_argument(
                "Integration Error: Stepping method not found. Options are {RK45, RKF45, "
                "RKF78, DOP45, DOP78}."
            );
    }
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
void Integrator::try_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{

    // Find k values: ki = timeStep*find_state_derivative(time + c[i]*stepSize, state + sum_(j=0)^(i+1) k_j a[i+1][j])
    for (std::size_t iStage = 0; iStage < _nStages; ++iStage) {
        // Find derivative
        OrbitalElementPartials partial;
        if (iStage == 0) {
            if (_stepMethod == StepMethod::RK45 || _stepMethod == StepMethod::RKF45 || _stepMethod == StepMethod::RKF78) {
                partial = find_state_derivative(time, state, eom, vehicle);
            }
            else if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
                if (_iteration == 0) { partial = find_state_derivative(time, state, eom, vehicle); }
                else {
                    partial = _YFinalPrevious;
                }
            }
        }
        else {
            OrbitalElements sPlusKi = _statePlusKi;
            partial                 = find_state_derivative(time + _c[iStage] * timeStep, sPlusKi, eom, vehicle);
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

    // Find max error from step
    Unitless maxError = 0.0;
    if (!_useFixedStep) {
        const auto stateErrorScaled = stateError.to_vector();
        const auto stateNewScaled   = stateNew.to_vector();
        for (std::size_t ii = 0; ii < stateErrorScaled.size(); ++ii) {
            // Error
            const auto err = mp_units::abs(stateErrorScaled[ii]) / (_ABS_TOL + mp_units::abs(stateNewScaled[ii]) * _REL_TOL);
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
    }

    // Check error of step
    if (!_useFixedStep) { check_error(maxError, stateNew, stateError, time, timeStep, state); }
    else {
        // Step time
        time += timeStep;

        // Adding the state error improves the next guess
        stateNew += stateError;

        // Store final function eval for Dormand-Prince methods
        if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
            _YFinalPrevious = _kMatrix[_nStages - 1] / timeStep;
        }

        state = stateNew;
    }
}


void Integrator::check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state)
{

    if (maxError <= 1.0) { // Step succeeded

        time += timeStep;
        state = stateNew;

        // Store final function eval for Dormand-Prince methods
        if (_stepMethod == StepMethod::DOP45 || _stepMethod == StepMethod::DOP78) {
            _YFinalPrevious = _kMatrix[_nStages - 1] / timeStep;
        }

        // Get new step after stepping time
        if (_iteration == 0) {
            // Store step and error
            _timeStepPrevious = timeStep;
            _maxErrorPrevious = maxError;

            if (maxError < _MIN_ERROR_TO_CATCH) { // Step is too small
                timeStep *= _MIN_ERROR_STEP_FACTOR;
            }
            else {
                timeStep *= pow<1, 5>(_EPSILON / maxError);
            }
        }
        else {
            // Predicted relative step size
            Unitless relativeTimeStep = 1.0 * astrea::detail::unitless;
            if (maxError != 0.0 * astrea::detail::unitless && _maxErrorPrevious != 0.0 * astrea::detail::unitless) { // TODO: Check more closely why we're getting 0 error
                relativeTimeStep = abs(timeStep / _timeStepPrevious) * pow<2, 25>(_EPSILON / maxError) *
                                   pow<3, 50>(maxError / _maxErrorPrevious);
            }
            else {
                std::cout << "Integrator Error: Max error is zero. This should not happen." << std::endl;
            }

            // Store step and error after computing relative time step
            _timeStepPrevious = timeStep;
            _maxErrorPrevious = maxError;

            // New step size
            timeStep *= relativeTimeStep;
        }

        // Go to next step
        _stepSuccess = true;
    }
    else { // Error is too large . truncate stepsize
        // Predicted relative step size
        const Unitless relativeTimeStep = pow<1, 5>(_EPSILON / maxError);

        // Keep step from getting too small too fast
        timeStep *= (relativeTimeStep < _MIN_REL_STEP_SIZE) ? _MIN_REL_STEP_SIZE : relativeTimeStep;
    }
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

bool Integrator::check_event(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Have equations of motion class check if object crashed
    // Should allow user to input pointer to custom event function
    bool terminalEvent = _eventDetector.detect_events(time, state, vehicle);

    // Break if hit nans or infs
    if (isinf(abs(time)) || isnan(abs(time))) { terminalEvent = true; }
    else {
        for (const auto& x : state.to_vector()) {
            if (isinf(abs(x)) || isnan(abs(x))) { terminalEvent = true; }
        }
    }
    return terminalEvent;
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