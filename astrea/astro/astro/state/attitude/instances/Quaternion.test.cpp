/**
 * @file Quaternion.test.cpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Unit tests for the Quaternion class
 * @date 2026-03-20
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <gtest/gtest.h>

#include <stdexcept>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/state/attitude/instances/EulerAngles.hpp>
#include <astro/state/attitude/instances/Quaternion.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;

// Define some dummy frame types for testing template functionality
constexpr inline struct TestFrame1 final : Frame<"TestFrame1", planets::Earth, axes::icrf> {
} TestFrame1;
constexpr inline struct TestFrame2 final : Frame<"TestFrame2", planets::Mars, axes::icrf> {
} TestFrame2;
constexpr inline struct TestFrame3 final : Frame<"TestFrame3", planets::Jupiter, axes::icrf> {
} TestFrame3;

// Define a complete chain of transformations: Frame1 -> Frame2 -> Frame3 -> Frame1
using Q12 = Quaternion<TestFrame1, TestFrame2>;
using Q13 = Quaternion<TestFrame1, TestFrame3>;
using Q23 = Quaternion<TestFrame2, TestFrame3>;
using Q21 = Quaternion<TestFrame2, TestFrame1>;
using Q31 = Quaternion<TestFrame3, TestFrame1>;
using Q11 = Quaternion<TestFrame1, TestFrame1>;

// Type aliases for easier testing
using TestQuaternion = Quaternion<TestFrame1, TestFrame2>;
using TestVector     = CartesianVector<Unitless, TestFrame1>;

/**
 * @brief Test fixture for Quaternion unit tests
 */
class QuaternionTest : public ::testing::Test {
  protected:
    void SetUp() override {}

    void TearDown() override {}

    // Test data
    const Unitless scalar1{ 0.5 * one };
    const Unitless x1{ 0.3 * one };
    const Unitless y1{ 0.4 * one };
    const Unitless z1{ 0.2 * one };

    const Unitless scalar2{ 0.7 * one };
    const Unitless x2{ 0.1 * one };
    const Unitless y2{ 0.3 * one };
    const Unitless z2{ 0.5 * one };

    // Floating point math is a curse
    const Unitless REL_TOL = 1.0e-12 * one;
    const Unitless ABS_TOL = 1.0e-15 * one;

    // Helper function to compare quaternions with tolerance
    template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
    void ExpectQuaternionNearlyEqual(const Quaternion<_in_frame_, _out_frame_>& actual, const Quaternion<_in_frame_, _out_frame_>& expected)
    {
        // Compare scalar parts
        EXPECT_TRUE(math::nearly_equal(actual.get_scalar_part(), expected.get_scalar_part(), REL_TOL, ABS_TOL));

        // Compare vector parts
        auto actualVec   = actual.get_vector_part();
        auto expectedVec = expected.get_vector_part();
        EXPECT_TRUE(math::nearly_equal(actualVec.get_x(), expectedVec.get_x(), REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(actualVec.get_y(), expectedVec.get_y(), REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(actualVec.get_z(), expectedVec.get_z(), REL_TOL, ABS_TOL));
    }
};

/**
 * @brief Test default constructor
 */
TEST_F(QuaternionTest, DefaultConstructor)
{
    // Default constructor initializes to zero components which cannot be normalized
    // This should throw an exception since zero quaternion has no valid normalized form
    EXPECT_NO_THROW({ TestQuaternion q; });
}

/**
 * @brief Test constructor with default parameters
 */
TEST_F(QuaternionTest, ConstructorWithDefaults)
{
    // Test with only scalar part - should be automatically normalized
    TestQuaternion q1;
    // After normalization, quaternion should have unit norm
    EXPECT_TRUE(math::nearly_equal(q1.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    // Scalar part should be normalized: scalar1 / |scalar1|
    EXPECT_TRUE(math::nearly_equal(q1.get_scalar_part(), 1.0 * one, REL_TOL, ABS_TOL));
    auto vec1 = q1.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vec1.get_x(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec1.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec1.get_z(), 0.0 * one, REL_TOL, ABS_TOL));

    // Test with scalar and vector - should be automatically normalized
    TestVector testVec(x1, y1, z1);
    TestQuaternion q2(scalar1, testVec);
    // Should have unit norm after normalization
    EXPECT_TRUE(math::nearly_equal(q2.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Calculate expected normalized values
    Unitless inputNorm = sqrt(scalar1 * scalar1 + x1 * x1 + y1 * y1 + z1 * z1);
    EXPECT_TRUE(math::nearly_equal(q2.get_scalar_part(), scalar1 / inputNorm, REL_TOL, ABS_TOL));
    auto vec2 = q2.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vec2.get_x(), x1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec2.get_y(), y1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec2.get_z(), z1 / inputNorm, REL_TOL, ABS_TOL));
}

/**
 * @brief Test parameterized constructor with valid inputs
 */
TEST_F(QuaternionTest, ParameterizedConstructor_ValidInputs)
{
    // Test with real components - should automatically normalize to unit quaternion
    EXPECT_NO_THROW({
        TestQuaternion q(scalar1, x1, y1, z1);
        // All quaternions should have unit norm due to automatic normalization
        EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    });

    // Test boundary values - should result in unit quaternions
    EXPECT_NO_THROW({
        TestQuaternion q(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
        EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    });

    EXPECT_NO_THROW({
        TestQuaternion q(-1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
        EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    });

    // Test zero quaternion should throw error (cannot normalize)
    EXPECT_THROW({ TestQuaternion q(0.0 * one, 0.0 * one, 0.0 * one, 0.0 * one); }, std::runtime_error);
}

/**
 * @brief Test addition operator
 */
TEST_F(QuaternionTest, AdditionOperator)
{
    TestQuaternion q1(scalar1, x1, y1, z1);
    TestQuaternion q2(scalar2, x2, y2, z2);

    TestQuaternion result = q1 + q2;

    // Result should be automatically normalized to unit quaternion
    EXPECT_TRUE(math::nearly_equal(result.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Addition should be commutative (after normalization)
    TestQuaternion result2 = q2 + q1;
    ExpectQuaternionNearlyEqual(result, result2);

    // Note: Addition with zero quaternion is not valid since default constructor
    // throws for zero quaternion - we cannot create a zero quaternion to test with
}

/**
 * @brief Test in-place addition operator
 */
TEST_F(QuaternionTest, InPlaceAdditionOperator)
{
    TestQuaternion q1(scalar1, x1, y1, z1);
    TestQuaternion q2(scalar2, x2, y2, z2);
    TestQuaternion originalQ1 = q1;

    TestQuaternion& result = q1 += q2;

    // Should return reference to q1
    EXPECT_EQ(&result, &q1);

    // Should be equivalent to regular addition
    TestQuaternion expected = originalQ1 + q2;
    ExpectQuaternionNearlyEqual(q1, expected);
}

/**
 * @brief Test unary negation operator
 */
TEST_F(QuaternionTest, UnaryNegationOperator)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    TestQuaternion negated = -q;

    // Negated quaternion should still have unit norm
    EXPECT_TRUE(math::nearly_equal(negated.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Adding a quaternion to its negation gives zero vector, which after normalization
    // is undefined - this should throw an error
    EXPECT_THROW({ TestQuaternion sum = q + negated; }, std::runtime_error);

    // Double negation should return original
    TestQuaternion doubleNegated = -(-q);
    ExpectQuaternionNearlyEqual(doubleNegated, q);
}

/**
 * @brief Test subtraction operator
 */
TEST_F(QuaternionTest, SubtractionOperator)
{
    TestQuaternion q1(scalar1, x1, y1, z1);
    TestQuaternion q2(scalar2, x2, y2, z2);

    TestQuaternion result = q1 - q2;

    // Result should be automatically normalized to unit quaternion
    EXPECT_TRUE(math::nearly_equal(result.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Should be equivalent to adding negation (both normalized)
    TestQuaternion expected = q1 + (-q2);
    ExpectQuaternionNearlyEqual(result, expected);

    // Subtracting itself should give zero vector which cannot be normalized
    EXPECT_THROW({ TestQuaternion selfDiff = q1 - q1; }, std::runtime_error);
}

/**
 * @brief Test in-place subtraction operator
 */
TEST_F(QuaternionTest, InPlaceSubtractionOperator)
{
    TestQuaternion q1(scalar1, x1, y1, z1);
    TestQuaternion q2(scalar2, x2, y2, z2);
    TestQuaternion originalQ1 = q1;

    TestQuaternion& result = q1 -= q2;

    // Should return reference to q1
    EXPECT_EQ(&result, &q1);

    // Should be equivalent to regular subtraction
    TestQuaternion expected = originalQ1 - q2;
    ExpectQuaternionNearlyEqual(q1, expected);
}

/**
 * @brief Test multiplication operator with frame chaining
 */
TEST_F(QuaternionTest, MultiplicationOperator)
{
    // Create quaternions with different frame types for chaining
    using QFrame12 = Quaternion<TestFrame1, TestFrame2>;
    using QFrame23 = Quaternion<TestFrame2, TestFrame3>;
    using QFrame13 = Quaternion<TestFrame1, TestFrame3>;

    QFrame12 q12(scalar1, x1, y1, z1);
    QFrame23 q23(scalar2, x2, y2, z2);

    // Test frame chaining: TestFrame1 -> TestFrame2 -> TestFrame3
    EXPECT_NO_THROW({
        QFrame13 result = q12 * q23;
        // Result should have unit norm (quaternions are automatically normalized)
        EXPECT_TRUE(math::nearly_equal(result.norm(), 1.0 * one, REL_TOL, ABS_TOL));

        // Verify we can access components of the result
        EXPECT_TRUE(std::isfinite(result.get_scalar_part().numerical_value_in(one)));
        auto resultVec = result.get_vector_part();
        EXPECT_TRUE(std::isfinite(resultVec.get_x().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(resultVec.get_y().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(resultVec.get_z().numerical_value_in(one)));
    });

    // Since all quaternions have unit norm, |q1 * q2| = 1
    auto chainResult = q12 * q23;
    EXPECT_TRUE(math::nearly_equal(chainResult.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    // Original quaternions also have unit norm
    EXPECT_TRUE(math::nearly_equal(q12.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(q23.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Test associativity with frame chaining
    using QFrame34 = Quaternion<TestFrame3, TestFrame1>; // Close the loop
    QFrame34 q34(0.6 * one, 0.2 * one, 0.1 * one, 0.3 * one);

    auto leftAssoc  = (q12 * q23) * q34; // QFrame11
    auto rightAssoc = q12 * (q23 * q34); // QFrame11
    // Both should have unit norm
    EXPECT_TRUE(math::nearly_equal(leftAssoc.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(rightAssoc.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test conjugate method
 */
TEST_F(QuaternionTest, ConjugateMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    auto conj = q.conjugate();

    // Verify conjugate properties - scalar stays same, vector negated
    EXPECT_TRUE(math::nearly_equal(conj.get_scalar_part(), scalar1));
    auto conjVec = conj.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(conjVec.get_x(), -x1));
    EXPECT_TRUE(math::nearly_equal(conjVec.get_y(), -y1));
    EXPECT_TRUE(math::nearly_equal(conjVec.get_z(), -z1));

    // Note: conjugate returns Quaternion<_out_frame_, _in_frame_>, so double conjugate
    // will return Quaternion<_in_frame_, _out_frame_> which matches original
    auto conjConj = conj.conjugate();
    ExpectQuaternionNearlyEqual(conjConj, q);
}

/**
 * @brief Test norm method
 */
TEST_F(QuaternionTest, NormMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    Unitless normValue = q.norm();

    // All quaternions should have unit norm due to automatic normalization
    EXPECT_TRUE(math::nearly_equal(normValue, 1.0 * one, REL_TOL, ABS_TOL));

    // Norm should be real and finite
    EXPECT_TRUE(std::isfinite(normValue.numerical_value_in(one)));

    // Unit quaternion cannot be constructed (throws in constructor)
    TestQuaternion identity;
    EXPECT_TRUE(math::nearly_equal(identity.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Any valid quaternion should have norm 1
    TestQuaternion unitI(0.0 * one, 1.0 * one, 0.0 * one, 0.0 * one);
    EXPECT_TRUE(math::nearly_equal(unitI.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test inverse method
 */
TEST_F(QuaternionTest, InverseMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    auto inv = q.inverse();

    // Note: inverse returns Quaternion<_out_frame_, _in_frame_>
    // Since quaternions are unit quaternions, inverse should also have unit norm
    EXPECT_TRUE(math::nearly_equal(inv.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Original quaternion should have unit norm
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test unit method
 */
TEST_F(QuaternionTest, UnitMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    TestQuaternion unitQ = q;
    unitQ.normalize();

    // Since quaternions are automatically normalized, unit() should return the same quaternion
    ExpectQuaternionNearlyEqual(unitQ, q);

    // Unit quaternion should have norm 1 (but so should the original)
    EXPECT_TRUE(math::nearly_equal(unitQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Test with any quaternion - unit() should be idempotent
    TestQuaternion anyUnit(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
    TestQuaternion unitOfUnit = anyUnit;
    unitOfUnit.normalize();
    ExpectQuaternionNearlyEqual(unitOfUnit, anyUnit);
}

/**
 * @brief Test unit method with zero quaternion (error case)
 */
TEST_F(QuaternionTest, UnitMethod_ZeroQuaternion)
{
    // Cannot construct zero quaternion as it throws in constructor
    // So this test is no longer applicable - zero quaternions cannot exist
}

/**
 * @brief Test edge cases and special quaternions
 */
TEST_F(QuaternionTest, EdgeCases)
{
    // Test with very small components - should still normalize properly
    const Unitless smallScalar{ 1e-10 * one };
    const Unitless smallX{ REL_TOL };
    const Unitless smallY{ REL_TOL };
    const Unitless smallZ{ REL_TOL };

    EXPECT_NO_THROW({
        TestQuaternion smallQ(smallScalar, smallX, smallY, smallZ);
        // Should be normalized to unit quaternion
        EXPECT_TRUE(math::nearly_equal(smallQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));
        // normalize() method should return the same quaternion (idempotent)
        TestQuaternion unitQ = smallQ;
        unitQ.normalize();
        ExpectQuaternionNearlyEqual(unitQ, smallQ);
        EXPECT_NO_THROW(smallQ.inverse());
    });

    // Test pure scalar quaternion (after normalization)
    TestQuaternion pureScalar(0.8 * one, 0.0 * one, 0.0 * one, 0.0 * one);
    // Should be normalized
    EXPECT_TRUE(math::nearly_equal(pureScalar.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    auto conjScalar = pureScalar.conjugate();
    // For pure scalar, conjugate should have same scalar part and zero vector
    EXPECT_TRUE(math::nearly_equal(conjScalar.get_scalar_part(), pureScalar.get_scalar_part()));
    auto conjVec = conjScalar.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(conjVec.get_x(), 0.0 * one));
    EXPECT_TRUE(math::nearly_equal(conjVec.get_y(), 0.0 * one));
    EXPECT_TRUE(math::nearly_equal(conjVec.get_z(), 0.0 * one));

    // Test pure vector quaternion (scalar = 0, will be normalized)
    TestQuaternion pureVector(0.0 * one, 0.6 * one, 0.8 * one, 0.0 * one);
    // Should be normalized to unit quaternion
    EXPECT_TRUE(math::nearly_equal(pureVector.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    auto conjVector              = pureVector.conjugate();
    TestQuaternion negatedVector = -pureVector;

    // For pure vector quaternion, conjugate should negate the vector part
    EXPECT_TRUE(math::nearly_equal(conjVector.get_scalar_part(), 0.0 * one, REL_TOL, ABS_TOL));
    auto conjVecPart = conjVector.get_vector_part();
    auto negVecPart  = negatedVector.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(conjVecPart.get_x(), negVecPart.get_x()));
    EXPECT_TRUE(math::nearly_equal(conjVecPart.get_y(), negVecPart.get_y()));
    EXPECT_TRUE(math::nearly_equal(conjVecPart.get_z(), negVecPart.get_z()));
}

/**
 * @brief Test frame transformation chaining
 */
TEST_F(QuaternionTest, FrameTransformationChaining)
{
    // Create quaternions representing rotations between frames
    Q12 q12(scalar1, x1, y1, z1);
    Q23 q23(scalar2, x2, y2, z2);
    Q31 q31(0.8 * one, 0.1 * one, 0.2 * one, 0.15 * one);

    // Test two-step chaining: Frame1 -> Frame2 -> Frame3
    EXPECT_NO_THROW({
        Q13 result13 = q12 * q23;
        EXPECT_GT(result13.norm(), 0.0 * one);

        // Chain should preserve composition properties
        Unitless expectedNorm = q12.norm() * q23.norm();
        EXPECT_TRUE(math::nearly_equal(result13.norm(), expectedNorm, REL_TOL, ABS_TOL));
    });

    // Test three-step chaining: Frame1 -> Frame2 -> Frame3 -> Frame1 (full cycle)
    EXPECT_NO_THROW({
        Q11 fullCycle = (q12 * q23) * q31;
        EXPECT_GT(fullCycle.norm(), 0.0 * one);

        // Test associativity in chaining
        Q11 alternateCycle = q12 * (q23 * q31);
        EXPECT_TRUE(math::nearly_equal(fullCycle.norm(), alternateCycle.norm(), REL_TOL, ABS_TOL));

        // Components should be finite and reasonable
        auto vec = fullCycle.get_vector_part();
        EXPECT_TRUE(std::isfinite(fullCycle.get_scalar_part().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(vec.get_x().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(vec.get_y().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(vec.get_z().numerical_value_in(one)));
    });

    // Test that inverse operations work with frame chaining
    EXPECT_NO_THROW({
        Q13 forward     = q12 * q23;
        auto inverseQ23 = q23.inverse(); // Returns Q32
        auto inverseQ12 = q12.inverse(); // Returns Q21

        // The inverse of a chain should be the reverse chain of inverses
        auto reverseChain = inverseQ23 * inverseQ12; // Q32 * Q21 = Q31

        // Both should have reasonable norms
        EXPECT_GT(forward.norm(), 0.0 * one);
        EXPECT_GT(reverseChain.norm(), 0.0 * one);
    });
}

/**
 * @brief Test DCM to Quaternion conversion
 */
TEST_F(QuaternionTest, DCMToQuaternionConversion)
{
    using TestDCM = DirectionCosineMatrix<TestFrame1, TestFrame2>;
    using mp_units::angular::unit_symbols::rad;

    // Test identity DCM -> should give identity quaternion
    EXPECT_NO_THROW({
        TestDCM identityDCM = TestDCM::identity();

        TestQuaternion q(identityDCM);

        // Identity quaternion should have scalar part = ±1 and zero vector part
        // (sign ambiguity is normal for quaternions)
        EXPECT_TRUE(math::nearly_equal(abs(q.get_scalar_part()), 1.0 * one, REL_TOL, ABS_TOL));
        auto vec = q.get_vector_part();
        EXPECT_TRUE(math::nearly_equal(vec.get_x(), 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(vec.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(vec.get_z(), 0.0 * one, REL_TOL, ABS_TOL));
    });

    // Test 90° rotation about Z-axis
    EXPECT_NO_THROW({
        TestDCM zRot90 = TestDCM::Z(90.0 * deg);
        TestQuaternion q(zRot90);

        // Should be valid quaternion with unit norm
        EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));

        // For 90° Z rotation: cos(45°) ≈ 0.7071, sin(45°) ≈ 0.7071
        EXPECT_TRUE(math::nearly_equal(abs(q.get_scalar_part()), 0.7071067811865475 * one, 1e-10 * one));
        auto vec = q.get_vector_part();
        EXPECT_TRUE(math::nearly_equal(abs(vec.get_z()), 0.7071067811865475 * one, 1e-10 * one));
    });

    // Test 180° rotation about X-axis (edge case for trace-based algorithm)
    EXPECT_NO_THROW({
        TestDCM xRot180 = TestDCM::X(180.0 * deg);
        TestQuaternion q(xRot180);

        // Should be unit quaternion
        EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));

        // 180° rotation should have zero scalar part and unit vector component
        EXPECT_TRUE(math::nearly_equal(abs(q.get_scalar_part()), 0.0 * one, REL_TOL, ABS_TOL));
        auto vec = q.get_vector_part();
        EXPECT_TRUE(math::nearly_equal(abs(vec.get_x()), 1.0 * one, REL_TOL, ABS_TOL));
    });
}

/**
 * @brief Test Quaternion to DCM conversion
 */
TEST_F(QuaternionTest, QuaternionToDCMConversion)
{
    using TestDCM = DirectionCosineMatrix<TestFrame1, TestFrame2>;

    // Test identity quaternion -> should give identity DCM
    EXPECT_NO_THROW({
        TestQuaternion identityQ(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
        TestDCM dcm = identityQ.to_dcm();

        // Should be identity matrix
        EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, REL_TOL, ABS_TOL));
    });

    // Test 90° Z rotation quaternion
    EXPECT_NO_THROW({
        // q = [cos(45°), 0, 0, sin(45°)] for 90° Z rotation
        const Unitless cos45 = 0.7071067811865475 * one;
        TestQuaternion zRot90Q(cos45, 0.0 * one, 0.0 * one, cos45);
        TestDCM dcm = zRot90Q.to_dcm();

        // Should match expected 90° Z rotation matrix
        // [ 0 -1  0]
        // [ 1  0  0]
        // [ 0  0  1]
        EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, REL_TOL, ABS_TOL));
    });

    // Test that DCM is orthogonal (DCM * DCM^T = I)
    EXPECT_NO_THROW({
        TestQuaternion q(scalar1, x1, y1, z1);
        TestQuaternion unitQ = q; // Ensure it's a unit quaternion
        unitQ.normalize();
        TestDCM dcm = unitQ.to_dcm();

        // Test orthogonality by checking that columns are unit vectors
        Unitless col0Norm = sqrt(dcm[0, 0] * dcm[0, 0] + dcm[1, 0] * dcm[1, 0] + dcm[2, 0] * dcm[2, 0]);
        Unitless col1Norm = sqrt(dcm[0, 1] * dcm[0, 1] + dcm[1, 1] * dcm[1, 1] + dcm[2, 1] * dcm[2, 1]);
        Unitless col2Norm = sqrt(dcm[0, 2] * dcm[0, 2] + dcm[1, 2] * dcm[1, 2] + dcm[2, 2] * dcm[2, 2]);

        EXPECT_TRUE(math::nearly_equal(col0Norm, 1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(col1Norm, 1.0 * one, REL_TOL, ABS_TOL));
        EXPECT_TRUE(math::nearly_equal(col2Norm, 1.0 * one, REL_TOL, ABS_TOL));
    });
}

/**
 * @brief Test round-trip DCM ↔ Quaternion conversions
 */
TEST_F(QuaternionTest, DCMQuaternionRoundTrip)
{
    using TestDCM = DirectionCosineMatrix<TestFrame1, TestFrame2>;

    // Test various rotation angles and axes
    std::vector<std::pair<std::string, TestDCM>> testCases = {
        { "Identity", TestDCM::identity() },    { "X_30deg", TestDCM::X(30.0 * deg) },
        { "Y_45deg", TestDCM::Y(45.0 * deg) },  { "Z_60deg", TestDCM::Z(60.0 * deg) },
        { "X_90deg", TestDCM::X(90.0 * deg) },  { "Y_120deg", TestDCM::Y(120.0 * deg) },
        { "Z_180deg", TestDCM::Z(180.0 * deg) }
    };

    // Since all quaternions are normalized, all should have unit norm
    for (const auto& [name, originalDCM] : testCases) {
        SCOPED_TRACE("Testing case: " + name);

        // Round trip: DCM -> Quaternion -> DCM
        EXPECT_NO_THROW({
            TestQuaternion q(originalDCM);
            // Quaternion should be automatically normalized
            EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
            TestDCM roundTripDCM = q.to_dcm();

            // Compare each element (accounting for possible quaternion sign ambiguity)
            for (int ii = 0; ii < 3; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
                    EXPECT_TRUE(math::nearly_equal(roundTripDCM[ii, jj], originalDCM[ii, jj], REL_TOL, ABS_TOL));
                }
            }
        });
    }

    // Test the reverse: Quaternion -> DCM -> Quaternion
    EXPECT_NO_THROW({
        TestQuaternion originalQ(scalar1, x1, y1, z1);
        // originalQ is automatically normalized to unit quaternion
        EXPECT_TRUE(math::nearly_equal(originalQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));

        TestDCM dcm = originalQ.to_dcm();
        TestQuaternion roundTripQ(dcm);
        // Round trip quaternion should also be unit
        EXPECT_TRUE(math::nearly_equal(roundTripQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));

        // Quaternions q and -q represent the same rotation, so check both possibilities
        bool matches = (abs(roundTripQ.get_scalar_part() - originalQ.get_scalar_part()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_x() - originalQ.get_vector_part().get_x()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_y() - originalQ.get_vector_part().get_y()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_z() - originalQ.get_vector_part().get_z()) < REL_TOL,
                        ABS_TOL) ||
                       (abs(roundTripQ.get_scalar_part() + originalQ.get_scalar_part()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_x() + originalQ.get_vector_part().get_x()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_y() + originalQ.get_vector_part().get_y()) < REL_TOL &&
                            abs(roundTripQ.get_vector_part().get_z() + originalQ.get_vector_part().get_z()) < REL_TOL,
                        ABS_TOL);

        EXPECT_TRUE(matches) << "Round-trip quaternion does not match original (accounting for sign ambiguity)";
    });
}

/**
 * @brief Test DCM conversion with challenging cases for numerical stability
 */
TEST_F(QuaternionTest, DCMConversionNumericalStability)
{
    using TestDCM = DirectionCosineMatrix<TestFrame1, TestFrame2>;

    // Test near-180° rotations that challenge the trace-based algorithm
    std::vector<Angle> challengingAngles = {
        179.0 * deg, // Very close to 180°
        179.9 * deg, // Even closer to 180°
        180.0 * deg  // Exactly 180°
    };

    for (const auto& angle : challengingAngles) {
        SCOPED_TRACE("Testing angle: " + std::to_string(angle.numerical_value_in(deg)));

        // Test X-axis rotation
        EXPECT_NO_THROW({
            TestDCM dcm = TestDCM::X(angle);
            TestQuaternion q(dcm);

            // Should produce a unit quaternion
            EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));

            // Round-trip should preserve the DCM
            TestDCM roundTrip = q.to_dcm();
            for (int ii = 0; ii < 3; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
                    EXPECT_TRUE(math::nearly_equal(roundTrip[ii, jj], dcm[ii, jj], REL_TOL, ABS_TOL));
                }
            }
        });
    }

    // Test small rotations that might challenge numerical precision
    std::vector<Angle> smallAngles = {
        1e-6 * deg, // Very small angle
        1e-3 * deg, // Small angle
        0.1 * deg   // Small but reasonable angle
    };

    for (const auto& angle : smallAngles) {
        SCOPED_TRACE("Testing small angle: " + std::to_string(angle.numerical_value_in(deg)));

        EXPECT_NO_THROW({
            TestDCM dcm = TestDCM::Z(angle);
            TestQuaternion q(dcm);

            // Should be close to identity quaternion
            EXPECT_GT(abs(q.get_scalar_part()), 0.9999 * one); // cos(small_angle/2) ≈ 1
            EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
        });
    }
}

TEST_F(QuaternionTest, BasicConstructorComprehensive)
{
    TestQuaternion q(scalar1, x1, y1, z1);

    // Verify automatic normalization to unit quaternion
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Calculate expected normalized values
    Unitless inputNorm = sqrt(scalar1 * scalar1 + x1 * x1 + y1 * y1 + z1 * z1);

    // Verify components are correctly normalized
    EXPECT_TRUE(math::nearly_equal(q.get_scalar_part(), scalar1 / inputNorm, REL_TOL, ABS_TOL));
    auto vecPart = q.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPart.get_x(), x1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_y(), y1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_z(), z1 / inputNorm, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, IdentityQuaternions)
{
    TestQuaternion identity(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);

    EXPECT_TRUE(math::nearly_equal(identity.get_scalar_part(), 1.0 * one, REL_TOL, ABS_TOL));
    auto vecPart = identity.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPart.get_x(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_z(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(identity.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, PureVectorQuaternions)
{
    TestQuaternion pureI(0.0 * one, 1.0 * one, 0.0 * one, 0.0 * one);
    TestQuaternion pureJ(0.0 * one, 0.0 * one, 1.0 * one, 0.0 * one);
    TestQuaternion pureK(0.0 * one, 0.0 * one, 0.0 * one, 1.0 * one);

    // All should be normalized to unit quaternions
    EXPECT_TRUE(math::nearly_equal(pureI.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(pureJ.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(pureK.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Verify components for pure I quaternion
    EXPECT_TRUE(math::nearly_equal(pureI.get_scalar_part(), 0.0 * one, REL_TOL, ABS_TOL));
    auto vecPartI = pureI.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPartI.get_x(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPartI.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPartI.get_z(), 0.0 * one, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, NegativeComponents)
{
    TestQuaternion negComponents(-scalar1, -x1, -y1, -z1);

    EXPECT_TRUE(math::nearly_equal(negComponents.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Calculate expected normalized values for negative components
    Unitless inputNorm = sqrt(scalar1 * scalar1 + x1 * x1 + y1 * y1 + z1 * z1);

    EXPECT_TRUE(math::nearly_equal(negComponents.get_scalar_part(), -scalar1 / inputNorm, REL_TOL, ABS_TOL));
    auto vecPart = negComponents.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPart.get_x(), -x1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_y(), -y1 / inputNorm, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_z(), -z1 / inputNorm, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, MixedSignComponents)
{
    TestQuaternion mixed(scalar1, -x1, y1, -z1);

    EXPECT_TRUE(math::nearly_equal(mixed.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Verify all components are finite
    EXPECT_TRUE(std::isfinite(mixed.get_scalar_part().numerical_value_in(one)));
    auto vecPart = mixed.get_vector_part();
    EXPECT_TRUE(std::isfinite(vecPart.get_x().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vecPart.get_y().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vecPart.get_z().numerical_value_in(one)));
}

TEST_F(QuaternionTest, EdgeCaseVerySmallNonZeroComponents)
{
    // Test 1: Very small but non-zero components
    Unitless small = 1e-10 * one;
    TestQuaternion smallQ(small, small, small, small);

    // Should normalize properly even with small components
    EXPECT_TRUE(math::nearly_equal(smallQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // Normalized components should be equal due to symmetry
    Unitless expectedComponent = small / (2.0 * small); // sqrt(4 * small^2) = 2 * small
    EXPECT_TRUE(math::nearly_equal(smallQ.get_scalar_part(), expectedComponent, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, EdgeCaseVeryLargeNonZeroComponents)
{
    Unitless large = 1000.0 * one;
    TestQuaternion largeQ(large, large, large, large);

    // Should normalize to unit quaternion regardless of input magnitude
    EXPECT_TRUE(math::nearly_equal(largeQ.norm(), 1.0 * one, REL_TOL, ABS_TOL));

    // All normalized components should be equal
    Unitless expectedComponent = 0.5 * one; // 1/sqrt(4) = 0.5
    EXPECT_TRUE(math::nearly_equal(largeQ.get_scalar_part(), expectedComponent, REL_TOL, ABS_TOL));
    auto vecPart = largeQ.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPart.get_x(), expectedComponent, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_y(), expectedComponent, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_z(), expectedComponent, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, EdgeCaseZeroComponents)
{
    EXPECT_THROW({ TestQuaternion zeroQ(0.0 * one, 0.0 * one, 0.0 * one, 0.0 * one); }, std::runtime_error);
}

TEST_F(QuaternionTest, SingleNonZeroComponent)
{
    TestQuaternion singleNonZero(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);

    EXPECT_TRUE(math::nearly_equal(singleNonZero.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(singleNonZero.get_scalar_part(), 1.0 * one, REL_TOL, ABS_TOL));
    auto vecPart = singleNonZero.get_vector_part();
    EXPECT_TRUE(math::nearly_equal(vecPart.get_x(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vecPart.get_z(), 0.0 * one, REL_TOL, ABS_TOL));
}

TEST_F(QuaternionTest, BoundaryValues)
{
    auto maxVal = std::numeric_limits<double>::max() * one;
    auto minVal = std::numeric_limits<double>::lowest() * one;

    // These extreme values should throw an inf error
    EXPECT_THROW({ TestQuaternion extremeQ(maxVal, minVal, 1.0 * one, -1.0 * one); }, std::runtime_error);
}

/**
 * @brief Test individual component constructor equivalence with other constructors
 */
TEST_F(QuaternionTest, IndividualComponentConstructorEquivalence)
{
    // Test equivalence with scalar + vector constructor
    TestVector testVec(x1, y1, z1);
    TestQuaternion vectorConstructed(scalar1, testVec);
    TestQuaternion componentConstructed(scalar1, x1, y1, z1);

    // Both should produce identical quaternions
    ExpectQuaternionNearlyEqual(vectorConstructed, componentConstructed);

    // Test equivalence with copy constructor
    TestQuaternion copied(componentConstructed);
    ExpectQuaternionNearlyEqual(componentConstructed, copied);

    // Test that different component orders produce different quaternions
    TestQuaternion differentOrder(scalar1, z1, x1, y1); // Different vector component order

    // These should NOT be equal (unless by coincidence)
    if (x1 != z1 || y1 != x1 || z1 != y1) {
        // Use a simple comparison instead of complex inequality logic
        bool areEqual = (componentConstructed.get_scalar_part() == differentOrder.get_scalar_part());
        auto vec1     = componentConstructed.get_vector_part();
        auto vec2     = differentOrder.get_vector_part();
        areEqual      = areEqual && (vec1.get_x() == vec2.get_x()) && (vec1.get_y() == vec2.get_y()) &&
                   (vec1.get_z() == vec2.get_z());

        EXPECT_FALSE(areEqual);
    }
}

/**
 * @brief Test EulerAngles constructor with ZXZ Intrinsic Euler angles
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Intrinsic)
{
    using TestEulerAnglesZXZ_Intrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZXZ_Intrinsic angles(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestQuaternion q(angles);

    // Should produce a valid unit quaternion
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with ZXZ Intrinsic Euler angles - component finiteness
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Intrinsic_ComponentFiniteness)
{
    using TestEulerAnglesZXZ_Intrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZXZ_Intrinsic angles(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestQuaternion q(angles);

    // Verify all components are finite
    EXPECT_TRUE(std::isfinite(q.get_scalar_part().numerical_value_in(one)));
}

/**
 * @brief Test EulerAngles constructor with ZXZ Intrinsic Euler angles - vector component finiteness
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Intrinsic_VectorFiniteness)
{
    using TestEulerAnglesZXZ_Intrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZXZ_Intrinsic angles(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestQuaternion q(angles);
    auto vec = q.get_vector_part();

    EXPECT_TRUE(std::isfinite(vec.get_x().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vec.get_y().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vec.get_z().numerical_value_in(one)));
}

/**
 * @brief Test EulerAngles constructor with ZXZ Intrinsic quaternion normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Intrinsic_Normalization)
{
    using TestEulerAnglesZXZ_Intrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 15.0 * deg;
    const Angle angle2 = 30.0 * deg;
    const Angle angle3 = 45.0 * deg;

    TestEulerAnglesZXZ_Intrinsic intrinsicAngles(angle1, angle2, angle3);
    TestQuaternion qIntrinsic(intrinsicAngles);

    EXPECT_TRUE(math::nearly_equal(qIntrinsic.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with ZXZ Extrinsic quaternion normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Extrinsic_Normalization)
{
    using TestEulerAnglesZXZ_Extrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 15.0 * deg;
    const Angle angle2 = 30.0 * deg;
    const Angle angle3 = 45.0 * deg;

    TestEulerAnglesZXZ_Extrinsic extrinsicAngles(angle1, angle2, angle3);
    TestQuaternion qExtrinsic(extrinsicAngles);

    EXPECT_TRUE(math::nearly_equal(qExtrinsic.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor intrinsic vs extrinsic difference
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_IntrinsicExtrinsicDifference)
{
    using TestEulerAnglesZXZ_Intrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;
    using TestEulerAnglesZXZ_Extrinsic = EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 15.0 * deg;
    const Angle angle2 = 30.0 * deg;
    const Angle angle3 = 45.0 * deg;

    TestEulerAnglesZXZ_Intrinsic intrinsicAngles(angle1, angle2, angle3);
    TestEulerAnglesZXZ_Extrinsic extrinsicAngles(angle1, angle2, angle3);

    TestQuaternion qIntrinsic(intrinsicAngles);
    TestQuaternion qExtrinsic(extrinsicAngles);

    // They should generally be different (unless special case)
    bool areIdentical = (qIntrinsic.get_scalar_part() == qExtrinsic.get_scalar_part());
    auto vec1         = qIntrinsic.get_vector_part();
    auto vec2         = qExtrinsic.get_vector_part();
    areIdentical      = areIdentical && (vec1.get_x() == vec2.get_x()) && (vec1.get_y() == vec2.get_y()) &&
                   (vec1.get_z() == vec2.get_z());

    // For non-trivial angles, intrinsic and extrinsic should differ
    EXPECT_FALSE(areIdentical);
}

/**
 * @brief Test EulerAngles constructor with XYX Intrinsic Euler sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYX_Intrinsic)
{
    using TestEulerAnglesXYX_Intrinsic = EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYX_Intrinsic angles(80.0 * deg, 10.0 * deg, 45.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with YZY Extrinsic Euler sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_YZY_Extrinsic)
{
    using TestEulerAnglesYZY_Extrinsic = EulerAngles<RotationSequence::YZY, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesYZY_Extrinsic angles(120.0 * deg, 60.0 * deg, 30.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with XYZ Intrinsic Tait-Bryan angles - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Intrinsic_Normalization)
{
    using TestEulerAnglesXYZ_Intrinsic = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle roll  = 10.0 * deg;
    const Angle pitch = 20.0 * deg;
    const Angle yaw   = 30.0 * deg;

    TestEulerAnglesXYZ_Intrinsic angles(roll, pitch, yaw);
    TestQuaternion q(angles);

    // Should produce a valid unit quaternion
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with XYZ Intrinsic Tait-Bryan angles - scalar finiteness
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Intrinsic_ScalarFiniteness)
{
    using TestEulerAnglesXYZ_Intrinsic = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle roll  = 10.0 * deg;
    const Angle pitch = 20.0 * deg;
    const Angle yaw   = 30.0 * deg;

    TestEulerAnglesXYZ_Intrinsic angles(roll, pitch, yaw);
    TestQuaternion q(angles);

    // Verify components are finite and reasonable
    EXPECT_TRUE(std::isfinite(q.get_scalar_part().numerical_value_in(one)));
}

/**
 * @brief Test EulerAngles constructor with XYZ Intrinsic Tait-Bryan angles - vector finiteness
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Intrinsic_VectorFiniteness)
{
    using TestEulerAnglesXYZ_Intrinsic = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle roll  = 10.0 * deg;
    const Angle pitch = 20.0 * deg;
    const Angle yaw   = 30.0 * deg;

    TestEulerAnglesXYZ_Intrinsic angles(roll, pitch, yaw);
    TestQuaternion q(angles);
    auto vec = q.get_vector_part();

    EXPECT_TRUE(std::isfinite(vec.get_x().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vec.get_y().numerical_value_in(one)));
    EXPECT_TRUE(std::isfinite(vec.get_z().numerical_value_in(one)));
}

/**
 * @brief Test EulerAngles constructor with XYZ Intrinsic normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Intrinsic_Comparison_Normalization)
{
    using TestEulerAnglesXYZ_Intrinsic = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 25.0 * deg;
    const Angle angle2 = 35.0 * deg;
    const Angle angle3 = 45.0 * deg;

    TestEulerAnglesXYZ_Intrinsic intrinsicAngles(angle1, angle2, angle3);
    TestQuaternion qIntrinsic(intrinsicAngles);

    EXPECT_TRUE(math::nearly_equal(qIntrinsic.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with XYZ Extrinsic normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Extrinsic_Normalization)
{
    using TestEulerAnglesXYZ_Extrinsic = EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 25.0 * deg;
    const Angle angle2 = 35.0 * deg;
    const Angle angle3 = 45.0 * deg;

    TestEulerAnglesXYZ_Extrinsic extrinsicAngles(angle1, angle2, angle3);
    TestQuaternion qExtrinsic(extrinsicAngles);

    EXPECT_TRUE(math::nearly_equal(qExtrinsic.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor XYZ intrinsic vs extrinsic difference
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_IntrinsicExtrinsicDifference)
{
    using TestEulerAnglesXYZ_Intrinsic = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;
    using TestEulerAnglesXYZ_Extrinsic = EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    const Angle angle1 = 25.0 * deg;
    const Angle angle2 = 35.0 * deg;
    const Angle angle3 = 55.0 * deg;

    TestEulerAnglesXYZ_Intrinsic intrinsicAngles(angle1, angle2, angle3);
    TestEulerAnglesXYZ_Extrinsic extrinsicAngles(angle1, angle2, angle3);

    auto dcmIntrinsic = intrinsicAngles.to_dcm();
    auto dcmExtrinsic = extrinsicAngles.to_dcm();
    ASSERT_FALSE(nearly_equal(dcmIntrinsic, dcmExtrinsic, REL_TOL));

    TestQuaternion qIntrinsic(intrinsicAngles);
    TestQuaternion qExtrinsic(extrinsicAngles);

    // For non-zero angles, they should be different
    bool areIdentical = math::nearly_equal(qIntrinsic.get_scalar_part(), qExtrinsic.get_scalar_part(), REL_TOL, ABS_TOL);
    auto vec1    = qIntrinsic.get_vector_part();
    auto vec2    = qExtrinsic.get_vector_part();
    areIdentical = areIdentical && nearly_equal(vec1, vec2, REL_TOL, ABS_TOL);

    EXPECT_FALSE(areIdentical);
}

/**
 * @brief Test EulerAngles constructor with ZYX Intrinsic (aerospace sequence)
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZYX_Intrinsic)
{
    using TestEulerAnglesZYX_Intrinsic = EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZYX_Intrinsic angles(90.0 * deg, 0.0 * deg, 180.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with YXZ Extrinsic
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_YXZ_Extrinsic)
{
    using TestEulerAnglesYXZ_Extrinsic = EulerAngles<RotationSequence::YXZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesYXZ_Extrinsic angles(45.0 * deg, 90.0 * deg, 135.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with zero angles (identity rotation) - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZeroAngles_Normalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ zeroAngles(0.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(zeroAngles);

    // Should produce identity or near-identity quaternion
    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with zero angles (identity rotation) - scalar part
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZeroAngles_ScalarPart)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ zeroAngles(0.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(zeroAngles);

    // Scalar part should be ±1, vector should be near zero
    EXPECT_TRUE(math::nearly_equal(abs(q.get_scalar_part()), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with zero angles (identity rotation) - vector parts
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZeroAngles_VectorParts)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ zeroAngles(0.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(zeroAngles);
    auto vec = q.get_vector_part();

    EXPECT_TRUE(math::nearly_equal(vec.get_x(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec.get_y(), 0.0 * one, REL_TOL, ABS_TOL));
    EXPECT_TRUE(math::nearly_equal(vec.get_z(), 0.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with 180-degree rotations - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_180DegreeRotation_Normalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ largeAngles(180.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(largeAngles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with 180-degree rotations - scalar part
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_180DegreeRotation_ScalarPart)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ largeAngles(180.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(largeAngles);

    // Should have zero or near-zero scalar part for 180° rotation
    EXPECT_TRUE(math::nearly_equal(abs(q.get_scalar_part()), 0.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with full 360-degree rotation
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_360DegreeRotation)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ fullRotation(360.0 * deg, 0.0 * deg, 0.0 * deg);
    TestQuaternion q(fullRotation);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
    // Should be equivalent to identity (angles are wrapped)
}

/**
 * @brief Test EulerAngles constructor with negative angles - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_NegativeAngles_Normalization)
{
    using TestEulerAnglesZXZ = EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZXZ negativeAngles(-30.0 * deg, -45.0 * deg, -60.0 * deg);
    TestQuaternion q(negativeAngles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with positive equivalent angles - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_PositiveEquivalentAngles_Normalization)
{
    using TestEulerAnglesZXZ = EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    // Compare with positive equivalent
    TestEulerAnglesZXZ positiveAngles(330.0 * deg, 315.0 * deg, 300.0 * deg);
    TestQuaternion qPos(positiveAngles);

    // Should represent the same or equivalent rotation
    EXPECT_TRUE(math::nearly_equal(qPos.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with very small angles - normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_SmallAngles_Normalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ smallAngles(1e-6 * deg, 1e-5 * deg, 1e-4 * deg);
    TestQuaternion q(smallAngles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with very small angles - near identity
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_SmallAngles_NearIdentity)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ smallAngles(1e-6 * deg, 1e-5 * deg, 1e-4 * deg);
    TestQuaternion q(smallAngles);

    // Should be very close to identity
    EXPECT_GT(abs(q.get_scalar_part()), 0.999 * one);
}

/**
 * @brief Test EulerAngles to Quaternion equivalence with DCM conversion - direct normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_DCMEquivalence_DirectNormalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    const Angle roll  = 30.0 * deg;
    const Angle pitch = 45.0 * deg;
    const Angle yaw   = 60.0 * deg;

    TestEulerAnglesXYZ angles(roll, pitch, yaw);

    // Direct construction from EulerAngles
    TestQuaternion qDirect(angles);

    EXPECT_TRUE(math::nearly_equal(qDirect.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles to Quaternion equivalence with DCM conversion - DCM normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_DCMEquivalence_DCMNormalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;
    using TestDCM            = DirectionCosineMatrix<TestFrame1, TestFrame2>;

    const Angle roll  = 30.0 * deg;
    const Angle pitch = 45.0 * deg;
    const Angle yaw   = 60.0 * deg;

    TestEulerAnglesXYZ angles(roll, pitch, yaw);

    // Construction via DCM
    TestDCM dcm = angles.to_dcm();
    TestQuaternion qViaDCM(dcm);

    EXPECT_TRUE(math::nearly_equal(qViaDCM.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles to Quaternion equivalence with DCM conversion - equivalence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_DCMEquivalence_Equivalence)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;
    using TestDCM            = DirectionCosineMatrix<TestFrame1, TestFrame2>;

    const Angle roll  = 30.0 * deg;
    const Angle pitch = 45.0 * deg;
    const Angle yaw   = 60.0 * deg;

    TestEulerAnglesXYZ angles(roll, pitch, yaw);

    // Direct construction from EulerAngles
    TestQuaternion qDirect(angles);

    // Construction via DCM
    TestDCM dcm = angles.to_dcm();
    TestQuaternion qViaDCM(dcm);

    // Should represent the same rotation (accounting for quaternion double-cover)
    bool areEqual = (abs(qDirect.get_scalar_part() - qViaDCM.get_scalar_part()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_x() - qViaDCM.get_vector_part().get_x()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_y() - qViaDCM.get_vector_part().get_y()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_z() - qViaDCM.get_vector_part().get_z()) < REL_TOL) ||
                    (abs(qDirect.get_scalar_part() + qViaDCM.get_scalar_part()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_x() + qViaDCM.get_vector_part().get_x()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_y() + qViaDCM.get_vector_part().get_y()) < REL_TOL &&
                     abs(qDirect.get_vector_part().get_z() + qViaDCM.get_vector_part().get_z()) < REL_TOL);

    EXPECT_TRUE(areEqual) << "Direct and DCM-based quaternion construction should give equivalent results";
}

/**
 * @brief Test EulerAngles constructor with ZXZ Euler sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXZ_Coverage)
{
    using TestEulerAngles = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAngles angles(30.0 * deg, 60.0 * deg, 90.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with XYX Euler sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYX_Coverage)
{
    using TestEulerAngles = EulerAngles<RotationSequence::XYX, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAngles angles(45.0 * deg, 30.0 * deg, 15.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with XYZ Tait-Bryan sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_Coverage)
{
    using TestEulerAngles = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAngles angles(15.0 * deg, 30.0 * deg, 45.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with YZX Tait-Bryan sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_YZX_Coverage)
{
    using TestEulerAngles = EulerAngles<RotationSequence::YZX, RotationType::EXTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAngles angles(60.0 * deg, 45.0 * deg, 30.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor with ZXY Tait-Bryan sequence
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZXY_Coverage)
{
    using TestEulerAngles = EulerAngles<RotationSequence::ZXY, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAngles angles(90.0 * deg, 0.0 * deg, 45.0 * deg);
    TestQuaternion q(angles);

    EXPECT_TRUE(math::nearly_equal(q.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor XYZ vs ZYX normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_XYZ_vs_ZYX_Normalization)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ anglesXYZ(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestQuaternion qXYZ(anglesXYZ);

    EXPECT_TRUE(math::nearly_equal(qXYZ.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test EulerAngles constructor ZYX normalization
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_ZYX_vs_XYZ_Normalization)
{
    using TestEulerAnglesZYX = EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesZYX anglesZYX(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestQuaternion qZYX(anglesZYX);

    EXPECT_TRUE(math::nearly_equal(qZYX.norm(), 1.0 * one, REL_TOL, ABS_TOL));
}

/**
 * @brief Test different angle sequences produce different rotations
 */
TEST_F(QuaternionTest, EulerAnglesConstructor_DifferentSequencesDifferentResults)
{
    using TestEulerAnglesXYZ = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame1, TestFrame2>;
    using TestEulerAnglesZYX = EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame1, TestFrame2>;

    TestEulerAnglesXYZ anglesXYZ(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestEulerAnglesZYX anglesZYX(30.0 * deg, 45.0 * deg, 60.0 * deg);

    TestQuaternion qXYZ(anglesXYZ);
    TestQuaternion qZYX(anglesZYX);

    // They should represent different rotations
    bool areIdentical = (qXYZ.get_scalar_part() == qZYX.get_scalar_part());
    auto vecXYZ       = qXYZ.get_vector_part();
    auto vecZYX       = qZYX.get_vector_part();
    areIdentical      = areIdentical && (vecXYZ.get_x() == vecZYX.get_x()) && (vecXYZ.get_y() == vecZYX.get_y()) &&
                   (vecXYZ.get_z() == vecZYX.get_z());

    EXPECT_FALSE(areIdentical) << "Different angle sequences should produce different rotations";
}
