
#include "Spacecraft.hpp"

// Constructor/Destructor
Spacecraft::Spacecraft() : integrator(), centralBody(), lambertSolver() { }
Spacecraft::~Spacecraft() { }

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ Setters -------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Spacecraft Properties
void Spacecraft::set_mass(double m) {
    mass = m;
    integrator.equationsOfMotion.mass = m;
}
void Spacecraft::set_coefficient_of_drag(double Cd) {
    coefficientOfDrag = Cd;
    integrator.equationsOfMotion.coefficientOfDrag = Cd;
}
void Spacecraft::set_coefficient_of_lift(double Cl) {
    coefficientOfLift = Cl;
    integrator.equationsOfMotion.coefficientOfLift = Cl;
}
void Spacecraft::coefficient_of_reflectivity(double Cr) {
    coefficientOfReflectivity = Cr;
    integrator.equationsOfMotion.coefficientOfReflectivity = Cr;
}

void Spacecraft::set_ram_area(double aRam) {
    areaRam[0] = aRam;
    integrator.equationsOfMotion.areaRam[0] = aRam*M_TO_KM*M_TO_KM; // store in EoM as km^2
}
void Spacecraft::set_ram_area(double* aRam) {
    for (int ii = 0; ii < 3; ++ii) {
        areaRam[ii] = aRam[ii];
        integrator.equationsOfMotion.areaRam[ii] = aRam[ii]*M_TO_KM*M_TO_KM; // store in EoM as km^2
    }
}

void Spacecraft::set_sun_area(double aSun) {
    areaSun[0] = aSun;
    integrator.equationsOfMotion.areaSun[0] = aSun*M_TO_KM*M_TO_KM; // store in EoM as km^2
}
void Spacecraft::set_sun_area(double* aSun) {
    for (int ii = 0; ii < 3; ++ii) {
        areaSun[ii] = aSun[ii];
        integrator.equationsOfMotion.areaSun[ii] = aSun[ii]*M_TO_KM*M_TO_KM; // store in EoM as km^2
    }
}

void Spacecraft::set_lift_area(double aLift) {
    areaLift[0] = aLift;
    integrator.equationsOfMotion.areaLift[0] = aLift*M_TO_KM*M_TO_KM; // store in EoM as km^2
}
void Spacecraft::set_lift_area(double* aLift) {
    for (int ii = 0; ii < 3; ++ii) {
        areaLift[ii] = aLift[ii];
        integrator.equationsOfMotion.areaLift[ii] = aLift[ii]*M_TO_KM*M_TO_KM; // store in EoM as km^2
    }
}

void Spacecraft::set_epoch(std::string inputEpoch) {
    // Update spacecraft
    epoch = inputEpoch;
    epochJulianDate = convert::epoch_to_julian_date(inputEpoch);

    // Update central Body
    double jdTemp = epochJulianDate;
    centralBody.set_dates(&jdTemp, 1);

    // Update EOMs
    integrator.equationsOfMotion.epoch = inputEpoch;
    integrator.equationsOfMotion.assign_eom_properties(centralBody);
}

// Integrator Properties
void Spacecraft::set_abs_tol(double absTol) {
    integrator.absoluteTolerance = absTol;
}
void Spacecraft::set_rel_tol(double relTol) {
    integrator.relativeTolerance = relTol;
}
void Spacecraft::set_max_iter(int itMax) {
    integrator.iterMax = itMax;
}

void Spacecraft::switch_print(bool onOff) {
    integrator.printOn = onOff;
}
void Spacecraft::switch_timer(bool onOff) {
    integrator.timerOn = onOff;
}

void Spacecraft::switch_custom_eom(bool onOff) {
    integrator.customEOM = onOff;
}

void Spacecraft::set_initial_timestep(double dt0) {
    integrator.timeStepInitial = dt0;
}
void Spacecraft::switch_fixed_timestep(bool onOff) {
    integrator.useFixedStep = onOff;
}
void Spacecraft::switch_fixed_timestep(bool onOff, double fixedTimeStep) {
    integrator.useFixedStep = onOff;
    integrator.fixedTimeStep = fixedTimeStep;
}
void Spacecraft::set_timestep(double fixedTimeStep) {
    integrator.fixedTimeStep = fixedTimeStep;
}

void Spacecraft::set_step_method(std::string stepMethod) {
    Integrator::odeStepper stepper{};
    if      (stepMethod == "rk45" ) { stepper = Integrator::odeStepper::rk45; }
    else if (stepMethod == "rkf45") { stepper = Integrator::odeStepper::rkf45; }
    else if (stepMethod == "rkf78") { stepper = Integrator::odeStepper::rkf78; }
    else if (stepMethod == "dop45") { stepper = Integrator::odeStepper::dop45; }
    else if (stepMethod == "dop78") { stepper = Integrator::odeStepper::dop78; }
    else { 
        std::cout << "Warning: Unknown step method selected. No change applied. \n\n"; 
    }
    integrator.stepMethod = stepper;
}

// Perturbation toggles
void Spacecraft::switch_oblateness(bool onOff) {
    integrator.equationsOfMotion.oblateness = onOff;
}
void Spacecraft::switch_oblateness(int N, int M) {
    // Switch perturbation toggle to true
    integrator.equationsOfMotion.oblateness = true;
    integrator.equationsOfMotion.NxMOblateness = true;

    // Set N and M
    integrator.equationsOfMotion.N = N;
    integrator.equationsOfMotion.M = M;

    // Get Cnm and Snm
    integrator.equationsOfMotion.get_oblateness_coefficients(N, M);
}
void Spacecraft::switch_drag(bool onOff) {
    integrator.equationsOfMotion.drag = onOff;
}
void Spacecraft::switch_lift(bool onOff) {
    integrator.equationsOfMotion.lift = onOff;
}
void Spacecraft::switch_srp(bool onOff) {
    integrator.equationsOfMotion.srp = onOff;
}
void Spacecraft::switch_nbody(bool onOff) {
    integrator.equationsOfMotion.nbody = onOff;
}


// Set equations of motion
void Spacecraft::switch_dynamics(std::string dynamics) {
    // Turn all off
    integrator.equationsOfMotion.twoBody = false;
    integrator.equationsOfMotion.cowellsMethod = false;
    integrator.equationsOfMotion.coesVoP = false;
    integrator.equationsOfMotion.j2MeanVoP = false;
    integrator.equationsOfMotion.meesVoP = false;

    // Turn selected on
    if (dynamics == "Two Body" || dynamics == "two body"){
        integrator.equationsOfMotion.twoBody = true;
    }
    else if (dynamics == "Cowells Method" || dynamics == "cowells method") {
        integrator.equationsOfMotion.cowellsMethod = true;
    }
    else if (dynamics == "COEs VoP" || dynamics == "coes vop") {
        integrator.equationsOfMotion.coesVoP = true;
    }
    else if (dynamics == "J2 Mean VoP" || dynamics == "j2 mean vop") {
        integrator.equationsOfMotion.j2MeanVoP = true;
    }
    else if (dynamics == "MEEs VoP" || dynamics == "mees vop") {
        integrator.equationsOfMotion.meesVoP = true;
    }
    else {
        std::cout << "Error: Selected dynamics set not recognized. \n\n";
    }
}

// Central Body stuff
void Spacecraft::set_mu(double mu) {
    integrator.equationsOfMotion.mu = mu;
}
void Spacecraft::set_central_body(std::string name) {
    centralBody.assign_properties(name);

    integrator.equationsOfMotion.assign_eom_properties(centralBody);
    integrator.equationsOfMotion.mu = centralBody.mu();
}
void Spacecraft::set_n_bodies(std::string* bodyNames, int numberOfBodies) {
    // Pass data to central body
    centralBody.numberOfNBodies = numberOfBodies;
    for (int ii = 0; ii < numberOfBodies; ++ii) {
        centralBody.nBodyNames[ii] = bodyNames[ii];
    }

    integrator.equationsOfMotion.assign_eom_properties(centralBody);
}
void Spacecraft::set_crash_radius(double crashRadius) {
    integrator.equationsOfMotion.crashRadius = crashRadius;
}
void Spacecraft::set_crash_velocity(double crashVelocity) {
    integrator.equationsOfMotion.crashVelocity = crashVelocity;
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ Getters -------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Spacecraft Property Getters
double  Spacecraft::get_mass()                        { return mass; }
double  Spacecraft::get_coefficient_of_drag()         { return coefficientOfDrag; }
double  Spacecraft::get_coefficient_of_lift()         { return coefficientOfLift; }
double  Spacecraft::get_coefficient_of_reflectivity() { return coefficientOfReflectivity; }
double* Spacecraft::get_ram_area()                    { return areaRam; }
double* Spacecraft::get_sun_area()                    { return areaSun; }
double* Spacecraft::get_lift_area()                   { return areaLift; }

// Integrator property getters
int Spacecraft::get_state_history_size() { return (int)integrator.timeVector.size(); }
void Spacecraft::get_state_history(double** stateHisotry) {
    // Copy to double array
    int sz = (int)integrator.timeVector.size();
    for (int ii = 0; ii < sz; ++ii) {
        stateHisotry[ii][0] = integrator.timeVector[ii];
        stateHisotry[ii][1] = integrator.stateVectorOne[ii];
        stateHisotry[ii][2] = integrator.stateVectorTwo[ii];
        stateHisotry[ii][3] = integrator.stateVectorThree[ii];
        stateHisotry[ii][4] = integrator.stateVectorFour[ii];
        stateHisotry[ii][5] = integrator.stateVectorFive[ii];
        stateHisotry[ii][6] = integrator.stateVectorSix[ii];
    }
}
void Spacecraft::get_final_state(double* state) { integrator.copy_final_state(state); }

// Central Body getter
double Spacecraft::get_mu() { return integrator.equationsOfMotion.mu; }

//----------------------------------------------------------------------------------------------------------//
//---------------------------------------------- Integration -----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Integration
void Spacecraft::integrate(double timeInitial, double timeFinal, double* stateInitial) {
    // Find julian dates
    int N = (int)ceil(abs(timeFinal - timeInitial)/86400);
    double* julianDate = new double[N];
    for (int ii = 0; ii < N; ++ii) {
        julianDate[ii] = epochJulianDate + (double) ii;
    }

    // Set julian dates in central body
    centralBody.set_dates(julianDate, N);

    // Pass updates to EOMs
    integrator.equationsOfMotion.assign_eom_properties(centralBody);

    // Integrate
    integrator.integrate(timeInitial, timeFinal, stateInitial);

    // Clean up
    delete[] julianDate;
}

// Save
void Spacecraft::save() { integrator.save(); }
void Spacecraft::save(std::string filename) { integrator.save(filename); }

// Lambert Solver
void Spacecraft::lambert(double timeInitial, double timeFinal, double* state0, double* statef) {
    if (integrator.equationsOfMotion.mu != 1.0) {
        lambertSolver.solve_rv(state0, timeFinal-timeInitial, integrator.equationsOfMotion.mu, statef);
    }
    else {
        lambertSolver.solve_rv(state0, timeFinal-timeInitial, statef);
    }
}
