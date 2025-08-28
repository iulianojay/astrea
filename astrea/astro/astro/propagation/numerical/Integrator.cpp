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
    ++functionEvaluations;

    // Ask eom object to evaluate
    return eom(state, vehicle);
}


StateHistory Integrator::propagate(const Date& epoch, const Interval& interval, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    return propagate(epoch, interval.start, interval.end, eom, vehicle, store);
}

StateHistory
    Integrator::propagate(const Date& epoch, const Time& startTime, const Time& endTime, const EquationsOfMotion& eom, Vehicle& vehicle, bool store)
{
    // Propagate vehicle to initial time without storing
    const Date vehicleEpoch = vehicle.get_state().get_epoch();
    if (epoch != vehicleEpoch) {
        const Time propTime = epoch - vehicleEpoch;
        propagate(vehicleEpoch, 0.0 * s, propTime, eom, vehicle, false); // TODO: I think this is correct but it is causing slowdowns of ~O(100)
    }

    // Time
    Time time     = startTime;
    Time timeStep = (useFixedStep) ? fixedTimeStep : timeStepInitial;

    if (endTime < startTime) {
        forwardTime = false;
        timeStep    = -timeStep;
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
    functionEvaluations = 0;

    // Setup stepper
    setup_stepper();

    // Fruit Loop
    iteration = 0;
    startTimer();
    StateHistory stateHistory;
    if (store) { stateHistory[epoch + time] = State({ state, epoch, sys }); }
    while (iteration < iterMax) {

        // Check for event
        check_event(time, state, eom, vehicle);
        if (eventTrigger) {
            print_iteration(time, state, endTime, state0);

            std::cout << crashMessage;
            return stateHistory;
        }

        if (useFixedStep) {
            // Step without error correction
            // I think an interesting choice would allow the user to use the fixed timestep but the
            // Integrator would use variable stepper to each fixed timestep. This would give the
            // desired output with the ensured accuracy of the variable stepper
            try_step(time, timeStep, state, eom, vehicle);
        }
        else { // Variable time step
            // Loop to find step size that meets tolerance
            variableStepIteration = 0;
            stepSuccess           = false;
            while (variableStepIteration < maxVariableStepIterations) {
                // Try to step
                try_step(time, timeStep, state, eom, vehicle);

                // Catch underflow
                if (time + timeStep == time) {
                    std::cout << underflowErrorMessage;
                    return stateHistory;
                }

                // Break if step succeeded
                if (stepSuccess) { break; }

                // Inner Loop Iteration
                ++variableStepIteration;
            }

            // Exceeded max inner loop iterations
            if (variableStepIteration >= maxVariableStepIterations) {
                std::cout << innerLoopStepOverflowErrorMessage;
                return stateHistory;
            }
        }

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
        ++iteration;
    }
    endTimer();

    // Exceeded max outer loop iterations
    if (iteration >= iterMax) { std::cout << outerLoopStepOverflowErrorMessage; }

    // Performance
    print_performance();

    return stateHistory;
}

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- Stepping Methods --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::setup_stepper()
{
    switch (stepMethod) {
        //----------------------------------- Runge-Kutta(-Fehlberg) Methods -----------------------------------//
        case RK45: // Traditional RK45

            // Delcare number of stages
            nStages = 6;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < nStages; ++ii) {
                for (std::size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rk45[ii][jj];
                }
                b[ii]    = b_rk45[ii];
                bhat[ii] = bhat_rk45[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_rk45[ii];
            }
            break;

        case RKF45: // RKF 45 Method

            // Delcare number of stages
            nStages = 6;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < nStages; ++ii) {
                for (std::size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rkf45[ii][jj];
                }
                b[ii]    = b_rkf45[ii];
                bhat[ii] = bhat_rkf45[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_rkf45[ii];
            }
            break;

        case RKF78: // Runge-Kutta-Felhlberg 78 Method

            // Delcare number of stages
            nStages = 13;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < nStages; ++ii) {
                for (std::size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rkf78[ii][jj];
                }
                b[ii]    = b_rkf78[ii];
                bhat[ii] = bhat_rkf78[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_rkf78[ii];
            }
            break;

        //--------------------------------------- Dormand-Prince Methods ---------------------------------------//
        case DOP45: // Dormand-Prince 45 Method

            // Delcare number of stages
            nStages = 7;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < nStages; ++ii) {
                for (std::size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_dop45[ii][jj];
                }
                b[ii]    = b_dop45[ii];
                bhat[ii] = bhat_dop45[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_dop45[ii];
            }
            break;

        case DOP78: // Dormand-Prince 78 Method

            // Delcare number of stages
            nStages = 13;

            // Get Butcher Tableau
            for (std::size_t ii = 0; ii < nStages; ++ii) {
                for (std::size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_dop78[ii][jj];
                }
                b[ii]    = b_dop78[ii];
                bhat[ii] = bhat_dop78[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_dop78[ii];
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
    for (std::size_t iStage = 0; iStage < nStages; ++iStage) {
        // Find derivative
        OrbitalElementPartials partial;
        if (iStage == 0) {
            if (stepMethod == RK45 || stepMethod == RKF45 || stepMethod == RKF78) {
                partial = find_state_derivative(time, state, eom, vehicle);
            }
            else if (stepMethod == DOP45 || stepMethod == DOP78) {
                if (iteration == 0) { partial = find_state_derivative(time, state, eom, vehicle); }
                else {
                    partial = YFinalPrevious;
                }
            }
        }
        else {
            OrbitalElements sPlusKi = statePlusKi;
            partial                 = find_state_derivative(time + c[iStage] * timeStep, sPlusKi, eom, vehicle);
        }
        statePlusKi = state;

        // Correct k value
        kMatrix[iStage] = partial * timeStep;

        // Get k next step
        for (std::size_t jStage = 0; jStage < iStage + 1; ++jStage) {
            statePlusKi += kMatrix[jStage] * a[iStage + 1][jStage];
        }
    }

    // Get new state and state error
    OrbitalElements stateNew   = state + kMatrix[0] * b[0];
    OrbitalElements stateError = kMatrix[0] * db[0];
    for (std::size_t iStage = 1; iStage < nStages; ++iStage) {
        stateNew += kMatrix[iStage] * b[iStage];
        stateError += kMatrix[iStage] * db[iStage];
    }

    // Find max error from step
    Unitless maxError = 0.0;
    if (!useFixedStep) {
        const auto stateErrorScaled = stateError.to_vector();
        const auto stateNewScaled   = stateNew.to_vector();
        for (std::size_t ii = 0; ii < stateErrorScaled.size(); ++ii) {
            // Error
            const auto err = mp_units::abs(stateErrorScaled[ii]) /
                             (absoluteTolerance + mp_units::abs(stateNewScaled[ii]) * relativeTolerance);
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
    if (!useFixedStep) { check_error(maxError, stateNew, stateError, time, timeStep, state); }
    else {
        // Step time
        time += timeStep;

        // Adding the state error improves the next guess
        stateNew += stateError;

        // Store final function eval for Dormand-Prince methods
        if (stepMethod == DOP45 || stepMethod == DOP78) { YFinalPrevious = kMatrix[nStages - 1] / timeStep; }

        state = stateNew;
    }
}


void Integrator::check_error(const Unitless& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state)
{

    if (maxError <= 1.0) { // Step succeeded

        time += timeStep;
        state = stateNew;

        // Store final function eval for Dormand-Prince methods
        if (stepMethod == DOP45 || stepMethod == DOP78) { YFinalPrevious = kMatrix[nStages - 1] / timeStep; }

        // Get new step after stepping time
        if (iteration == 0) {
            // Store step and error
            timeStepPrevious = timeStep;
            maxErrorPrevious = maxError;

            if (maxError < minErrorCatch) { // Step is too small
                timeStep *= minErrorStepFactor;
            }
            else {
                timeStep *= pow<1, 5>(epsilon / maxError);
            }
        }
        else {
            // Predicted relative step size
            Unitless relativeTimeStep = 1.0 * astrea::detail::unitless;
            if (maxError != 0.0 * astrea::detail::unitless && maxErrorPrevious != 0.0 * astrea::detail::unitless) { // TODO: Check more closely why we're getting 0 error
                relativeTimeStep = abs(timeStep / timeStepPrevious) * pow<2, 25>(epsilon / maxError) *
                                   pow<3, 50>(maxError / maxErrorPrevious);
            }
            else {
                std::cout << "Integrator Error: Max error is zero. This should not happen." << std::endl;
            }

            // Store step and error after computing relative time step
            timeStepPrevious = timeStep;
            maxErrorPrevious = maxError;

            // New step size
            timeStep *= relativeTimeStep;
        }

        // Go to next step
        stepSuccess = true;
    }
    else { // Error is too large . truncate stepsize
        // Predicted relative step size
        const Unitless relativeTimeStep = pow<1, 5>(epsilon / maxError);

        // Keep step from getting too small too fast
        if (relativeTimeStep < minRelativeStepSize) { // step size is too small
            timeStep *= minRelativeStepSize;
        }
        else {
            timeStep *= relativeTimeStep;
        }
    }
}


void Integrator::print_iteration(const Time& time, const OrbitalElements& state, const Time& endTime, const OrbitalElements& state0)
{
    // This message is not lined up with iteration since ti and statei are advanced before this but it's okay
    if (printOn) {
        // if (iteration == 0 || (day % 100 == 0 && day != checkDay) || time == endTime || eventTrigger) {
        if (iteration == 0) {
            std::cout << "Run Conditions:" << std::endl << std::endl;
            std::cout << "Initial Time = " << 0.0 << std::endl;
            std::cout << "Final Time =  " << endTime << std::endl;
            std::cout << "Initial State = " << state0 << std::endl;
            std::cout << "Integration Tolerance: " << relativeTolerance << std::endl << std::endl;
            std::cout << "Run:" << std::endl << std::endl;
        }
        else {
            std::cout << "Iteration: " << iteration + 1 << std::endl;
            std::cout << "time = " << time << std::endl;
            std::cout << "state = " << state << std::endl << std::endl;
        }
        // }
        if (time == endTime) { std::cout << "Run Completed." << std::endl << std::endl; }
    }
}

void Integrator::print_performance() const
{
    if (printOn) {
        std::cout << "Number of Steps:                " << iteration << " iter" << std::endl;
        std::cout << "Number of Function Evaluations: " << functionEvaluations << " fval" << std::endl;

        double runtime{};
        if (timerOn) {
            runtime = ((double)endClock - (double)startClock) / ((double)CLOCKS_PER_SEC);
            std::cout << "Runtime:                        " << runtime << " s" << std::endl;
        }

        std::cout << "\nAverage Function Evaluations per Step:   " << (double)functionEvaluations / (double)iteration
                  << " fval/iter" << std::endl;

        if (timerOn) {
            std::cout << "Average Runtime per Step:                " << runtime / (double)iteration << " s/iter" << std::endl;
            std::cout << "Average Runtime per Function Evaluation: " << runtime / (double)functionEvaluations
                      << " s/fval" << std::endl
                      << std::endl;
        }
    }
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Event Function ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::check_event(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Have equations of motion class check if object crashed
    // Should allow user to input pointer to custom event function
    eventTrigger = eom.check_crash(state, vehicle);

    // Break if hit nans or infs
    if (isinf(abs(time)) || isnan(abs(time))) { eventTrigger = true; }
    else {
        for (const auto& x : state.to_vector()) {
            if (isinf(abs(x)) || isnan(abs(x))) { eventTrigger = true; }
        }
    }
}


// Integrator Properties
void Integrator::set_abs_tol(Unitless absTol) { absoluteTolerance = absTol; }
void Integrator::set_rel_tol(Unitless relTol) { relativeTolerance = relTol; }
void Integrator::set_max_iter(int itMax) { iterMax = itMax; }

void Integrator::switch_print(bool onOff) { printOn = onOff; }
void Integrator::switch_timer(bool onOff) { timerOn = onOff; }

void Integrator::set_initial_timestep(Time dt0) { timeStepInitial = dt0; }
void Integrator::switch_fixed_timestep(bool onOff) { useFixedStep = onOff; }
void Integrator::switch_fixed_timestep(bool onOff, Time fixedTimeStep)
{
    useFixedStep  = onOff;
    fixedTimeStep = fixedTimeStep;
}
void Integrator::set_timestep(Time fixedTimeStep) { fixedTimeStep = fixedTimeStep; }

void Integrator::set_step_method(std::string stepMethod)
{
    Integrator::odeStepper stepper{};
    if (stepMethod == "RK45") { stepper = Integrator::odeStepper::RK45; }
    else if (stepMethod == "RKF45") {
        stepper = Integrator::odeStepper::RKF45;
    }
    else if (stepMethod == "RKF78") {
        stepper = Integrator::odeStepper::RKF78;
    }
    else if (stepMethod == "DOP45") {
        stepper = Integrator::odeStepper::DOP45;
    }
    else if (stepMethod == "DOP78") {
        stepper = Integrator::odeStepper::DOP78;
    }
    else {
        std::cout << "Warning: Unknown step method selected. No change applied. \n\n";
    }
    stepMethod = stepper;
}

} // namespace astro
} // namespace astrea