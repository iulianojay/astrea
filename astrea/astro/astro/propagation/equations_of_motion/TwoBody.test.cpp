#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <tests/utilities/comparisons.hpp>

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class TwoBodyTest : public testing::Test {
  public:
    TwoBodyTest() :
        eom(sys)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Vehicle sat;
    AstrodynamicsSystem sys;
    Date epoch;
    TwoBody eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(TwoBodyTest, GetExpectedSet) { ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Cartesian>()); }

TEST_F(TwoBodyTest, Derivative)
{
    Cartesian state0          = Cartesian::LEO(sys);
    CartesianPartial expected = CartesianPartial(
        state0.get_vx(), state0.get_vy(), state0.get_vz(), -0.0081347028957142863 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s)
    );

    OrbitalElementPartials dstate = eom(state0, sat);
    ASSERT_EQ_ORB_PART(expected, dstate, REL_TOL);
}

// Vallado, Ex. 8.5
TEST_F(TwoBodyTest, DerivativeValladoEx85)
{
    Cartesian state0{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                      -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    CartesianPartial expected = CartesianPartial(
        state0.get_vx(), state0.get_vy(), state0.get_vz(), 0.00074873079 * km / (s * s), 0.00725534667 * km / (s * s), -0.00431725847 * km / (s * s)
    );

    OrbitalElementPartials dstate = eom(state0, sat);
    ASSERT_EQ_ORB_PART(expected, dstate, REL_TOL);
}
