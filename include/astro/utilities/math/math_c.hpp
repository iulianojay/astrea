
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
            norm += std::pow(array[ii], p);
        }
        return (T)std::pow(norm, 1.0/p);
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

    // These two implementations were taken from here:
    // https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
    template<typename T>
    inline T cos(T x) noexcept
    {
        return std::cos(x);
        // constexpr T tp = 1./(2.*M_PI);
        // x *= tp;
        // x -= T(.25) + std::floor(x + T(.25));
        // x *= T(16.) * (std::abs(x) - T(.5));
        // x += T(.225) * x * (std::abs(x) - T(1.));
        // return x;
    }

    template<typename T>
    inline T sin(T x) noexcept
    {
        return std::sin(x);
        // constexpr T B = 4./M_PI;
        // constexpr T C = -4./(M_PI*M_PI);
        // x = B * x + C * x * std::abs(x);
        // x = T(0.225) * (x * std::abs(x) - x) + x;   // Q * y + P * y * abs(y)
        // return x;
    }

    //TODO: Add similar fast approximations for sqrt, asin, acos, and other commonly used functions
};

