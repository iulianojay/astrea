#include <cmath>
#include <gtest/gtest.h>
#include <math/trig.hpp>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

using namespace astrea;
using namespace astrea::math;
using mp_units::one;
using mp_units::angular::unit_symbols::rad;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TrigTest, Sinc)
{
    auto x      = 1.0 * rad;
    auto result = sinc(x);
    ASSERT_NEAR(result.numerical_value_ref_in(result.unit), std::sin(x.numerical_value_ref_in(x.unit)), 1e-10);
}

TEST(TrigTest, Cosh)
{
    auto x      = 1.0 * rad;
    auto result = cosh(x);
    ASSERT_NEAR(result.numerical_value_ref_in(result.unit), std::cosh(x.numerical_value_ref_in(x.unit)), 1e-10);
}

TEST(TrigTest, Sinh)
{
    auto x      = 1.0 * rad;
    auto result = sinh(x);
    ASSERT_NEAR(result.numerical_value_ref_in(result.unit), std::sinh(x.numerical_value_ref_in(x.unit)), 1e-10);
}

TEST(TrigTest, CylBesselJ)
{
    auto x      = 1.0 * one;
    auto result = cyl_bessel_j(0.0, x);
    ASSERT_NEAR(result.numerical_value_ref_in(result.unit), std::cyl_bessel_j(0.0, 1.0), 1e-10);
}

TEST(TrigTest, AssocLegendre)
{
    auto x      = 0.5 * one;
    auto result = assoc_legendre(1, 0, x);
    ASSERT_NEAR(result.numerical_value_ref_in(result.unit), std::assoc_legendre(1, 0, 0.5), 1e-10);
}

// TEST(TrigTest, Atan3)
// {
//     ASSERT_NEAR(atan3(1.0, 1.0), std::atan2(1.0, 1.0), 1e-10);
//     ASSERT_NEAR(atan3(-1.0, 1.0), std::atan2(-1.0, 1.0), 1e-10);
//     ASSERT_NEAR(atan3(1.0, -1.0), std::atan2(1.0, -1.0), 1e-10);
//     ASSERT_NEAR(atan3(-1.0, -1.0), std::atan2(-1.0, -1.0), 1e-10);
// }
