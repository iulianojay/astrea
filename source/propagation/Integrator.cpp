#include "Integrator.hpp"	    // Integrator class

// Constructor and destructor
Integrator::Integrator() : equationsOfMotion() {}
Integrator::~Integrator() {}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------ Equations of Motion -------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::find_state_derivative(double time, double* state, double* stateDerivative) {
    
    // Ask eom object to evaluate
    equationsOfMotion->evaluate_state_derivative(time, state, spacecraft, stateDerivative);

    // Count fevals
    ++functionEvaluations;
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------- Integrator -----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::propagate(double timeInitial, double timeFinal, Spacecraft sc, EquationsOfMotion eom) {					
    
    // TODO: Fix this nonsense
    auto state0 = sc.get_initial_state().elements;
    state0.convert(ElementSet::CARTESIAN, eom.get_system());

    // Copy
    double stateInitial[6];
    for (int ii = 0; ii < nStates; ++ii) {
        stateInitial[ii] = state0[ii]; // initial state
    }

    // Set for now TODO: Make this pass into the functions, no need to use pointers
    spacecraft = &sc;
    equationsOfMotion = &eom;

    // Integrate
    integrate(timeInitial, timeFinal, stateInitial);

    // Assign state history to spacecraft
    
}

void Integrator::integrate(double timeInitial, double timeFinal, double* stateInitial) {

    // Setup dem variables
    time = timeInitial; // time at current iteration

    if (useFixedStep) { // time step at current iteration
        timeStep = fixedTimeStep; 
    }
    else { 
        timeStep = timeStepInitial; 
    }	

    for (int ii = 0; ii < nStates; ++ii) {
        state[ii] = stateInitial[ii]; // initial state
    }
    if (timeFinal < timeInitial) {
        forwardTime = false;
        timeStep *= -1.0;
    }

    // Clean up vectors so Integrator can be used multiple times
    cleanup();

    // Predict number of steps
    reserve_space((int) ceil(timeFinal/30)); // guess 1 point every 30 seconds

    // Ensure count restarts
    functionEvaluations = 0;

    // Setup stepper
    setup_stepper();

    // Fruit Loop 
    iteration = 0;
    startTimer();
    while (iteration < iterMax) {

        // Break if final time is reached
        if (( forwardTime && time > timeFinal) || 
            (!forwardTime && time < timeFinal)) {
            break;
        }

        // Add time and state to storage file
        store_iteration();

        // Check for event
        check_event();
        if (eventTrigger) {
            print_iteration(timeFinal, stateInitial);

            if (printOn){ 
                std::cout << crashMessage; 
            }
            return;
        }

        if (useFixedStep) {
            // Step without error correction
            // I think an interesting choice would allow the user to use the fixed timestep but the 
            // Integrator would use variable stepper to each fixed timestep. This would give the 
            // desired output with the ensured accuracy of the variable stepper
            try_step();

            // Step time
            time += timeStep;
            for (int ii = 0; ii < nStates; ++ii) {
                // Step state
                state[ii] = stateNew[ii] + stateError[ii]; // Adding the state error improves the next guess

                // Store final function eval for Dormand-Prince methods
                if (stepMethod == dop45 || stepMethod == dop78) {
                    YFinalPrevious[ii] = kMatrix[nStages-1][ii]/timeStep;
                }
            }
        }
        else { // Variable time step
            // Loop to find step size that meets tolerance
            variableStepIteration = 0;
            stepSuccess = false;
            while (variableStepIteration < maxVariableStepIterations) {
                // Try to step
                try_step();

                // Check error of step
                check_error();

                // Catch underflow
                if (time + timeStep == time) {
                    if (printOn) { 
                        std::cout << underflowErrorMessage; 
                    }
                    return;
                }

                // Break if step succeeded
                if (stepSuccess) { break; }

                // Inner Loop Iteration
                ++variableStepIteration;
            }

            // Exceeded max inner loop iterations
            if (variableStepIteration >= maxVariableStepIterations) {
                if (printOn) { 
                    std::cout << innerLoopStepOverflowErrorMessage; 
                }
                return;
            }
        }

        // Ensure last step goes to exact final time
        if (( forwardTime && time + timeStep > timeFinal && time < timeFinal) || 
            (!forwardTime && time + timeStep < timeFinal && time > timeFinal)) {
            timeStep = timeFinal - time;
        }

        // Print time and state 
        print_iteration(timeFinal, stateInitial);

        // Step iteration
        ++iteration;
    }
    endTimer();

    // Exceeded max outer loop iterations
    if (iteration >= iterMax) {
        if (printOn) {
            std::cout << outerLoopStepOverflowErrorMessage;
        }
    }

    // Performance
    print_performance();
}

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- Stepping Methods --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::setup_stepper() {
    switch (stepMethod) {
        //----------------------------------- Runge-Kutta(-Fehlberg) Methods -----------------------------------//
        case rk45: // Traditional RK45

            // Delcare number of stages
            nStages = 6;

            // Get Butcher Tableau
            for (int ii = 0; ii < nStages; ++ii) {
                for (int jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rk45[ii][jj];
                }
                b[ii] = b_rk45[ii];
                bhat[ii] = bhat_rk45[ii];
                db[ii] = b[ii] - bhat[ii];
                c[ii] = c_rk45[ii];
            }
            break;

        case rkf45: // RKF 45 Method

            // Delcare number of stages
            nStages = 6;

            // Get Butcher Tableau
            for (int ii = 0; ii < nStages; ++ii) {
                for (int jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rkf45[ii][jj];
                }
                b[ii] = b_rkf45[ii];
                bhat[ii] = bhat_rkf45[ii];
                db[ii] = b[ii] - bhat[ii];
                c[ii] = c_rkf45[ii];
            }
            break;

        case rkf78: // Runge-Kutta-Felhlberg 78 Method

            // Delcare number of stages
            nStages = 13;

            // Get Butcher Tableau
            for (int ii = 0; ii < nStages; ++ii) {
                for (int jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_rkf78[ii][jj];
                }
                b[ii] = b_rkf78[ii];
                bhat[ii] = bhat_rkf78[ii];
                db[ii] = b[ii] - bhat[ii];
                c[ii] = c_rkf78[ii];
            }
            break;

        //--------------------------------------- Dormand-Prince Methods ---------------------------------------//
        case dop45: // Dormand-Prince 45 Method

            // Delcare number of stages
            nStages = 7;

            // Get Butcher Tableau
            for (int ii = 0; ii < nStages; ++ii) {
                for (int jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_dop45[ii][jj];
                }
                b[ii] = b_dop45[ii];
                bhat[ii] = bhat_dop45[ii];
                db[ii] = b[ii] - bhat[ii];
                c[ii] = c_dop45[ii];
            }
            break;

        case dop78: // Dormand-Prince 78 Method

            // Delcare number of stages
            nStages = 13;

            // Get Butcher Tableau
            for (int ii = 0; ii < nStages; ++ii) {
                for (int jj = 0; jj < nStages; ++jj) {
                    a[ii][jj] = a_dop78[ii][jj];
                }
                b[ii] = b_dop78[ii];
                bhat[ii] = bhat_dop78[ii];
                db[ii] = b[ii] - bhat[ii];
                c[ii] = c_dop78[ii];
            }
            break;

        default:
            throw std::invalid_argument("THATS NOT A STEPPING METHOD, SIR.");
    }
}

void Integrator::try_step() { // This is a generic form of an rk step method. Works for any rk, rkf, or dop method. 

    // Find k values: ki = timeStep*find_state_derivative(time + c[i]*stepSize, state + sum_(j=0)^(i+1) k_j a[i+1][j]) 
    for (int ii = 0; ii < nStages; ++ii) {
        // Find derivative
        if (ii == 0) {
            if (stepMethod == rk45 || stepMethod == rkf45 || stepMethod == rkf78) {
                find_state_derivative(time, state, kMatrix[0]);
            }
            else if (stepMethod == dop45 || stepMethod == dop78) {
                if (iteration == 0) {
                    find_state_derivative(time, state, kMatrix[0]);
                }
                else {
                    for (int jj = 0; jj < nStages; ++jj) {
                        kMatrix[0][jj] = YFinalPrevious[jj];
                    }
                }
            }
        }
        else {
            find_state_derivative(time + c[ii]*timeStep, statePlusKi, kMatrix[ii]);
        }

        for (int jj = 0; jj < nStates; ++jj) {
            // Correct k value
            kMatrix[ii][jj] *= timeStep;

            // Get k next step
            statePlusKi[jj] = state[jj];
            for (int kk = 0; kk < ii+1; ++kk) {
                statePlusKi[jj] += kMatrix[kk][jj]*a[ii+1][kk];
            }
        }
    }

    // Find max error from step
    errorMax = 0.0;
    for (int ii = 0; ii < nStates; ++ii) {

        stateNew[ii] = state[ii];
        stateError[ii] = 0.0;
        for (int jj = 0; jj < nStages; ++jj) {
            stateNew[ii] += kMatrix[jj][ii]*b[jj];
            stateError[ii] += kMatrix[jj][ii]*db[jj];
        }

        if (!useFixedStep){
            // Error
            error = abs(stateError[ii])/(absoluteTolerance + abs(stateNew[ii])*relativeTolerance);
            if (error > errorMax) {
                errorMax = error;
            }

            // Catch huge steps
            /* There has to be a better way to do this. It's still possible for the integration to 
               pass through a singularity without a huge step */
            if (abs(stateNew[ii] - state[ii]) > 1.0e6 || std::isnan(stateNew[ii]) || std::isinf(stateNew[ii])) { 
                /* 1e6 is arbitrily chosen but is a safe bet for orbital calculations.
                   If the step is legitimate, but just very large, this will just force
                   it to lower the step slightly and try again without killing the run */
                errorMax = 2.0; // Force step failure
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------//
//---------------------------------------------- Error Methods ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::check_error() {

	if (errorMax <= 1.0) { // Step succeeded
		// Step time
		time += timeStep;
		for (int ii = 0; ii < nStates; ++ii) {
            // Step state
			state[ii] = stateNew[ii] + stateError[ii]; // Adding the state error improves the next guess

            // Store final function eval for Dormand-Prince methods
            if (stepMethod == dop45 || stepMethod == dop78) {
                YFinalPrevious[ii] = kMatrix[nStages-1][ii]/timeStep;
            }
		}

		// Get new step after stepping time
		if (iteration == 0) {
			// Store step and error
			timeStepPrevious = timeStep;
			errorMaxPrevious = errorMax;

			if (errorMax < minErrorCatch) { // Step is too small
				timeStep *= minErrorStepFactor;
			}
			else {
				timeStep *= pow(epsilon/errorMax, 0.2);
			}
		}
		else {
			// Predicted relative step size
			relativeTimeStep = abs(timeStep/timeStepPrevious)*pow(epsilon/errorMax, 0.08)*pow(errorMax/errorMaxPrevious, 0.06);

			// Store step and error after computing relative time step
			timeStepPrevious = timeStep;
			errorMaxPrevious = errorMax;

			// New step size
			timeStep *= relativeTimeStep;
		}

		// Go to next step
		stepSuccess = true;
	}
	else { // Error is too large . truncate stepsize
		// Predicted relative step size
		relativeTimeStep = pow(epsilon/errorMax, 0.2);

		// Keep step from getting too small too fast
		if (relativeTimeStep < minRelativeStepSize) { // step size is too small
			timeStep *= minRelativeStepSize;
		}
		else {
			timeStep *= relativeTimeStep;
		}
	}
}

//----------------------------------------------------------------------------------------------------------//
// ---------------------------------------------Saving Methods ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::save() {

    if (printOn) { std::cout << "Saving... \n"; }

	// Create file to write results too
	std::ofstream outf("last_run.txt");
	char buffer[200];
	snprintf(buffer, 200, "%-15s, %-15s, %-15s, %-15s, %-15s, %-15s, %-15s \n", 
             "Time (s)", "x (km)", "y (km)", "z (km)", "vx (km/s)", "vy (km/s)", "vz (km/s)");
	outf << buffer;

	for (int ii = 0; ii < (int)timeVector.size(); ++ii) {
		snprintf(buffer, 200, "%-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g \n", 
                 timeVector[ii], stateVectorOne[ii], stateVectorTwo[ii], stateVectorThree[ii], 
                 stateVectorFour[ii], stateVectorFive[ii], stateVectorSix[ii]);
		outf << buffer;
	}
    outf.close();

    if (printOn) { std::cout << "Saving Complete. \n\n"; }
}

void Integrator::save(std::string filename) {

    if (printOn){ std::cout << "Saving... \n"; }

	// Create file to write results too
	std::ofstream outf(filename);
	char buffer[200];
	snprintf(buffer, 200, "%-15s, %-15s, %-15s, %-15s, %-15s, %-15s, %-15s \n", 
             "Time (s)", "x (km)", "y (km)", "z (km)", "vx (km/s)", "vy (km/s)", "vz (km/s)");
	outf << buffer;

	for (int ii = 0; ii < (int)timeVector.size(); ++ii) {
		snprintf(buffer, 200, "%-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g, %-15.8g \n", 
                 timeVector[ii], stateVectorOne[ii], stateVectorTwo[ii], stateVectorThree[ii], 
                 stateVectorFour[ii], stateVectorFive[ii], stateVectorSix[ii]);
		outf << buffer;
	}
    outf.close();

    if (printOn) { std::cout << "Saving Complete. \n\n"; }
}

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- Printing Methods --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::print_iteration(double timeFinal, double* stateInitial) {
	// This message is not lined up with iteration since ti and statei are advanced before this but it's okay
    if (printOn) {
        day = (int) floor(time*SEC_TO_DAY);
        if (iteration == 0 || (day % 100 == 0 && day != checkDay) || time == timeFinal || eventTrigger) {
            if (iteration == 0) {
                std::cout << "Run Conditions: \n\n";
                std::cout << "Initial Time = " << 0.0 << "\n";
                std::cout << "Final Time =  " << timeFinal/86400.0 << " days \n";
                for (int ii = 0; ii < nStates; ++ii) {
                    if (ii == 0) {
                        std::cout << "Initial State = [";
                    }
                    std::cout << " " << stateInitial[ii] << " ";
                }
                std::cout << "]" << "\n";
                std::cout << "R = " << sqrt(stateInitial[0]*stateInitial[0] + stateInitial[1]*stateInitial[1] + stateInitial[2]*stateInitial[2]) << " km \n";
                std::cout << "V = " << sqrt(stateInitial[3]*stateInitial[3] + stateInitial[4]*stateInitial[4] + stateInitial[5]*stateInitial[5]) << " km/s \n\n";
                std::cout << "Integration Tolerance: " << relativeTolerance << "\n\n\n";
                std::cout << "Run:"<< "\n\n";
            }
            else {
                checkDay = day;

                std::cout << "Iteration: " << iteration+1 << "\n";
                std::cout << "time = " << time/86400.0 << " days \n";
                for (int ii = 0; ii < nStates; ++ii) {
                    if (ii == 0) {
                        std::cout << "state = [";
                    }
                    std::cout << " " << state[ii] << " ";
                }
                std::cout << "] \n";
                std::cout << "R = " << sqrt(state[0]*state[0] + state[1]*state[1] + state[2]*state[2]) << " km \n";
                std::cout << "V = " << sqrt(state[3]*state[3] + state[4]*state[4] + state[5]*state[5]) << " km/s \n\n";
            }
        }
        if (time == timeFinal) {
            std::cout << "Run Completed. \n\n";
        }
    }
}

void Integrator::print_performance() {
	if (printOn) {
		std::cout << "Number of Steps:                " << iteration << " iter \n";
		std::cout << "Number of Function Evaluations: " << functionEvaluations << " fval \n";

		double runtime{};
		if (timerOn) {
			runtime = ( (double) endClock - (double) startClock)/( (double) CLOCKS_PER_SEC);
			std::cout << "Runtime:                        " << runtime << " s \n";
		}

		std::cout <<   "\nAverage Function Evaluations per Step:   " << (double)functionEvaluations/(double)iteration << " fval/iter \n";

		if (timerOn) {
			std::cout << "Average Runtime per Step:                " << runtime/(double)iteration << " s/iter \n";
			std::cout << "Average Runtime per Function Evaluation: " << runtime/(double)functionEvaluations << " s/fval \n\n";
		}
	}
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Vector Methods ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::reserve_space(int N) {
	timeVector.reserve(N);
	stateVectorOne.reserve(N);
	stateVectorTwo.reserve(N);
	stateVectorThree.reserve(N);
	stateVectorFour.reserve(N);
	stateVectorFive.reserve(N);
	stateVectorSix.reserve(N);
}

void Integrator::store_iteration() {
	timeVector.push_back(time);
	stateVectorOne.push_back(state[0]);
	stateVectorTwo.push_back(state[1]);
	stateVectorThree.push_back(state[2]);
	stateVectorFour.push_back(state[3]);
	stateVectorFive.push_back(state[4]);
	stateVectorSix.push_back(state[5]);
}

void Integrator::cleanup() {
    timeVector.clear();
    stateVectorOne.clear();
    stateVectorTwo.clear();
    stateVectorThree.clear();
    stateVectorFour.clear();
    stateVectorFive.clear();
    stateVectorSix.clear();
}

void Integrator::copy_final_state(double* state) {
    state[0] = stateVectorOne.back();
    state[1] = stateVectorTwo.back();
    state[2] = stateVectorThree.back();
    state[3] = stateVectorFour.back();
    state[4] = stateVectorFive.back();
    state[5] = stateVectorSix.back();
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Event Function ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void Integrator::check_event() {
    // Have equations of motion class check if object crashed
    // Should allow user to input pointer to custom event function
    eventTrigger = equationsOfMotion->check_crash(state);

    // Break if hit nans or infs
    if (std::isinf(abs(time)) || std::isnan(abs(time))) {
        eventTrigger = true;
    }
    else {
        for (int ii = 0; ii < nStates; ++ii) {
            if (std::isinf(abs(state[ii])) || std::isnan(abs(state[ii]))) {
                eventTrigger = true;
            }
        }
    }
}



// Integrator Properties
void Integrator::set_abs_tol(double absTol) {
    absoluteTolerance = absTol;
}
void Integrator::set_rel_tol(double relTol) {
    relativeTolerance = relTol;
}
void Integrator::set_max_iter(int itMax) {
    iterMax = itMax;
}

void Integrator::switch_print(bool onOff) {
    printOn = onOff;
}
void Integrator::switch_timer(bool onOff) {
    timerOn = onOff;
}

void Integrator::set_initial_timestep(double dt0) {
    timeStepInitial = dt0;
}
void Integrator::switch_fixed_timestep(bool onOff) {
    useFixedStep = onOff;
}
void Integrator::switch_fixed_timestep(bool onOff, double fixedTimeStep) {
    useFixedStep = onOff;
    fixedTimeStep = fixedTimeStep;
}
void Integrator::set_timestep(double fixedTimeStep) {
    fixedTimeStep = fixedTimeStep;
}

void Integrator::set_step_method(std::string stepMethod) {
    Integrator::odeStepper stepper{};
    if      (stepMethod == "rk45" ) { stepper = Integrator::odeStepper::rk45; }
    else if (stepMethod == "rkf45") { stepper = Integrator::odeStepper::rkf45; }
    else if (stepMethod == "rkf78") { stepper = Integrator::odeStepper::rkf78; }
    else if (stepMethod == "dop45") { stepper = Integrator::odeStepper::dop45; }
    else if (stepMethod == "dop78") { stepper = Integrator::odeStepper::dop78; }
    else { 
        std::cout << "Warning: Unknown step method selected. No change applied. \n\n"; 
    }
    stepMethod = stepper;
}


// Integrator history getters
int Integrator::get_state_history_size() { return (int)timeVector.size(); }
void Integrator::get_state_history(double** stateHisotry) {
    // Copy to double array
    int sz = (int)timeVector.size();
    for (int ii = 0; ii < sz; ++ii) {
        stateHisotry[ii][0] = timeVector[ii];
        stateHisotry[ii][1] = stateVectorOne[ii];
        stateHisotry[ii][2] = stateVectorTwo[ii];
        stateHisotry[ii][3] = stateVectorThree[ii];
        stateHisotry[ii][4] = stateVectorFour[ii];
        stateHisotry[ii][5] = stateVectorFive[ii];
        stateHisotry[ii][6] = stateVectorSix[ii];
    }
}