
#pragma once

#include <iostream>
#include <math.h>
#include <cmath>

#include "math_constants.h"
#include "astronomical_constants.h"

class LambertSolver
{
private:
    // Private members
    double r0[3] = {}, v0[3] = {}, R0{}, V0{},
           rf[3] = {}, vf[3] = {}, Rf{},
           sqMU{}, r0v0_sqMU{},
           dtheta{}, A{},
           alpha{}, Xn{}, X{}, X2{},
           z{}, zn{}, y{},
           Cz{}, Sz{}, sqz{}, sqnz{},
           F{}, dF{},
           f{}, g{}, fdot{}, gdot{},
           err{}, divG{};

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

