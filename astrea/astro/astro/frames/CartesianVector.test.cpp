#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using TestFrame  = frames::earth::icrf;
using TestVector = CartesianVector<Unitless, TestFrame>;

class CartesianVectorTest : public testing::Test {
  public:
    CartesianVectorTest() {}

    void SetUp() override {}

    Unitless REL_TOL = 1.0e-10 * one;

    TestVector vec1 = { 1.0 * one, 0.0 * one, 0.0 * one };
    TestVector vec2 = { 0.0 * one, 1.0 * one, 0.0 * one };
    TestVector vec3 = { 0.0 * one, 0.0 * one, 1.0 * one };
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CartesianVectorTest, TestComponentConstructor)
{
    ASSERT_NO_THROW(TestVector(1.0 * one, 2.0 * one, 3.0 * one));
    ASSERT_NO_THROW(TestVector());
}

TEST_F(CartesianVectorTest, TestCopyConstructor)
{
    // Copy constructor within the same frame should work
    ASSERT_NO_THROW(TestVector vecCopy(vec1));
    auto vecCopy = TestVector(vec1);
    ASSERT_EQ_CART_VEC(vec1, vecCopy, REL_TOL);

    // Copy constructor between different frames should not compile
    // CartesianVector<Unitless, frames::earth::j2000> vecInvalidCopy(vec1);
}

TEST_F(CartesianVectorTest, TestMoveConstructor)
{
    // Move constructor within the same frame should work
    auto vecTemp = TestVector(1.0 * one, 2.0 * one, 3.0 * one);
    ASSERT_NO_THROW(TestVector vecMove(std::move(vecTemp)));
    auto vecMove = TestVector(std::move(vecTemp));
    ASSERT_EQ_CART_VEC(vecMove, TestVector(1.0 * one, 2.0 * one, 3.0 * one), REL_TOL);

    // Move constructor between different frames should not compile
    // CartesianVector<Unitless, frames::earth::j2000> vecInvalidMove(std::move(vec1));
}

TEST_F(CartesianVectorTest, TestForceFrameConversion)
{
    // Force frame conversion should work between different frames
    ASSERT_NO_THROW(vec1.force_frame_conversion<frames::earth::j2000>());
    auto vecConverted = vec1.force_frame_conversion<frames::earth::icrf>();
    ASSERT_EQ_CART_VEC(vecConverted, TestVector(1.0 * one, 0.0 * one, 0.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestAccessOperators)
{
    // Non-const access
    vec1[0] = 5.0 * one;
    vec1[1] = 6.0 * one;
    vec1[2] = 7.0 * one;
    ASSERT_EQ_CART_VEC(vec1, TestVector(5.0 * one, 6.0 * one, 7.0 * one), REL_TOL);

    // Const access
    const auto& constVec = vec1;
    EXPECT_EQ(constVec[0], 5.0 * one);
    EXPECT_EQ(constVec[1], 6.0 * one);
    EXPECT_EQ(constVec[2], 7.0 * one);
}

TEST_F(CartesianVectorTest, TestGetters)
{
    EXPECT_EQ(vec1.get_x(), 1.0 * one);
    EXPECT_EQ(vec1.get_y(), 0.0 * one);
    EXPECT_EQ(vec1.get_z(), 0.0 * one);

    vec1.get_x() = 2.0 * one;
    vec1.get_y() = 3.0 * one;
    vec1.get_z() = 4.0 * one;
    ASSERT_EQ_CART_VEC(vec1, TestVector(2.0 * one, 3.0 * one, 4.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestEqualityOperators)
{
    // Equality within the same frame
    auto vecSame = TestVector(1.0 * one, 0.0 * one, 0.0 * one);
    EXPECT_TRUE(vec1 == vecSame);

    auto vecDifferent = TestVector(0.0 * one, 1.0 * one, 0.0 * one);
    EXPECT_FALSE(vec1 == vecDifferent);

    // Equality between different frames should always be false
    CartesianVector<Unitless, frames::earth::j2000> vecOtherFrame(1.0 * one, 0.0 * one, 0.0 * one);
    EXPECT_FALSE(vec1 == vecOtherFrame);
}

TEST_F(CartesianVectorTest, TestAdditionAndSubtraction)
{
    // Addition within the same frame
    auto vecSum = vec1 + vec2;
    ASSERT_EQ_CART_VEC(vecSum, TestVector(1.0 * one, 1.0 * one, 0.0 * one), REL_TOL);

    vecSum += vec3;
    ASSERT_EQ_CART_VEC(vecSum, TestVector(1.0 * one, 1.0 * one, 1.0 * one), REL_TOL);

    // Subtraction within the same frame
    auto vecDiff = vecSum - vec1;
    ASSERT_EQ_CART_VEC(vecDiff, TestVector(0.0 * one, 1.0 * one, 1.0 * one), REL_TOL);

    vecDiff -= vec2;
    ASSERT_EQ_CART_VEC(vecDiff, TestVector(0.0 * one, 0.0 * one, 1.0 * one), REL_TOL);

    // Negation
    auto vecNeg = -vecDiff;
    ASSERT_EQ_CART_VEC(vecNeg, TestVector(0.0 * one, 0.0 * one, -1.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestScalarMultiplicationAndDivision)
{
    // Scalar multiplication
    auto vecScaled = vec1 * 3.0 * one;
    ASSERT_EQ_CART_VEC(vecScaled, TestVector(3.0 * one, 0.0 * one, 0.0 * one), REL_TOL);

    vecScaled *= 2.0 * one;
    ASSERT_EQ_CART_VEC(vecScaled, TestVector(6.0 * one, 0.0 * one, 0.0 * one), REL_TOL);

    // Scalar division
    auto vecDivided = vecScaled / (2.0 * one);
    ASSERT_EQ_CART_VEC(vecDivided, TestVector(3.0 * one, 0.0 * one, 0.0 * one), REL_TOL);

    vecDivided /= (3.0 * one);
    ASSERT_EQ_CART_VEC(vecDivided, TestVector(1.0 * one, 0.0 * one, 0.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestUnitedMultiplicationAndDivision)
{
    // Scalar multiplication
    auto vecScaled = vec1 * 3.0 * km;
    ASSERT_EQ_CART_VEC(vecScaled, CartesianVector<Distance, TestFrame>(3.0 * km, 0.0 * km, 0.0 * km), REL_TOL);

    vecScaled *= 2.0 * one;
    ASSERT_EQ_CART_VEC(vecScaled, CartesianVector<Distance, TestFrame>(6.0 * km, 0.0 * km, 0.0 * km), REL_TOL);

    // Scalar division
    auto vecDivided = vecScaled / (2.0 * s);
    ASSERT_EQ_CART_VEC(vecDivided, CartesianVector<Velocity, TestFrame>(3.0 * km / s, 0.0 * km / s, 0.0 * km / s), REL_TOL);

    vecDivided /= (3.0 * one);
    ASSERT_EQ_CART_VEC(vecDivided, CartesianVector<Velocity, TestFrame>(1.0 * km / s, 0.0 * km / s, 0.0 * km / s), REL_TOL);
}

TEST_F(CartesianVectorTest, TestDotAndCrossProduct)
{
    // Dot product
    auto dotProduct = vec1.dot(vec2);
    EXPECT_EQ(dotProduct, 0.0 * one);

    dotProduct = vec1.dot(vec1);
    EXPECT_EQ(dotProduct, 1.0 * one);

    // Cross product
    auto crossProduct = vec1.cross(vec2);
    ASSERT_EQ_CART_VEC(crossProduct, TestVector(0.0 * one, 0.0 * one, 1.0 * one), REL_TOL);

    crossProduct = vec2.cross(vec3);
    ASSERT_EQ_CART_VEC(crossProduct, TestVector(1.0 * one, 0.0 * one, 0.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestNormAndUnit)
{
    // Norm
    auto normVec1 = vec1.norm();
    EXPECT_EQ(normVec1, 1.0 * one);

    auto normVec2 = (vec1 + vec2).norm();
    EXPECT_EQ(normVec2, sqrt(2.0) * one);

    // Unit vector
    auto unitVec1 = vec1.unit();
    ASSERT_EQ_CART_VEC(unitVec1, TestVector(1.0 * one, 0.0 * one, 0.0 * one), REL_TOL);

    auto unitVec2   = (vec1 + vec2).unit();
    double invSqrt2 = 1.0 / sqrt(2.0);
    ASSERT_EQ_CART_VEC(unitVec2, TestVector(invSqrt2 * one, invSqrt2 * one, 0.0 * one), REL_TOL);
}

TEST_F(CartesianVectorTest, TestAngleBetweenVectors)
{
    // Angle between orthogonal vectors
    auto angle1 = vec1.offset_angle(vec2);
    ASSERT_EQ_QUANTITY(angle1, Angle(M_PI_2 * rad), REL_TOL);

    // Angle between identical vectors
    auto angle2 = vec1.offset_angle(vec1);
    ASSERT_EQ_QUANTITY(angle2, Angle(0.0 * rad), REL_TOL);

    // Angle between opposite vectors
    auto angle3 = vec1.offset_angle(-vec1);
    ASSERT_EQ_QUANTITY(angle3, Angle(M_PI * rad), REL_TOL);
}

TEST_F(CartesianVectorTest, TestFrameTransformation)
{
    // Frame transformation to the same frame should return the same vector
    TestVector vecInSameFrame = vec1.in_frame<TestFrame>(Date());
    ASSERT_EQ_CART_VEC(vecInSameFrame, vec1, REL_TOL);

    // Frame transformation to a different frame should compile and return a vector in the new frame
    ASSERT_NO_THROW(vec1.in_frame<frames::earth::j2000>(Date()));
    // ASSERT_NO_THROW(vec1.with_respect_to_frame<frames::earth::j2000>(Date())); // TODO: Fix this function

    // TODO: Let's get some regressions for these
}

// TEST_F(CartesianVectorTest, TestTranslationAndOffset)
// {
//     // Translation between frames with same axes but different origins should compile
//     CartesianVector<Unitless, frames::earth::j2000> vecJ2000(1.0 * one, 0.0 * one, 0.0 * one);
//     ASSERT_NO_THROW(vec1.translate<frames::earth::j2000, frames::earth::icrf>(vecJ2000));
//     ASSERT_NO_THROW(vec1.offset<frames::earth::j2000, frames::earth::icrf>(vecJ2000));
// }

TEST_F(CartesianVectorTest, TestOutputStream)
{
    std::ostringstream oss;
    oss << vec1;
    EXPECT_EQ(oss.str(), "[1, 0, 0]");

    CartesianVector<Unitless, frames::earth::j2000> vecOtherFrame(1.0 * one, 2.0 * one, 3.0 * one);
    std::ostringstream ossOther;
    ossOther << vecOtherFrame;
    EXPECT_EQ(ossOther.str(), "[1, 2, 3]");
}
