
#pragma once

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

