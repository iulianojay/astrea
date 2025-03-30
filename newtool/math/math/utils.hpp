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

template <typename T>
T mean(std::vector<T> vec)
{
    T mean = 0.0;
    for (const auto& x : vec) {
        mean += x;
    }
    return mean / (static_cast<T>(vec.size()));
}

template <typename T>
T atan3(T a, T b)
{
    T sa{}, sb{};
    if (a >= 0) { sa = 1; }
    else {
        sa = -1;
    }
    if (b >= 0) { sb = 1; }
    else {
        sb = -1;
    }

    static constexpr T PI_T = static_cast<T>(M_PI);
    if (std::abs(a) < 1e-10) { return (1 - sb) * PI_T / 2.0; }
    else if (std::abs(b) < 1e-10) {
        return (2.0 - sa) * PI_T / 2.0;
    }
    else {
        return (2.0 - sa) * PI_T / 2 + sa * sb * (std::abs(std::atan(a / b)) - PI_T / 2.0);
    }
}

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
