#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <tests/utilities/comparisons.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class J2MeanTest : public testing::Test {
  public:
    J2MeanTest() :
        eom(sys)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Vehicle sat;
    AstrodynamicsSystem sys;
    Date epoch;
    J2MeanVop eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(J2MeanTest, GetExpectedSet) { ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Keplerian>()); }

TEST_F(J2MeanTest, Derivative)
{
    Keplerian state0 = Keplerian::LEO();
    KeplerianPartial expected =
        KeplerianPartial(0.0 * km / s, 0.0 * 1 / s, 0.0 * rad / s, 0.0 * rad / s, 0.0 * rad / s, 0.0010780076129942077 * rad / s);

    OrbitalElementPartials dstate = eom(state0, sat);
    ASSERT_EQ_ORB_PART(expected, dstate, REL_TOL);
}
