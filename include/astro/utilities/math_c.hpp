/*
    This file is part of the Iuliano Orbital Propagation Suite

    The Orbital Propagation Suite is a high precision orbital propagation toolset
    Copyright(C) 2018, Jay Iuliano

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

#include "math_constants.h"

namespace math_c
{
    //------------------------------------------------- Norms --------------------------------------------------//
    // Default vector norm
    double normalize(double* vec);
    double normalize(double* vec, int startIndex, int endIndex);

    // Vector p-norm
    double normalize(double* vec, int startIndex, int endIndex, int p);

    // Default matrix norm
    double normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn);

    // Matrix p-norm
    double normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn, int p);

    //---------------------------------------------- Spline Class ----------------------------------------------//
    class Spline
    {
    private:
        double* h{};
        double* b{};
        double* u{};
        double* v{};
        double* z{};
        double xRef{}, dx{}, dxp1{}, zDiv6{}, zp1Div6{}, h2{};

        void size_arrays(const int n);
        void clear_arrays();
    public:
        // Methods
        Spline();
        ~Spline();

        void cubic_spline(double* x, double* y, double* sx, const int n, const int m, double* sy);
    };

    //----------------------------------------- Vector and Matrix Math -----------------------------------------//
    template<typename T>
    void copy_array(T* copythis, T* intothis, int arraySize);
    
    template<typename T>
    void copy_matrix(T** copythis, T** intothis, int nRows, int nColumns);

    double array_mean(double* vec, int arraySize);

    //----------------------------------------- Miscallaneous Functions ----------------------------------------//
    double atan3(double a, double b);
};

