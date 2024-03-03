
#include "LambertSolver.hpp"

// Constructor and destructor
LambertSolver::LambertSolver(){}
LambertSolver::~LambertSolver(){}

// r and v Lambert solver
void LambertSolver::solve_rv(double* state0, double dt, double mu, double* statef) {

    // Parse initial state
    for (int ii = 0; ii < 3; ++ii) {
        r0[ii] = state0[ii];
        v0[ii] = state0[ii+3];
    }

    // Constants
    R0 = normalize(r0);
    V0 = normalize(v0);

    sqMU = sqrt(mu);
    r0v0_sqMU = (r0[0]*v0[0] + r0[1]*v0[1] + r0[2]*v0[2])/sqMU;

    // Find X
    alpha = 2/R0 - V0*V0/mu;
    Xn = sqMU*dt*abs(alpha);

    // Universal Variable loop
    it = 0;
    err = 1;
    while (err > tol && it < 1000) {
        // Reset
        X = Xn;

        // Precalculate
        X2 = X*X;
        z = X2*alpha;

        // Evaluate Stumpff Functions
        evaluate_stumpff();

        // Newton Functions
        F = r0v0_sqMU*X2*Cz + (1 - alpha*R0)*X*X2*Sz + R0*X - sqMU*dt;
        dF = r0v0_sqMU*X*(1 - alpha*X2*Sz) + (1 - alpha*R0)*X2*Cz + R0;

        // Step
        Xn = X - F/dF;

        err = abs((Xn - X)/X);
        ++it;
    }

    // Find r
    f = 1 - X2/R0*Cz;
    g = dt - 1/sqMU*X2*X*Sz;

    rf[0] = f*r0[0] + g*v0[0];
    rf[1] = f*r0[1] + g*v0[1];
    rf[2] = f*r0[2] + g*v0[2];
    Rf = normalize(rf);

    // Find v
    fdot = sqMU/(Rf*R0)*X*(z*Sz - 1);
    gdot = 1 - X2/Rf*Cz;

    vf[0] = fdot*r0[0] + gdot*v0[0];
    vf[1] = fdot*r0[1] + gdot*v0[1];
    vf[2] = fdot*r0[2] + gdot*v0[2];

    // Store results
    for (int ii = 0; ii < 3; ++ii) {
        statef[ii] = rf[ii];
        statef[ii+3] = vf[ii];
    }
}

// modified r and v Lambert solver
void LambertSolver::solve_rv(double* state0, double dt, double* statef) {

    // Parse initial state
    for (int ii = 0; ii < 3; ++ii) {
        r0[ii] = state0[ii];
        v0[ii] = state0[ii+3];
    }

    // Constants
    R0 = normalize(r0);
    V0 = normalize(v0);

    r0v0_sqMU = (r0[0]*v0[0] + r0[1]*v0[1] + r0[2]*v0[2]);

    // Find X
    alpha = 2.0/R0 - V0*V0;
    Xn = dt*abs(alpha);

    // Universal Variable loop
    it = 0;
    err = 1.0;
    while (err > tol && it < 1000) {
        // Reset
        X = Xn;

        // Precalculate
        X2 = X*X;
        z = X2*alpha;

        // Evaluate Stumpff Functions
        evaluate_stumpff();

        // Newton Functions
        F = r0v0_sqMU*X2*Cz + (1.0 - alpha*R0)*X*X2*Sz + R0*X - dt;
        dF = r0v0_sqMU*X*(1.0 - alpha*X2*Sz) + (1.0 - alpha*R0)*X2*Cz + R0;

        // Step
        Xn = X - F/dF;

        err = abs((Xn - X)/X);
        ++it;
    }

    // Find r
    f = 1.0 - X2/R0*Cz;
    g = dt - X2*X*Sz;

    rf[0] = f*r0[0] + g*v0[0];
    rf[1] = f*r0[1] + g*v0[1];
    rf[2] = f*r0[2] + g*v0[2];
    Rf = normalize(rf);

    // Find v
    fdot = 1.0/(Rf*R0)*X*(z*Sz - 1.0);
    gdot = 1.0 - X2/Rf*Cz;

    vf[0] = fdot*r0[0] + gdot*v0[0];
    vf[1] = fdot*r0[1] + gdot*v0[1];
    vf[2] = fdot*r0[2] + gdot*v0[2];

    // Store results
    for (int ii = 0; ii < 3; ++ii) {
        statef[ii] = rf[ii];
        statef[ii+3] = vf[ii];
    }
}

// r and r Lambert solver
void LambertSolver::solve_rr(double* r0, double* rf, double dt, double mu, int I, double* v0, double* vf) {
    // Constants
    R0 = normalize(r0);
    Rf = normalize(rf);

    sqMU = sqrt(mu);

    // Change in TA
    dtheta = acos((r0[0]*rf[0] + r0[1]*rf[1] + r0[2]*rf[2])/(R0*Rf));

    if (r0[0]*rf[1] - r0[1]*rf[0] >= 0){
        if (I == -1) { // Retrograde
            dtheta = 2.0*PI - dtheta;
        }
    }
    else {
        if (I == 1) { // Prograde
            dtheta = 2.0*PI - dtheta;
        }
    }

    A = sin(dtheta)*sqrt(R0*Rf/(1 - cos(dtheta)));

    // Find z
    zn = 0.0;
    it = 0;
    err = 1.0;
    while (err > tol && it < itMax){
        // Reset
        z = zn;

        // Evaluate Stumpff Functions
        evaluate_stumpff();
        y = R0 + Rf + A*(z*Sz - 1.0)/sqrt(Cz);

        // Newton Functions
        F = pow(y/Cz, 1.5)*Sz + A*sqrt(y) - sqMU*dt;
        if (z == 0.0){
            dF = sqrt(2.0)/40.0*pow(y, 1.5) + A/8*(sqrt(y) + A*sqrt(1.0/(2.0*y)));
        }
        else{
            dF = pow(y/Cz, 1.5)*(1.0/(2.0*z)*(Cz - 3.0*Sz/(2.0*Cz)) + 3.0*Sz*Sz/(4.0*Cz)) + A/8.0*(3.0*Sz/Cz*sqrt(y) + A*sqrt(Cz/y));
        }

        // Step
        zn = z - F/dF;

        err = abs((zn - z)/z);
        it += 1;
    }

    // Recalculate for final values
    evaluate_stumpff();
    y = R0 + Rf + A*(z*Sz - 1.0)/sqrt(Cz);

    // f and g functions
    f = 1.0 - y/R0;
    g = A*sqrt(y)/sqMU;

    gdot = 1.0 - y/Rf;

    // v1 and v2
    divG = 1.0/g;

    v0[0] = divG*(rf[0] - f*r0[0]);
    v0[1] = divG*(rf[1] - f*r0[1]);
    v0[2] = divG*(rf[2] - f*r0[2]);

    vf[0] = divG*(gdot*rf[0] - r0[0]);
    vf[1] = divG*(gdot*rf[1] - r0[1]);
    vf[2] = divG*(gdot*rf[2] - r0[2]);
}

// Helpful methods
void LambertSolver::evaluate_stumpff() {
    if (z > 0.0) {
        sqz = sqrt(z);
        Cz = (1.0 - cos(sqz))/z;
        Sz = (sqz - sin(sqz))/(sqz*sqz*sqz);
    }
    else if (z < 0.0) {
        sqnz = sqrt(-z);
        Cz = (1.0 - cosh(sqnz))/z;
        Sz = (sinh(sqnz) - sqnz)/(sqnz*sqnz*sqnz);
    }
    else {
        Cz = 0.5;
        Sz = 1.0/6.0;
    }
}

double LambertSolver::normalize(double* vec) {
    return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}