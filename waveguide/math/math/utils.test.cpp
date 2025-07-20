#include <gtest/gtest.h>

#include <math/utils.hpp>

using namespace waveguide;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Math, ArrayNormTypes)
{
    std::array<int, 3> arrayInt{ 3, 4 };
    std::array<float, 3> arrayFloat{ 3.0, 4.0 };
    std::array<double, 3> arrayDouble{ 3.0, 4.0 };

    int normInt       = math::normalize(arrayInt);
    float normFloat   = math::normalize(arrayFloat);
    double normDouble = math::normalize(arrayDouble);

    ASSERT_EQ(normInt, 5);
    ASSERT_EQ(normFloat, 5.0);
    ASSERT_EQ(normDouble, 5.0);
}

TEST(Math, ArrayPNorm)
{
    std::array<double, 3> array{ 3.0, 4.0 };

    double norm1 = math::normalize(array, 1);
    double norm2 = math::normalize(array, 2);
    double norm3 = math::normalize(array, 3);

    ASSERT_EQ(norm1, 7.0);
    ASSERT_EQ(norm2, 5.0);
    ASSERT_NEAR(norm3, 4.4979, 1e-4);
}

TEST(Math, VectorNormTypes)
{
    std::vector<int> vectorInt{ 3, 4 };
    std::vector<float> vectorFloat{ 3.0, 4.0 };
    std::vector<double> vectorDouble{ 3.0, 4.0 };

    int normInt       = math::normalize(vectorInt);
    float normFloat   = math::normalize(vectorFloat);
    double normDouble = math::normalize(vectorDouble);

    ASSERT_EQ(normInt, 5);
    ASSERT_EQ(normFloat, 5.0);
    ASSERT_EQ(normDouble, 5.0);
}

TEST(Math, VectorPNorm)
{
    std::vector<double> vector{ 3.0, 4.0 };

    double norm1 = math::normalize(vector, 1);
    double norm2 = math::normalize(vector, 2);
    double norm3 = math::normalize(vector, 3);

    ASSERT_EQ(norm1, 7.0);
    ASSERT_EQ(norm2, 5.0);
    ASSERT_NEAR(norm3, 4.4979, 1e-4);
}

TEST(Math, VectorMeanType)
{
    std::vector<int> vectorInt{ 3, 4 };
    std::vector<float> vectorFloat{ 3.0, 4.0 };
    std::vector<double> vectorDouble{ 3.0, 4.0 };

    int meanInt       = math::mean(vectorInt);
    float meanFloat   = math::mean(vectorFloat);
    double meanDouble = math::mean(vectorDouble);

    ASSERT_EQ(meanInt, 3);
    ASSERT_EQ(meanFloat, 3.5);
    ASSERT_EQ(meanDouble, 3.5);
}

TEST(Math, InvTan3Type)
{
    int ansInt       = math::atan3(1, 1);
    float ansFloat   = math::atan3(1.0, 1.0);
    double ansDouble = math::atan3(1.0, 1.0);

    ASSERT_EQ(ansInt, 0);
    ASSERT_NEAR(ansFloat, M_PI_4, 1e-6);
    ASSERT_NEAR(ansDouble, M_PI_4, 1e-6);
}

TEST(Math, InvTan3Quadrant)
{
    ASSERT_NEAR(math::atan3(1.0, 1.0), M_PI_4, 1e-6);
    ASSERT_NEAR(math::atan3(1.0, -1.0), 3 * M_PI_4, 1e-6);
    ASSERT_NEAR(math::atan3(-1.0, -1.0), 5 * M_PI_4, 1e-6);
    ASSERT_NEAR(math::atan3(-1.0, 1.0), 7 * M_PI_4, 1e-6);

    ASSERT_NEAR(math::atan3(0.0, 1.0), 0.0, 1e-6);
    ASSERT_NEAR(math::atan3(1.0, 0.0), M_PI_2, 1e-6);
    ASSERT_NEAR(math::atan3(0.0, -1.0), M_PI, 1e-6);
    ASSERT_NEAR(math::atan3(-1.0, 0.0), 3 * M_PI_2, 1e-6);
}