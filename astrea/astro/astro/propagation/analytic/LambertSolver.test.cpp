#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/propagation/analytic/LambertSolver.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

class LambertSolverTest : public testing::Test {
  public:
    LambertSolverTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    AstrodynamicsSystem sys;

    // Numbers from Vallado, 5th Ed., Ex. 7-5
    RadiusVector<ECI> r0{ 15945.34 * km, 0.0 * km, 0.0 * km }, rf{ 12214.83899 * km, 10249.46731 * km, 0.0 * km };
    VelocityVector<ECI> v0{ 2.058913 * km / s, 2.915964 * km / s }, vf{ -3.451565 * km / s, 0.910314 * km / s };
    Time dt = 76.0 * min;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(LambertSolverTest, SolveRV)
{
    const Cartesian result = LambertSolver::solve({ r0, v0 }, dt, sys.get_center()->get_mu());
    ASSERT_EQ_CART_VEC(result.get_position(), rf, REL_TOL);
    ASSERT_EQ_CART_VEC(result.get_velocity(), vf, REL_TOL);
}

TEST_F(LambertSolverTest, SolveRR)
{
    const auto [res0, resf] = LambertSolver::solve(r0, rf, dt, sys.get_center()->get_mu(), LambertSolver::OrbitDirection::PROGRADE);
    ASSERT_EQ_CART_VEC(res0, v0, REL_TOL);
    ASSERT_EQ_CART_VEC(resf, vf, REL_TOL);
}
