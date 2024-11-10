
#pragma once

#ifndef SWIG
    #include <cmath>
    #include <array>
#endif

#include "math_constants.h"

namespace math_c
{
    //------------------------------------------------- Norms --------------------------------------------------//
    // Default vector norm
    template<typename T, size_t Size>
    T normalize(const std::array<T, Size>& array, const double p, const size_t idx0, const size_t idxf) {
        T norm = 0.0;
        for (size_t ii = idx0; ii < idxf; ++ii) {
            norm += pow(array[ii], p);
        }
        return (T)pow(norm, 1.0/p);
    }

    template<typename T, size_t Size>
    T normalize(const std::array<T, Size>& array, const double p) {
        return normalize(array, p, size_t(0), Size);
    }

    double normalize(const double* vec);

    double normalize(double* vec, int startIndex, int endIndex);

    // Vector p-norm
    double normalize(double* vec, int startIndex, int endIndex, int p);

    // Default matrix norm
    double normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn);

    // Matrix p-norm
    double normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn, int p);

    //----------------------------------------- Vector and Matrix Math -----------------------------------------//

    double array_mean(double* vec, int arraySize);

    //----------------------------------------- Miscallaneous Functions ----------------------------------------//
    double atan3(double a, double b);
};

