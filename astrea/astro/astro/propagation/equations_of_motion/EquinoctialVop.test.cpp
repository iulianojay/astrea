#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <tests/utilities/comparisons.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class EquinoctialTest : public testing::Test {
  public:
    EquinoctialTest() :
        eom(sys, forces)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Vehicle sat;
    AstrodynamicsSystem sys;
    Date epoch;
    EquinoctialVop eom;
    ForceModel forces;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(EquinoctialTest, GetExpectedSet)
{
    ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Equinoctial>());
}

TEST_F(EquinoctialTest, Derivative)
{
    Equinoctial state0 = Equinoctial::LEO(sys.get_mu());
    EquinoctialPartial expected =
        EquinoctialPartial(0.0 * km / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0010780076129942077 * rad / s);

    OrbitalElementPartials dstate = eom(state0, sat);
    ASSERT_EQ_ORB_PART(expected, dstate, REL_TOL);
}