#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <access/platforms/Antenna.hpp>

using namespace astro;
using namespace accesslib;

using namespace mp_units;
using mp_units::one;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::GHz;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;

template <typename T>
void compare_united_values(const T& first, const T& second, const double& absTol = 1.0e-4)
{
    ASSERT_NEAR(first.numerical_value_in(first.unit), second.numerical_value_in(first.unit), absTol);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.2
TEST(SatCommTest, Ex_12_2)
{
    Antenna antenna(3.0 * m, 0.55 * one, 12.0 * GHz, 1.0 * W);
    compare_united_values(antenna.gain(), 78275.53246 * one); // 48.93 dB (78162.78) according to text, but text rounds heavily
}
