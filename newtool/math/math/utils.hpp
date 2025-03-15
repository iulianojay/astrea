#pragma once

#ifndef SWIG
#include <array>
#include <cmath>
#include <vector>
#endif

namespace math {

template <typename T, size_t Size>
T normalize(std::array<T, Size> array, double p = 2)
{
    T norm = 0.0;
    for (size_t ii = 0; ii < Size; ++ii) {
        norm += std::pow(array[ii], p);
    }
    return (T)std::pow(norm, 1.0 / p);
}

template <typename T>
T normalize(std::vector<T> vector, double p = 2)
{
    T norm = 0.0;
    for (size_t ii = 0; ii < vector.size(); ++ii) {
        norm += std::pow(vector[ii], p);
    }
    return (T)std::pow(norm, 1.0 / p);
}

double array_mean(double* vec, int arraySize);

double atan3(double a, double b);

// These two implementations were taken from here:
// https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
template <typename T>
inline T cos(T x) noexcept
{
    constexpr T tp = 1. / (2. * M_PI);
    x *= tp;
    x -= T(.25) + std::floor(x + T(.25));
    x *= T(16.) * (std::abs(x) - T(.5));
    x += T(.225) * x * (std::abs(x) - T(1.));
    return x;
}

template <typename T>
inline T sin(T x) noexcept
{
    constexpr T B = 4. / M_PI;
    constexpr T C = -4. / (M_PI * M_PI);
    x             = B * x + C * x * std::abs(x);
    x             = T(0.225) * (x * std::abs(x) - x) + x; // Q * y + P * y * abs(y)
    return x;
}

// TODO: Add similar fast approximations for sqrt, asin, acos, and other commonly used functions

} // namespace math
