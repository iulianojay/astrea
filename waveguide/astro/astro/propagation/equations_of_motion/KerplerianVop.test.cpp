#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace waveguide;
using namespace astro;

class KeplerianVopTest : public testing::Test {
  public:
    KeplerianVopTest() :
        eom(sys)
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
    KeplerianVop eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(KeplerianVopTest, GetExpectedSet) { ASSERT_EQ(eom.get_expected_set(), ElementSet::KEPLERIAN); }

TEST_F(KeplerianVopTest, Derivative)
{
    Keplerian state0 = Keplerian::LEO();
    KeplerianPartial expected =
        KeplerianPartial(0.0 * km / s, 0.0 * 1 / s, 0.0 * rad / s, 0.0 * rad / s, 0.0 * rad / s, 0.0279019 * rad / s);

    OrbitalElementPartials dstate = eom(state0, sat);
    assert_nearly_equal(expected, dstate);
}
