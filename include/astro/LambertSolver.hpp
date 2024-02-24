/*
    This file is part of the Orbital Operations Propagation Suite.

    The Orbital Operations Propagation Suite is a high precision 6DoF orbital
    propagation interface for Maltab. Copyright (C) 2018, Jay Iuliano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.

    iuliano.jay@gmail.com
*/

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

