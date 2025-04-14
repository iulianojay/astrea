#include <astro/propagation/Integrator.hpp>


OrbitalElementPartials
    Integrator::find_state_derivative(const Time& time, const OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    // Count fevals
    ++functionEvaluations;

    // Ask eom object to evaluate
    return eom(time, state, vehicle);
}


void Integrator::propagate(const Interval& interval, const EquationsOfMotion& eom, Vehicle& vehicle)
{
    integrate(interval.start, interval.end, eom, vehicle);
}

void Integrator::integrate(const Time& timeInitial, const Time& timeFinal, const EquationsOfMotion& eom, Vehicle& vehicle)
{

    // Time
    Time time     = timeInitial;
    Time timeStep = (useFixedStep) ? fixedTimeStep : timeStepInitial;

    if (timeFinal < timeInitial) {
        forwardTime = false;
        timeStep    = -timeStep;
    }

    // States
    const OrbitalElements stateInitial = vehicle.get_state().elements;
    OrbitalElements state              = stateInitial;

    // Ensure count restarts
    functionEvaluations = 0;

    // Setup stepper
    setup_stepper();

    // Fruit Loop
    iteration = 0;
    startTimer();
    while (iteration < iterMax) {

        // Break if final time is reached
        if ((forwardTime && time > timeFinal) || (!forwardTime && time < timeFinal)) { break; }

        // Check for event
        check_event(time, state, eom, vehicle);
        if (eventTrigger) {
            print_iteration(time, state, timeFinal, stateInitial);

            std::cout << crashMessage;
            return;
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
                    return;
                }

                // Break if step succeeded
                if (stepSuccess) { break; }

                // Inner Loop Iteration
                ++variableStepIteration;
            }

            // Exceeded max inner loop iterations
            if (variableStepIteration >= maxVariableStepIterations) {
                std::cout << innerLoopStepOverflowErrorMessage;
                return;
            }
        }

        vehicle.update_state({ time, state });

        // Ensure last step goes to exact final time
        if ((forwardTime && time + timeStep > timeFinal && time < timeFinal) ||
            (!forwardTime && time + timeStep < timeFinal && time > timeFinal)) {
            timeStep = timeFinal - time;
        }

        // Print time and state
        print_iteration(time, state, timeFinal, stateInitial);

        // Step iteration
        ++iteration;
    }
    endTimer();

    // Exceeded max outer loop iterations
    if (iteration >= iterMax) { std::cout << outerLoopStepOverflowErrorMessage; }

    // Performance
    print_performance();
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
            for (size_t ii = 0; ii < nStages; ++ii) {
                for (size_t jj = 0; jj < nStages; ++jj) {
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
            for (size_t ii = 0; ii < nStages; ++ii) {
                for (size_t jj = 0; jj < nStages; ++jj) {
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
            for (size_t ii = 0; ii < nStages; ++ii) {
                for (size_t jj = 0; jj < nStages; ++jj) {
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
            for (size_t ii = 0; ii < nStages; ++ii) {
                for (size_t jj = 0; jj < nStages; ++jj) {
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
            for (size_t ii = 0; ii < nStages; ++ii) {
                for (size_t jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_dop78[ii][jj];
                }
                b[ii]    = b_dop78[ii];
                bhat[ii] = bhat_dop78[ii];
                db[ii]   = b[ii] - bhat[ii];
                c[ii]    = c_dop78[ii];
            }
            break;

        default:
            throw std::invalid_argument("Integration Error: Stepping method not found. Options are {RK45, RKF45, "
                                        "RKF78, DOP45, DOP78}.");
    }
}

// This is a generic form of an rk step method. Works for any rk, rkf, or dop method.
void Integrator::try_step(Time& time, Time& timeStep, OrbitalElements& state, const EquationsOfMotion& eom, Vehicle& vehicle)
{

    // Find k values: ki = timeStep*find_state_derivative(time + c[i]*stepSize, state + sum_(j=0)^(i+1) k_j a[i+1][j])
    for (size_t ii = 0; ii < nStages; ++ii) {
        // Find derivative
        OrbitalElementPartials partial;
        if (ii == 0) {
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
            partial                 = find_state_derivative(time + c[ii] * timeStep, sPlusKi, eom, vehicle);
        }
        statePlusKi = state;

        // Correct k value
        kMatrix[ii] = partial * timeStep;

        // Get k next step
        for (size_t kk = 0; kk < ii + 1; ++kk) {
            statePlusKi += kMatrix[kk] * a[ii + 1][kk];
        }
    }

    // Find max error from step
    double maxError          = 0.0;
    OrbitalElements stateNew = state;
    OrbitalElements stateError;
    for (size_t ii = 0; ii < stateNew.size(); ++ii) {

        stateError[ii] = 0.0;
        for (size_t jj = 0; jj < nStages; ++jj) {
            stateNew[ii] += kMatrix[jj][ii] * b[jj];
            stateError[ii] += kMatrix[jj][ii] * db[jj];
        }

        if (!useFixedStep) {
            // Error
            maxError = std::max(maxError, abs(stateError[ii]) / (absoluteTolerance + abs(stateNew[ii]) * relativeTolerance));

            // Catch huge steps
            /* There has to be a better way to do this. It's still possible for the integration to
               pass through a singularity without a huge step */
            if (abs(stateNew[ii] - state[ii]) > 1.0e6 || std::isnan(stateNew[ii]) || std::isinf(stateNew[ii])) {
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


void Integrator::check_error(const double& maxError, const OrbitalElements& stateNew, const OrbitalElements& stateError, Time& time, Time& timeStep, OrbitalElements& state)
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
                timeStep *= std::pow(epsilon / maxError, 0.2);
            }
        }
        else {
            // Predicted relative step size
            const double relativeTimeStep = abs(timeStep / timeStepPrevious) * std::pow(epsilon / maxError, 0.08) *
                                            std::pow(maxError / maxErrorPrevious, 0.06);

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
        const double relativeTimeStep = std::pow(epsilon / maxError, 0.2);

        // Keep step from getting too small too fast
        if (relativeTimeStep < minRelativeStepSize) { // step size is too small
            timeStep *= minRelativeStepSize;
        }
        else {
            timeStep *= relativeTimeStep;
        }
    }
}


void Integrator::print_iteration(const Time& time, const OrbitalElements& state, const Time& timeFinal, const OrbitalElements& stateInitial)
{
    // This message is not lined up with iteration since ti and statei are advanced before this but it's okay
    if (printOn) {
        int day = days(time).count();
        // if (iteration == 0 || (day % 100 == 0 && day != checkDay) || time == timeFinal || eventTrigger) {
        if (iteration == 0) {
            std::cout << "Run Conditions:" << std::endl << std::endl;
            std::cout << "Initial Time = " << 0.0 << std::endl;
            std::cout << "Final Time =  " << timeFinal << std::endl;
            std::cout << "Initial State = " << stateInitial << std::endl;
            std::cout << "Integration Tolerance: " << relativeTolerance << std::endl << std::endl;
            std::cout << "Run:" << std::endl << std::endl;
        }
        else {
            checkDay = day;

            std::cout << "Iteration: " << iteration + 1 << std::endl;
            std::cout << "time = " << time << std::endl;
            std::cout << "state = " << state << std::endl << std::endl;
        }
        // }
        if (time == timeFinal) { std::cout << "Run Completed." << std::endl << std::endl; }
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
    eventTrigger = eom.check_crash(time, state, vehicle);

    // Break if hit nans or infs
    if (std::isinf(abs(time)) || std::isnan(abs(time))) { eventTrigger = true; }
    else {
        for (const auto& x : state) {
            if (std::isinf(abs(x)) || std::isnan(abs(x))) { eventTrigger = true; }
        }
    }
}


// Integrator Properties
void Integrator::set_abs_tol(double absTol) { absoluteTolerance = absTol; }
void Integrator::set_rel_tol(double relTol) { relativeTolerance = relTol; }
void Integrator::set_max_iter(int itMax) { iterMax = itMax; }

void Integrator::switch_print(bool onOff) { printOn = onOff; }
void Integrator::switch_timer(bool onOff) { timerOn = onOff; }

void Integrator::set_initial_timestep(double dt0) { timeStepInitial = dt0; }
void Integrator::switch_fixed_timestep(bool onOff) { useFixedStep = onOff; }
void Integrator::switch_fixed_timestep(bool onOff, double fixedTimeStep)
{
    useFixedStep  = onOff;
    fixedTimeStep = fixedTimeStep;
}
void Integrator::set_timestep(double fixedTimeStep) { fixedTimeStep = fixedTimeStep; }

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