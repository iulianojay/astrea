#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class ThrusterTest : public testing::Test {
  public:
    ThrusterTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Thrust thrust{ 1.0 * N };
    ThrusterParameters params{ thrust };
    Spacecraft sat;
    Thruster thruster{ sat, params };
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ThrusterTest, GetId) { ASSERT_EQ(thruster.get_id(), std::hash<Thrust>()(thrust)); }

TEST_F(ThrusterTest, GetImpulsiveDeltaV)
{
    ASSERT_EQ_QUANTITY(thruster.get_impulsive_delta_v(), thrust / sat.get_mass() * 1.0 * s, REL_TOL);
}
