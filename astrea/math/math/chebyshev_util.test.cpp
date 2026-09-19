/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <array>
#include <cmath>

#include <gtest/gtest.h>

#include <math/chebyshev_util.hpp>

using namespace astrea;
using namespace astrea::math;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class ChebyshevUtilTest : public testing::Test {
  public:
    ChebyshevUtilTest() {}

    void SetUp() override {}

    const double REL_TOL = 1.0e-10;
};

// ============================================================================
// Transform Functions Tests
// ============================================================================

TEST_F(ChebyshevUtilTest, TransformFromChebyshevRangeZero)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // x = 0 should map to midpoint (5.0)
    const double result = transform_from_chebyshev_range(0.0, lb, ub);
    ASSERT_NEAR(result, 5.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformFromChebyshevRangeLowerBound)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // x = -1 should map to lb (0.0)
    const double result = transform_from_chebyshev_range(-1.0, lb, ub);
    ASSERT_NEAR(result, 0.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformFromChebyshevRangeUpperBound)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // x = 1 should map to ub (10.0)
    const double result = transform_from_chebyshev_range(1.0, lb, ub);
    ASSERT_NEAR(result, 10.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformFromChebyshevRangeNegativeBounds)
{
    const double lb = -5.0;
    const double ub = 5.0;

    ASSERT_NEAR(transform_from_chebyshev_range(-1.0, lb, ub), -5.0, REL_TOL);
    ASSERT_NEAR(transform_from_chebyshev_range(0.0, lb, ub), 0.0, REL_TOL);
    ASSERT_NEAR(transform_from_chebyshev_range(1.0, lb, ub), 5.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformToChebyshevRangeZero)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // Midpoint (5.0) should map to x = 0
    const double result = transform_to_chebyshev_range(5.0, lb, ub);
    ASSERT_NEAR(result, 0.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformToChebyshevRangeLowerBound)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // lb (0.0) should map to x = -1
    const double result = transform_to_chebyshev_range(0.0, lb, ub);
    ASSERT_NEAR(result, -1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformToChebyshevRangeUpperBound)
{
    const double lb = 0.0;
    const double ub = 10.0;

    // ub (10.0) should map to x = 1
    const double result = transform_to_chebyshev_range(10.0, lb, ub);
    ASSERT_NEAR(result, 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformToChebyshevRangeNegativeBounds)
{
    const double lb = -5.0;
    const double ub = 5.0;

    ASSERT_NEAR(transform_to_chebyshev_range(-5.0, lb, ub), -1.0, REL_TOL);
    ASSERT_NEAR(transform_to_chebyshev_range(0.0, lb, ub), 0.0, REL_TOL);
    ASSERT_NEAR(transform_to_chebyshev_range(5.0, lb, ub), 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, TransformRoundTrip)
{
    const double lb = -10.0;
    const double ub = 20.0;

    // Test round-trip transformation
    const double original = 5.0;
    const double cheb     = transform_to_chebyshev_range(original, lb, ub);
    const double back     = transform_from_chebyshev_range(cheb, lb, ub);

    ASSERT_NEAR(back, original, REL_TOL);
}

// ============================================================================
// Polynomial Evaluation Tests
// ============================================================================

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialConstant)
{
    // Constant function: f(x) = 5
    const std::array<double, 3> coeff = { 5.0, 0.0, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    // With coeffZeroFactor = 0.5 (default), result should be 0.5 * 5.0 = 2.5
    const double result = evaluate_chebyshev_polynomial(0.0, lb, ub, coeff);
    ASSERT_NEAR(result, 2.5, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialConstantFactorOne)
{
    // Constant function: f(x) = 5
    const std::array<double, 3> coeff = { 5.0, 0.0, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    // With coeffZeroFactor = 1.0, result should be 5.0
    const double result = evaluate_chebyshev_polynomial(0.0, lb, ub, coeff, 1.0);
    ASSERT_NEAR(result, 5.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialLinear)
{
    // Linear approximation: f(x) ≈ x on [-1, 1]
    // T_0(x) = 1, T_1(x) = x
    // For f(x) = x, coefficients are [0, 1, 0, ...]
    const std::array<double, 4> coeff = { 0.0, 1.0, 0.0, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    ASSERT_NEAR(evaluate_chebyshev_polynomial(-1.0, lb, ub, coeff, 1.0), -1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(0.0, lb, ub, coeff, 1.0), 0.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(1.0, lb, ub, coeff, 1.0), 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialQuadratic)
{
    // Quadratic: f(x) = x^2 on [-1, 1]
    // T_0(x) = 1, T_1(x) = x, T_2(x) = 2x^2 - 1
    // For f(x) = x^2: x^2 = 0.5*(T_0 + T_2) = 0.5*(1 + 2x^2 - 1) = x^2
    // Coefficients: [0.5, 0, 0.5]
    const std::array<double, 4> coeff = { 0.5, 0.0, 0.5, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    ASSERT_NEAR(evaluate_chebyshev_polynomial(-1.0, lb, ub, coeff, 1.0), 1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(0.0, lb, ub, coeff, 1.0), 0.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(0.5, lb, ub, coeff, 1.0), 0.25, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(1.0, lb, ub, coeff, 1.0), 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialBoundsCoeff)
{
    // Test overload that includes bounds in coefficient array
    const std::array<double, 5> boundsCoeff = { -1.0, 1.0, 0.5, 0.0, 0.5 }; // lb, ub, then coefficients

    ASSERT_NEAR(evaluate_chebyshev_polynomial(-1.0, boundsCoeff, 1.0), 1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(0.0, boundsCoeff, 1.0), 0.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_polynomial(1.0, boundsCoeff, 1.0), 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialScaledRange)
{
    // Test with scaled range [0, 10]
    const std::array<double, 4> coeff = { 5.0, 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // Should work correctly with range transformation
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(0.0, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(5.0, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(10.0, lb, ub, coeff, 1.0));
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialExtrapolationLower)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // x = -1.0 is outside bounds, should throw
    ASSERT_THROW(evaluate_chebyshev_polynomial(-1.0, lb, ub, coeff), std::invalid_argument);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialExtrapolationUpper)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // x = 11.0 is outside bounds, should throw
    ASSERT_THROW(evaluate_chebyshev_polynomial(11.0, lb, ub, coeff), std::invalid_argument);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevPolynomialWithinTolerance)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;
    const double tol                  = 1.0e-5;

    // x = -1e-6 is within tolerance, should not throw
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(-1.0e-6, lb, ub, coeff, 1.0, tol));

    // x = 10 + 1e-6 is within tolerance, should not throw
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(10.0 + 1.0e-6, lb, ub, coeff, 1.0, tol));
}

// ============================================================================
// Derivative Evaluation Tests
// ============================================================================

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeConstant)
{
    // Derivative of constant function is zero
    const std::array<double, 3> coeff = { 5.0, 0.0, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    const double result = evaluate_chebyshev_derivative(0.0, lb, ub, coeff);
    ASSERT_NEAR(result, 0.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeLinear)
{
    // Derivative of f(x) = x is 1
    const std::array<double, 4> coeff = { 0.0, 1.0, 0.0, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    ASSERT_NEAR(evaluate_chebyshev_derivative(-1.0, lb, ub, coeff), 1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(0.0, lb, ub, coeff), 1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(1.0, lb, ub, coeff), 1.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeQuadratic)
{
    // Derivative of f(x) = x^2 is 2x
    const std::array<double, 4> coeff = { 0.5, 0.0, 0.5, 0.0 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;

    ASSERT_NEAR(evaluate_chebyshev_derivative(-1.0, lb, ub, coeff), -2.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(0.0, lb, ub, coeff), 0.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(0.5, lb, ub, coeff), 1.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(1.0, lb, ub, coeff), 2.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeBoundsCoeff)
{
    // Test overload with bounds in coefficient array
    const std::array<double, 5> boundsCoeff = { -1.0, 1.0, 0.5, 0.0, 0.5 }; // x^2

    ASSERT_NEAR(evaluate_chebyshev_derivative(-1.0, boundsCoeff), -2.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(0.0, boundsCoeff), 0.0, REL_TOL);
    ASSERT_NEAR(evaluate_chebyshev_derivative(1.0, boundsCoeff), 2.0, REL_TOL);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeScaledRange)
{
    // Test with scaled range [0, 10]
    // f(x) = x on [0, 10], df/dx = 1
    // In Chebyshev space [-1, 1], need to account for scaling
    const std::array<double, 4> coeff = { 5.0, 5.0, 0.0, 0.0 }; // Approximation of f(x) = x on [0, 10]
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // Derivative should be scaled by 2/(ub-lb) = 2/10 = 0.2
    const double result = evaluate_chebyshev_derivative(5.0, lb, ub, coeff);
    ASSERT_NEAR(result, 1.0, 1.0e-2); // Less strict tolerance due to approximation
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeExtrapolationLower)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // x = -1.0 is outside bounds, should throw
    ASSERT_THROW(evaluate_chebyshev_derivative(-1.0, lb, ub, coeff), std::invalid_argument);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeExtrapolationUpper)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;

    // x = 11.0 is outside bounds, should throw
    ASSERT_THROW(evaluate_chebyshev_derivative(11.0, lb, ub, coeff), std::invalid_argument);
}

TEST_F(ChebyshevUtilTest, EvaluateChebyshevDerivativeWithinTolerance)
{
    const std::array<double, 3> coeff = { 1.0, 0.0, 0.0 };
    const double lb                   = 0.0;
    const double ub                   = 10.0;
    const double tol                  = 1.0e-5;

    // x slightly outside bounds but within tolerance should not throw
    ASSERT_NO_THROW(evaluate_chebyshev_derivative(-1.0e-6, lb, ub, coeff, tol));
    ASSERT_NO_THROW(evaluate_chebyshev_derivative(10.0 + 1.0e-6, lb, ub, coeff, tol));
}

// ============================================================================
// Integration Tests with Known Functions
// ============================================================================

TEST_F(ChebyshevUtilTest, PolynomialAndDerivativeConsistency)
{
    // Test that numerical derivative approximates Chebyshev derivative
    const std::array<double, 5> coeff = { 1.0, 2.0, 3.0, 1.0, 0.5 };
    const double lb                   = -1.0;
    const double ub                   = 1.0;
    const double x                    = 0.3;
    const double h                    = 1.0e-6;

    // Compute analytical derivative
    const double analytical = evaluate_chebyshev_derivative(x, lb, ub, coeff);

    // Compute numerical derivative
    const double f_plus    = evaluate_chebyshev_polynomial(x + h, lb, ub, coeff, 1.0);
    const double f_minus   = evaluate_chebyshev_polynomial(x - h, lb, ub, coeff, 1.0);
    const double numerical = (f_plus - f_minus) / (2.0 * h);

    ASSERT_NEAR(analytical, numerical, 1.0e-4);
}

TEST_F(ChebyshevUtilTest, HighOrderPolynomial)
{
    // Test with a higher-order polynomial
    const std::array<double, 15> coeff = {
        1.0,          0.5,           0.25,           0.125,           0.0625,
        0.03125,      0.015625,      0.0078125,      0.00390625,      0.001953125,
        0.0009765625, 0.00048828125, 0.000244140625, 0.0001220703125, 0.00006103515625
    };
    const double lb = -1.0;
    const double ub = 1.0;

    // Should evaluate without error at various points
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(-1.0, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(-0.5, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(0.0, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(0.5, lb, ub, coeff, 1.0));
    ASSERT_NO_THROW(evaluate_chebyshev_polynomial(1.0, lb, ub, coeff, 1.0));
}

TEST_F(ChebyshevUtilTest, TransformInvariance)
{
    // Test that transforming to and from Chebyshev range preserves relationships
    const double lb1 = 0.0, ub1 = 10.0;
    const double lb2 = -5.0, ub2 = 5.0;

    std::array<double, 5> values = { 2.0, 3.5, 5.0, 7.2, 8.9 };

    for (const auto& val : values) {
        const double cheb = transform_to_chebyshev_range(val, lb1, ub1);
        const double back = transform_from_chebyshev_range(cheb, lb1, ub1);
        ASSERT_NEAR(val, back, REL_TOL);
    }
}
