#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace waveguide;
using namespace astro;

class CowellsMethodTest : public testing::Test {
  public:
    CowellsMethodTest() :
        eom(sys, forces)
    {
    }

    void SetUp() override {}

    void assert_nearly_equal(const OrbitalElementPartials& elements, const OrbitalElementPartials& expectedElements)
    {
        ASSERT_TRUE(nearly_equal(elements, expectedElements)) << "Conversion caused issues greater than " << REL_TOL * 100 << "%\n"
                                                              << "Converted Set: " << elements << "\n"
                                                              << "Expected Set : " << expectedElements << "\n\n";
    }

    template <auto R, typename Rep>
    void assert_nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y) noexcept
    {
        ASSERT_TRUE(nearly_equal(x, y)) << "Conversion caused issues greater than " << REL_TOL * 100 << "%\n"
                                        << "First: " << x << "\n"
                                        << "Second: " << y << "\n\n";
    }

    const double REL_TOL = 1.0e-6;

    Vehicle sat;
    AstrodynamicsSystem sys;
    Date epoch;
    CowellsMethod eom;
    ForceModel forces;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CowellsMethodTest, GetExpectedSet) { ASSERT_EQ(eom.get_expected_set(), ElementSet::CARTESIAN); }

TEST_F(CowellsMethodTest, Derivative)
{
    Cartesian state0 = Cartesian::LEO(sys);
    CartesianPartial expected =
        CartesianPartial(state0.get_vx(), state0.get_vy(), state0.get_vz(), -0.622813 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s));

    OrbitalElementPartials dstate = eom(state0, sat);
    assert_nearly_equal(expected, dstate);
}

// Vallado, Ex. 8.5
TEST_F(CowellsMethodTest, DerivativeValladoEx85)
{
    Cartesian state0{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                      -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    CartesianPartial expected = CartesianPartial(
        state0.get_vx(), state0.get_vy(), state0.get_vz(), 0.00074873079 * km / (s * s), 0.00725534667 * km / (s * s), -0.00431725847 * km / (s * s)
    );

    OrbitalElementPartials dstate = eom(state0, sat);
    assert_nearly_equal(expected, dstate);
}