#include <gtest/gtest.h>

#include <complex>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/angular_elements/Quaternion.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using namespace std::complex_literals;

class QuaternionTest : public testing::Test {
  public:
    QuaternionTest() {}

    void SetUp() override {}

    Quaternion q;
    Unitless q0      = 1.0 * one;
    quantity<one> q1 = std::complex<double>(0.0, 1.0) * one;
    quantity<one> q2 = std::complex<double>(0.0, 1.0) * one;
    quantity<one> q3 = std::complex<double>(0.0, 1.0) * one;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(QuaternionTest, DefaultConstructor) { ASSERT_NO_THROW(Quaternion()); }

TEST_F(QuaternionTest, Constructor) { ASSERT_NO_THROW(Quaternion(q0, q1, q2, q3)); }

TEST_F(QuaternionTest, VectorConstructor) { ASSERT_NO_THROW(Quaternion(q0, { q1, q2, q3 })); }
