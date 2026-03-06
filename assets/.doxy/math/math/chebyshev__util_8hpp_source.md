

# File chebyshev\_util.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**math**](dir_450de47f4bf9646ba641743528a4ea64.md) **>** [**math**](dir_b2ecf34ed687fe8e79818a2ecae6cd69.md) **>** [**chebyshev\_util.hpp**](chebyshev__util_8hpp.md)

[Go to the documentation of this file](chebyshev__util_8hpp.md)


```C++

#pragma once

#include <array>
#include <stdexcept>

namespace astrea {
namespace math {

double transform_from_chebyshev_range(const double& x, const double& lb, const double& ub);

double transform_to_chebyshev_range(const double& x, const double& lb, const double& ub);

template <std::size_t N>
double evaluate_chebyshev_polynomial(
    const double& x,
    const double& lb,
    const double& ub,
    const std::array<double, N>& coeff,
    const double& coeffZeroFactor  = 0.5,
    const double& extrapolationTol = 1.0e-6
)
{
    // Error checking
    static_assert(N > 2, "evaluate_chebyshev_polynomial() - Size of coeff vector must be greater than zero.");
    if (x < lb && std::abs(x - lb) > extrapolationTol) {
        throw std::invalid_argument(
            "evaluate_chebyshev_polynomial() - Value provided for x is outside of the lower bound for the "
            "interpolant."
        );
    }
    else if (x > ub && std::abs(x - ub) > extrapolationTol) {
        throw std::invalid_argument(
            "evaluate_chebyshev_polynomial() - Value provided for x is outside of the upper bound for the "
            "interpolant."
        );
    }

    // Set the order or degree of the Chebyshev polynomial
    const std::size_t order = N - 1;

    // Perform change of variables
    const double y  = transform_to_chebyshev_range(x, lb, ub);
    const double y2 = 2.0 * y;

    // Apply Clenshaw's recurrence formula in reverse to preserve small numbers
    double d = 0.0, dd = 0.0, sv = 0.0;
    for (std::size_t k = order; k >= 1; k--) {
        sv = d;
        d  = y2 * d - dd + coeff[k];
        dd = sv;
    }

    // To be compatible with CSpice, don't multiply coeff[0] by 0.5
    return y * d - dd + coeffZeroFactor * coeff[0];
}

template <std::size_t N>
double evaluate_chebyshev_polynomial(const double& x, const std::array<double, N>& boundsCoeff, const double& coeffZeroFactor = 0.5, const double& extrapolationTol = 1.0e-6)
{
    // Error Checking
    static_assert(N > 2, "evaluate_chebyshev_polynomial() - Size of boundsCoeff array must be greater than or equal to three.");

    // Extract lb, ub, and coefficients
    std::array<double, N - 2> coeff;
    for (std::size_t k = 0; k < N - 2; k++) {
        coeff[k] = boundsCoeff[k + 2];
    }

    // Evaluate the Chebyshev polynomial
    return evaluate_chebyshev_polynomial(x, boundsCoeff[0], boundsCoeff[1], coeff, coeffZeroFactor, extrapolationTol);
}

template <size_t N>
double evaluate_chebyshev_derivative(double x, double lb, double ub, const std::array<double, N>& coeff, double extrapolationTol = 1.0e-6)
{
    // Error checking
    static_assert(N > 0, "evaluate_chebyshev_derivative() - Size of coeff array must be greater than zero.");
    if (x < lb && std::abs(x - lb) > extrapolationTol) {
        throw std::invalid_argument(
            "evaluate_chebyshev_derivative() - Value provided for x is outside of the lower bound for "
            "the interpolant."
        );
    }
    else if (x > ub && std::abs(x - ub) > extrapolationTol) {
        throw std::invalid_argument(
            "evaluate_chebyshev_derivative() - Value provided for x is outside of the upper bound for "
            "the interpolant."
        );
    }

    // Perform change of variables
    const double y  = transform_to_chebyshev_range(x, lb, ub);
    const double y2 = 2.0 * y;

    // Apply Clenshaw's recurrence formula in reverse to preserve small numbers
    double d = 0.0, dd = 0.0, sv = 0.0;
    double dp = 0.0, ddp = 0.0, svp = 0.0;

    for (std::size_t k = N - 1; k >= 1; k--) {
        // Compute the derivative coefficient values
        svp = dp;
        dp  = y2 * dp - ddp + 2.0 * d;
        ddp = svp;

        // Compute the coefficient values, which are required by the derivative
        sv = d;
        d  = y2 * d - dd + coeff[k];
        dd = sv;
    }

    // Normalize to the interval ub - lb
    return 2.0 / (ub - lb) * (y * dp - ddp + d);
}

template <size_t N>
double evaluate_chebyshev_derivative(double x, const std::array<double, N>& boundsCoeff, double extrapolationTol = 1.0e-6)
{
    // Error Checking
    static_assert(N > 2, "evaluate_chebyshev_derivative() - Size of boundsCoeff array must be greater than or equal to three.");

    // Extract lb, ub, and coefficients
    std::array<double, N - 2> coeff;
    for (std::size_t k = 0; k < N - 2; k++) {
        coeff[k] = boundsCoeff[k + 2];
    }

    // Evaluate the Chebyshev polynomial
    return evaluate_chebyshev_derivative(x, boundsCoeff[0], boundsCoeff[1], coeff, extrapolationTol);
}

} // namespace math
} // namespace astrea
```


