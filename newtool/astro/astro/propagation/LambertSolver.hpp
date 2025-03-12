
#pragma once

#ifndef SWIG
    #include <iostream>
    #include <math.h>
    #include <cmath>
#endif

#include <astro/constants/astronomical_constants.h>

class LambertSolver
{
private:
    // Private members
    double r0[3] = {};
    double v0[3] = {};
    double R0{};
    double V0{};
    double rf[3] = {};
    double vf[3] = {};
    double Rf{};
    double sqMU{};
    double r0v0_sqMU{};
    double dtheta{};
    double A{};
    double alpha{};
    double Xn{};
    double X{};
    double X2{};
    double z{};
    double zn{};
    double y{};
    double Cz{};
    double Sz{};
    double sqz{};
    double sqnz{};
    double F{};
    double dF{};
    double f{};
    double g{};
    double fdot{};
    double gdot{};
    double err{};
    double divG{};

    int it = 0;

    // Private methods
    void evaluate_stumpff();
    double normalize(double* vec);
public:
    LambertSolver();
    ~LambertSolver();

    // Members
    int itMax = 1000;
    double tol = 1.0e-12;

    // Methods
    void solve_rv(double* state0, double dt, double mu, double* statef); // Starts with r and v and outputs r and v after dt
    void solve_rv(double* state0, double dt, double* statef); // Starts with r and v and outputs r and v after dt modified to assume mu = 1

    void solve_rr(double* r0, double* rf, double dt, double mu, int I, double* v0, double* vf); // Starts with r and r and ouputs v and v for the given dt
};

