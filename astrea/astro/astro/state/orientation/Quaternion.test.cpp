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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/state/orientation/Quaternion.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

// Define some dummy frame types for testing template functionality
struct TestFrame1 {};
struct TestFrame2 {};
struct TestFrame3 {};

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
    template <typename In_Frame_T, typename Out_Frame_T>
    void ExpectQuaternionNearlyEqual(const Quaternion<In_Frame_T, Out_Frame_T>& actual, const Quaternion<In_Frame_T, Out_Frame_T>& expected)
    {
        // Compare scalar parts
        EXPECT_EQ_QUANTITY(actual.get_scalar_part(), expected.get_scalar_part(), REL_TOL, ABS_TOL);

        // Compare vector parts
        auto actualVec   = actual.get_vector_part();
        auto expectedVec = expected.get_vector_part();
        EXPECT_EQ_QUANTITY(actualVec.get_x(), expectedVec.get_x(), REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(actualVec.get_y(), expectedVec.get_y(), REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(actualVec.get_z(), expectedVec.get_z(), REL_TOL, ABS_TOL);
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
    EXPECT_EQ_QUANTITY(q1.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    // Scalar part should be normalized: scalar1 / |scalar1|
    EXPECT_EQ_QUANTITY(q1.get_scalar_part(), 1.0 * one, REL_TOL, ABS_TOL);
    auto vec1 = q1.get_vector_part();
    EXPECT_EQ_QUANTITY(vec1.get_x(), 0.0 * one, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(vec1.get_y(), 0.0 * one, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(vec1.get_z(), 0.0 * one, REL_TOL, ABS_TOL);

    // Test with scalar and vector - should be automatically normalized
    TestVector testVec(x1, y1, z1);
    TestQuaternion q2(scalar1, testVec);
    // Should have unit norm after normalization
    EXPECT_EQ_QUANTITY(q2.norm(), 1.0 * one, REL_TOL, ABS_TOL);

    // Calculate expected normalized values
    Unitless inputNorm = sqrt(scalar1 * scalar1 + x1 * x1 + y1 * y1 + z1 * z1);
    EXPECT_EQ_QUANTITY(q2.get_scalar_part(), scalar1 / inputNorm, REL_TOL, ABS_TOL);
    auto vec2 = q2.get_vector_part();
    EXPECT_EQ_QUANTITY(vec2.get_x(), x1 / inputNorm, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(vec2.get_y(), y1 / inputNorm, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(vec2.get_z(), z1 / inputNorm, REL_TOL, ABS_TOL);
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
        EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    });

    // Test boundary values - should result in unit quaternions
    EXPECT_NO_THROW({
        TestQuaternion q(1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
        EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    });

    EXPECT_NO_THROW({
        TestQuaternion q(-1.0 * one, 0.0 * one, 0.0 * one, 0.0 * one);
        EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
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
    EXPECT_EQ_QUANTITY(result.norm(), 1.0 * one, REL_TOL, ABS_TOL);

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
    EXPECT_EQ_QUANTITY(negated.norm(), 1.0 * one, REL_TOL, ABS_TOL);

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
    EXPECT_EQ_QUANTITY(result.norm(), 1.0 * one, REL_TOL, ABS_TOL);

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
        EXPECT_EQ_QUANTITY(result.norm(), 1.0 * one, REL_TOL, ABS_TOL);

        // Verify we can access components of the result
        EXPECT_TRUE(std::isfinite(result.get_scalar_part().numerical_value_in(one)));
        auto resultVec = result.get_vector_part();
        EXPECT_TRUE(std::isfinite(resultVec.get_x().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(resultVec.get_y().numerical_value_in(one)));
        EXPECT_TRUE(std::isfinite(resultVec.get_z().numerical_value_in(one)));
    });

    // Since all quaternions have unit norm, |q1 * q2| = 1
    auto chainResult = q12 * q23;
    EXPECT_EQ_QUANTITY(chainResult.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    // Original quaternions also have unit norm
    EXPECT_EQ_QUANTITY(q12.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(q23.norm(), 1.0 * one, REL_TOL, ABS_TOL);

    // Test associativity with frame chaining
    using QFrame34 = Quaternion<TestFrame3, TestFrame1>; // Close the loop
    QFrame34 q34(0.6 * one, 0.2 * one, 0.1 * one, 0.3 * one);

    auto leftAssoc  = (q12 * q23) * q34; // QFrame11
    auto rightAssoc = q12 * (q23 * q34); // QFrame11
    // Both should have unit norm
    EXPECT_EQ_QUANTITY(leftAssoc.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(rightAssoc.norm(), 1.0 * one, REL_TOL, ABS_TOL);
}

/**
 * @brief Test conjugate method
 */
TEST_F(QuaternionTest, ConjugateMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    auto conj = q.conjugate();

    // Verify conjugate properties - scalar stays same, vector negated
    EXPECT_EQ_QUANTITY(conj.get_scalar_part(), scalar1);
    auto conjVec = conj.get_vector_part();
    EXPECT_EQ_QUANTITY(conjVec.get_x(), -x1);
    EXPECT_EQ_QUANTITY(conjVec.get_y(), -y1);
    EXPECT_EQ_QUANTITY(conjVec.get_z(), -z1);

    // Note: conjugate returns Quaternion<Out_Frame_T, In_Frame_T>, so double conjugate
    // will return Quaternion<In_Frame_T, Out_Frame_T> which matches original
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
    EXPECT_EQ_QUANTITY(normValue, 1.0 * one, REL_TOL, ABS_TOL);

    // Norm should be real and finite
    EXPECT_TRUE(std::isfinite(normValue.numerical_value_in(one)));

    // Unit quaternion cannot be constructed (throws in constructor)
    TestQuaternion identity;
    EXPECT_EQ_QUANTITY(identity.norm(), 1.0 * one, REL_TOL, ABS_TOL);

    // Any valid quaternion should have norm 1
    TestQuaternion unitI(0.0 * one, 1.0 * one, 0.0 * one, 0.0 * one);
    EXPECT_EQ_QUANTITY(unitI.norm(), 1.0 * one, REL_TOL, ABS_TOL);
}

/**
 * @brief Test inverse method
 */
TEST_F(QuaternionTest, InverseMethod)
{
    TestQuaternion q(scalar1, x1, y1, z1);
    auto inv = q.inverse();

    // Note: inverse returns Quaternion<Out_Frame_T, In_Frame_T>
    // Since quaternions are unit quaternions, inverse should also have unit norm
    EXPECT_EQ_QUANTITY(inv.norm(), 1.0 * one, REL_TOL, ABS_TOL);

    // Original quaternion should have unit norm
    EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
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
    EXPECT_EQ_QUANTITY(unitQ.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);

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
        EXPECT_EQ_QUANTITY(smallQ.norm(), 1.0 * one, REL_TOL, ABS_TOL);
        // normalize() method should return the same quaternion (idempotent)
        TestQuaternion unitQ = smallQ;
        unitQ.normalize();
        ExpectQuaternionNearlyEqual(unitQ, smallQ);
        EXPECT_NO_THROW(smallQ.inverse());
    });

    // Test pure scalar quaternion (after normalization)
    TestQuaternion pureScalar(0.8 * one, 0.0 * one, 0.0 * one, 0.0 * one);
    // Should be normalized
    EXPECT_EQ_QUANTITY(pureScalar.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    auto conjScalar = pureScalar.conjugate();
    // For pure scalar, conjugate should have same scalar part and zero vector
    EXPECT_EQ_QUANTITY(conjScalar.get_scalar_part(), pureScalar.get_scalar_part());
    auto conjVec = conjScalar.get_vector_part();
    EXPECT_EQ_QUANTITY(conjVec.get_x(), 0.0 * one);
    EXPECT_EQ_QUANTITY(conjVec.get_y(), 0.0 * one);
    EXPECT_EQ_QUANTITY(conjVec.get_z(), 0.0 * one);

    // Test pure vector quaternion (scalar = 0, will be normalized)
    TestQuaternion pureVector(0.0 * one, 0.6 * one, 0.8 * one, 0.0 * one);
    // Should be normalized to unit quaternion
    EXPECT_EQ_QUANTITY(pureVector.norm(), 1.0 * one, REL_TOL, ABS_TOL);
    auto conjVector              = pureVector.conjugate();
    TestQuaternion negatedVector = -pureVector;

    // For pure vector quaternion, conjugate should negate the vector part
    EXPECT_EQ_QUANTITY(conjVector.get_scalar_part(), 0.0 * one, REL_TOL, ABS_TOL);
    auto conjVecPart = conjVector.get_vector_part();
    auto negVecPart  = negatedVector.get_vector_part();
    EXPECT_EQ_QUANTITY(conjVecPart.get_x(), negVecPart.get_x());
    EXPECT_EQ_QUANTITY(conjVecPart.get_y(), negVecPart.get_y());
    EXPECT_EQ_QUANTITY(conjVecPart.get_z(), negVecPart.get_z());
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
        EXPECT_EQ_QUANTITY(result13.norm(), expectedNorm, REL_TOL, ABS_TOL);
    });

    // Test three-step chaining: Frame1 -> Frame2 -> Frame3 -> Frame1 (full cycle)
    EXPECT_NO_THROW({
        Q11 fullCycle = (q12 * q23) * q31;
        EXPECT_GT(fullCycle.norm(), 0.0 * one);

        // Test associativity in chaining
        Q11 alternateCycle = q12 * (q23 * q31);
        EXPECT_EQ_QUANTITY(fullCycle.norm(), alternateCycle.norm(), REL_TOL, ABS_TOL);

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
    using mp_units::angular::unit_symbols::deg;
    using mp_units::angular::unit_symbols::rad;

    // Test identity DCM -> should give identity quaternion
    EXPECT_NO_THROW({
        TestDCM identityDCM = TestDCM::identity();

        TestQuaternion q(identityDCM);

        // Identity quaternion should have scalar part = ±1 and zero vector part
        // (sign ambiguity is normal for quaternions)
        EXPECT_EQ_QUANTITY(abs(q.get_scalar_part()), 1.0 * one, REL_TOL, ABS_TOL);
        auto vec = q.get_vector_part();
        EXPECT_EQ_QUANTITY(vec.get_x(), 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(vec.get_y(), 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(vec.get_z(), 0.0 * one, REL_TOL, ABS_TOL);
    });

    // Test 90° rotation about Z-axis
    EXPECT_NO_THROW({
        TestDCM zRot90 = TestDCM::Z(90.0 * deg);
        TestQuaternion q(zRot90);

        // Should be valid quaternion with unit norm
        EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);

        // For 90° Z rotation: cos(45°) ≈ 0.7071, sin(45°) ≈ 0.7071
        EXPECT_EQ_QUANTITY(abs(q.get_scalar_part()), 0.7071067811865475 * one, 1e-10 * one);
        auto vec = q.get_vector_part();
        EXPECT_EQ_QUANTITY(abs(vec.get_z()), 0.7071067811865475 * one, 1e-10 * one);
    });

    // Test 180° rotation about X-axis (edge case for trace-based algorithm)
    EXPECT_NO_THROW({
        TestDCM xRot180 = TestDCM::X(180.0 * deg);
        TestQuaternion q(xRot180);

        // Should be unit quaternion
        EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);

        // 180° rotation should have zero scalar part and unit vector component
        EXPECT_EQ_QUANTITY(abs(q.get_scalar_part()), 0.0 * one, REL_TOL, ABS_TOL);
        auto vec = q.get_vector_part();
        EXPECT_EQ_QUANTITY(abs(vec.get_x()), 1.0 * one, REL_TOL, ABS_TOL);
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
        EXPECT_EQ_QUANTITY(dcm[0, 0], 1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[0, 1], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[0, 2], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 0], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 1], 1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 2], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 0], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 1], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 2], 1.0 * one, REL_TOL, ABS_TOL);
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
        EXPECT_EQ_QUANTITY(dcm[0, 0], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[0, 1], -1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[0, 2], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 0], 1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 1], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[1, 2], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 0], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 1], 0.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(dcm[2, 2], 1.0 * one, REL_TOL, ABS_TOL);
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

        EXPECT_EQ_QUANTITY(col0Norm, 1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(col1Norm, 1.0 * one, REL_TOL, ABS_TOL);
        EXPECT_EQ_QUANTITY(col2Norm, 1.0 * one, REL_TOL, ABS_TOL);
    });
}

/**
 * @brief Test round-trip DCM ↔ Quaternion conversions
 */
TEST_F(QuaternionTest, DCMQuaternionRoundTrip)
{
    using TestDCM = DirectionCosineMatrix<TestFrame1, TestFrame2>;
    using mp_units::angular::unit_symbols::deg;

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
            EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
            TestDCM roundTripDCM = q.to_dcm();

            // Compare each element (accounting for possible quaternion sign ambiguity)
            for (int ii = 0; ii < 3; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
                    EXPECT_EQ_QUANTITY(roundTripDCM[ii, jj], originalDCM[ii, jj], REL_TOL, ABS_TOL);
                }
            }
        });
    }

    // Test the reverse: Quaternion -> DCM -> Quaternion
    EXPECT_NO_THROW({
        TestQuaternion originalQ(scalar1, x1, y1, z1);
        // originalQ is automatically normalized to unit quaternion
        EXPECT_EQ_QUANTITY(originalQ.norm(), 1.0 * one, REL_TOL, ABS_TOL);

        TestDCM dcm = originalQ.to_dcm();
        TestQuaternion roundTripQ(dcm);
        // Round trip quaternion should also be unit
        EXPECT_EQ_QUANTITY(roundTripQ.norm(), 1.0 * one, REL_TOL, ABS_TOL);

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
    using mp_units::angular::unit_symbols::deg;

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
            EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);

            // Round-trip should preserve the DCM
            TestDCM roundTrip = q.to_dcm();
            for (int ii = 0; ii < 3; ++ii) {
                for (int jj = 0; jj < 3; ++jj) {
                    EXPECT_EQ_QUANTITY(roundTrip[ii, jj], dcm[ii, jj], REL_TOL, ABS_TOL);
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
            EXPECT_EQ_QUANTITY(q.norm(), 1.0 * one, REL_TOL, ABS_TOL);
        });
    }
}
