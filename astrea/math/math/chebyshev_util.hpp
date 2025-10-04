/**
 * @file jpl_ephemeris/chebyshev/chebyshev_transformation.hpp
 * @brief Utility functions for Chebyshev interpolation
 *
 * @note Adapted from https://github.com/mschmit6/jpl_ephemeris.git
 */

#pragma once

#include <array>
#include <stdexcept>

namespace astrea {
namespace math {

/**
 * @brief Transform variable from the Chebyshev range of [-1, 1] to the range [lb, ub]
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10
 *
 * @param x Variable in the Chebyshev range
 * @param lb Lower bound of the function range
 * @param ub Upper bound of the function range
 *
 * @return Variable in the range [lb, ub]
 */
double transform_from_chebyshev_range(const double& x, const double& lb, const double& ub);

/**
 * @brief Transform variable from the range [lb, ub] to the Chebyshev range of [-1, 1]
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10
 *
 * @param x Variable in the range [lb, ub]
 * @param lb Lower bound of the function range
 * @param ub Upper bound of the function range
 *
 * @return Variable in the Chebyshev range [-1, 1]
 */
double transform_to_chebyshev_range(const double& x, const double& lb, const double& ub);

/**
 * @brief Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using
 * Clenshaw's recurrence formula.
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev
 *
 * @param x Value at which the Chebyshev polynomial is to be evaluated at
 * @param lb Lower bound of the function range
 * @param ub Upper bound of the function range
 * @param coeff Chebyshev coefficients evaluated using chebyshev_coefficients function
 * @param coeffZeroFactor Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0]
 *     has already been multiplied by 0.5, so set factor to 1.0
 * @param extrapolationTol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * @return Corresponding Chebyshev coefficient values
 *
 * @tparam N Size of the array
 *
 * @throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
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

/**
 * @brief Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using
 * Clenshaw's recurrence formula.
 *
 * @note The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary
 * coefficients from CSpice
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev
 *
 * @param x Value at which the Chebyshev polynomial is to be evaluated at
 * @param boundsCoeff Array containing lb, ub, and Chebyshev coefficients evaluated using chebyshev_coefficients function
 * @param coeffZeroFactor Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0]
 *     has already been multiplied by 0.5, so set factor to 1.0
 * @param extrapolationTol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * @return Corresponding Chebyshev coefficient values
 *
 * @tparam N Size of the array
 *
 * @throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
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

/**
 * @brief Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub],
 * using Clenshaw's recurrence formula.
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder
 *
 * @param x Value at which the Chebyshev polynomial is to be evaluated at
 * @param lb Lower bound of the function range
 * @param ub Upper bound of the function range
 * @param coeff Chebyshev coefficients evaluated using chebyshev_coefficients function
 * @param extrapolationTol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * @return Corresponding Chebyshev coefficient values
 *
 * @tparam N Size of the array
 *
 * @throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
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

/**
 * @brief Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub],
 * using Clenshaw's recurrence formula.
 *
 * @note The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary
 * coefficients from CSpice
 *
 * @ref Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder
 *
 * @param x Value at which the Chebyshev polynomial is to be evaluated at
 * @param boundsCoeff Vector containing lb, ub, and Chebyshev coefficients evaluated using chebyshev_coefficients function
 * @param extrapolationTol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * @return Corresponding Chebyshev coefficient values
 *
 * @tparam N Size of the array
 *
 * @throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
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
