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

#include "math_c.hpp"

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------- Norms --------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Default vector norm
double math_c::normalize(double* vec) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = 0; ii < 3; ++ii) {
        norm += vec[ii]*vec[ii];
    }

    return sqrt(norm);
}

double math_c::normalize(double* vec, int startIndex, int endIndex) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = startIndex; ii < endIndex+1; ++ii) {
        norm += vec[ii]*vec[ii];
    }

    return sqrt(norm);
}

// Vector p-norm
double math_c::normalize(double* vec, int startIndex, int endIndex, int p) {
    if (p <= 0) {
        std::cout << "Error: p must be >= 1 \n\n";
        return -1.0;
    }

    // p norm
    double norm = 0.0;
    for (int ii = startIndex; ii < endIndex+1; ++ii) {
        norm += pow(abs(vec[ii]),p);
    }
    return pow(norm, 1/p);
}

// Default matrix norm
double math_c::normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = startRow; ii < endRow+1; ++ii) {
        for (int jj = startColumn; jj < endColumn+1; ++jj){
            norm += matrix[ii][jj]*matrix[ii][jj];
        }
    }

    return sqrt(norm);
}

// Matrix p-norm
double math_c::normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn, int p) {
    if (p <= 0) {
        std::cout << "Error: p must be >= 1 \n\n";
        return -1.0;
    }

    // p norm
    double norm = 0.0;
    for (int ii = startRow; ii < endRow+1; ++ii) {
        for (int jj = startColumn; jj < endColumn+1; ++jj) {
            norm += pow(abs(matrix[ii][jj]),p);
        }
    }
    return pow(norm, 1/p);
}

//----------------------------------------------------------------------------------------------------------//
//---------------------------------------------- Spline Class ----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

math_c::Spline::Spline() {}
math_c::Spline::~Spline() {}

// Cubic Spline
/*
    x is the input knot vector with corresponding points y
    sx is the desired output vector to interpolate to
    n is the number of knots
    m is the number of knots to interpolat to

    sy is the output spline values at sx
*/
void math_c::Spline::cubic_spline(double* x, double* y, double* sx, const int n, const int m, double* sy) {

    // Size arrays
    size_arrays(n);

    // Catch spline x values outside the knots
    for (int ii = 0; ii < m; ++ii) {
        if (sx[ii] < x[0] || sx[ii] > x[n-1]) {
            std::cout << "Error: Requested spline values outside of input knots. Exiting... \n\n";
            return;
        }
    }

    // Solve for spline coefficients
    for (int ii = 0; ii < n-1; ++ii) {
        h[ii] = x[ii+1] - x[ii];
        b[ii] = 6*(y[ii+1] - y[ii])/h[ii];
    }

    u[1] = 2*(h[0] + h[1]);
    v[1] = b[1] - b[0];
    for (int ii = 1; ii < n-1; ++ii) {
        u[ii+1] = 2*(h[ii+1] + h[ii]) - h[ii]*h[ii]/u[ii];
        v[ii+1] = b[ii+1] - b[ii] - h[ii]*v[ii]/u[ii];
    }

    for (int ii = n-2; ii > -1; --ii) {
        z[ii+1] = (v[ii+1] - h[ii+1]*z[ii+2])/u[ii+1];
    }

    // Create spline
    for (int ii = 0; ii < m; ++ii) {
        // Find nearest knot
        int jj = 0;
        xRef = x[0];
        for (int kk = 1; kk < n; ++kk) {
            if (abs(sx[ii] - x[kk]) < abs(sx[ii] - xRef) && x[kk] < sx[ii]) {
                jj = kk;
                xRef = x[kk];
            }
        }
        // Calculate variables once
        dx = sx[ii] - x[jj];
        dxp1 = x[jj+1] - sx[ii];

        zDiv6 = z[jj]/6;
        zp1Div6 = z[jj+1]/6;
        h2 = h[jj]*h[jj];

        // Spline
        sy[ii] = (zDiv6*pow(dxp1,3) + zp1Div6*pow(dx,3) + (y[jj+1] - zp1Div6*h2)*dx + (y[jj] - h2*zDiv6)*dxp1)/h[jj];
    }

    // Clean up
    clear_arrays();
}

void math_c::Spline::size_arrays(const int n) {
    h = new double[n-1]();
    b = new double[n-1]();
    u = new double[n]();
    v = new double[n]();
    z = new double[n+1]();
}

void math_c::Spline::clear_arrays() {
    delete[] h;
    delete[] b;
    delete[] u;
    delete[] v;
    delete[] z;
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------- Vector and Matrix Math -----------------------------------------//
//----------------------------------------------------------------------------------------------------------//
template<typename T>
void math_c::copy_array(T* copythis, T* intothis, int arraySize) {
    for (int ii = 0; ii < arraySize; ii++) {
        intothis[ii] = copythis[ii];
    }
}

template<typename T>
void math_c::copy_matrix(T** copythis, T** intothis, int nRows, int nColumns) {
    for (int ii = 0; ii < nRows; ii++) {
        for (int jj = 0; jj < nColumns; jj++) {
            intothis[ii][jj] = copythis[ii][jj];
        }
    }
}

double math_c::array_mean(double* vec, int arraySize) {
    double mean = 0.0;
    for (int ii = 0; ii < arraySize; ii++) {
        mean += vec[ii];
    }
    return mean/((double)arraySize);
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------- Miscallaneous Functions ----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double math_c::atan3(double a, double b) {

    double sa{}, sb{};

    if (a >= 0) { sa =  1; }
    else        { sa = -1; }
    if (b >= 0) { sb =  1; }
    else        { sb = -1; }

    if (abs(a) < 1e-10) {
        return (1 - sb)*PI/2;
    }
    else if (abs(b) < 1e-10) {
        return (2 - sa)*PI/2;
    }
    else {
        return (2 - sa)*PI/2 + sa*sb*(abs(atan(a/b)) - PI/2);
    }
}
