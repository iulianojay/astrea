#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class LambertSolverTest : public testing::Test {
  public:
    LambertSolverTest() {}

    void SetUp() override {}

    template <auto R, typename Rep>
    const bool nearly_equal(const mp_units::quantity<R, Rep>& first, const mp_units::quantity<R, Rep>& second) const
    {
        const Rep a       = first.numerical_value_ref_in(first.unit);
        const Rep b       = first.numerical_value_ref_in(second.unit);
        const Rep REL_TOL = 1.0e-4;
        if (a != 0.0 && abs((a - b) / a) > REL_TOL) { return false; }
        else if (b != 0.0 && abs((a - b) / b) > REL_TOL) {
            return false;
        }
        return true;
    }

    template <typename Value_T, typename Frame_T>
    void assert_nearly_equal(const CartesianVector<Value_T, Frame_T>& vec, const CartesianVector<Value_T, Frame_T>& expected)
    {
        for (std::size_t ii = 0; ii < 3; ++ii) {
            ASSERT_TRUE(nearly_equal(vec[ii], expected[ii]))
                << "Lambert Solution caused issues greater than " << REL_TOL * 100 << "%\n"
                << "Vector: " << vec << "\n"
                << "Expected: " << expected << "\n\n";
        }
    }

    template <auto R, typename Rep>
    void assert_nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y) noexcept
    {
        ASSERT_TRUE(nearly_equal(x, y)) << "Lambert Solution issues greater than " << REL_TOL * 100 << "%\n"
                                        << "First: " << x << "\n"
                                        << "Second: " << y << "\n\n";
    }

    const double REL_TOL = 1.0e-6;

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
    assert_nearly_equal(result.get_position(), rf);
    assert_nearly_equal(result.get_velocity(), vf);
}

TEST_F(LambertSolverTest, SolveRR)
{
    const auto [res0, resf] = LambertSolver::solve(r0, rf, dt, sys.get_center()->get_mu(), LambertSolver::OrbitDirection::PROGRADE);
    assert_nearly_equal(res0, v0);
    assert_nearly_equal(resf, vf);
}
