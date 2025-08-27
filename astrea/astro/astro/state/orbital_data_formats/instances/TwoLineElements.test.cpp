#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

class TwoLineElementsTest : public testing::Test {
  public:
    TwoLineElementsTest() = default;

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

    template <auto R, typename Rep>
    void assert_nearly_equal(const mp_units::quantity<R, Rep>& value, const mp_units::quantity<R, Rep>& expected)
    {
        ASSERT_TRUE(nearly_equal(value, expected)) << "Issues greater than " << REL_TOL * 100 << "%\n"
                                                   << "Value: " << value << "\n"
                                                   << "Expected: " << expected << "\n\n";
    }

    const double REL_TOL = 1.0e-6;
    AstrodynamicsSystem _sys;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(TwoLineElementsTest, DefaultConstructor) { ASSERT_NO_THROW(TwoLineElements()); }

TEST_F(TwoLineElementsTest, StringConstructorEmpty)
{
    ASSERT_ANY_THROW(TwoLineElements(std::array<std::string, 2>{}, _sys));
}

TEST_F(TwoLineElementsTest, StringConstructor)
{
    std::array<std::string, 2> rawTle = { "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927",
                                          "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537" };
    TwoLineElements tle(rawTle, _sys);

    ASSERT_EQ(tle.get_raw_tle()[0], rawTle[0]);
    ASSERT_EQ(tle.get_raw_tle()[1], rawTle[1]);

    ASSERT_EQ(tle.get_catalogue_number(), 25544);
    ASSERT_EQ(tle.get_classification(), "U");
    ASSERT_EQ(tle.get_launch_year(), "98");
    ASSERT_EQ(tle.get_launch_number(), "067");
    ASSERT_EQ(tle.get_launch_piece(), "A");
    ASSERT_EQ(tle.get_epoch(), Date("2008-09-20 12:25:40"));
    assert_nearly_equal(tle.get_mean_motion_1st_derivative(), MeanMotion1stDer(-0.00002182 * one / pow<2>(day)));
    assert_nearly_equal(tle.get_mean_motion_2nd_derivative(), MeanMotion2ndDer(-0.0 * one / pow<3>(day)));
    assert_nearly_equal(tle.get_ballistic_coefficient(), BallisticCoefficient(-0.000011606 * one / EarthRadii));
    ASSERT_EQ(tle.get_ephemeris_type(), 0);
    ASSERT_EQ(tle.get_element_set_number(), 292);
    ASSERT_EQ(tle.get_check_sum1(), 7);

    assert_nearly_equal(tle.get_semimajor(), Distance(22919.1 * km));
    assert_nearly_equal(tle.get_eccentricity(), Unitless(0.0006703));
    assert_nearly_equal(tle.get_inclination(), Angle(51.6416 * deg));
    assert_nearly_equal(tle.get_right_ascension(), Angle(247.4627 * deg));
    assert_nearly_equal(tle.get_argument_of_perigee(), Angle(130.5360 * deg));
    assert_nearly_equal(tle.get_true_anomaly(), Angle(325.0288 * deg));

    assert_nearly_equal(tle.get_mean_motion(), MeanMotion(15.72125391 * one / day));

    ASSERT_EQ(tle.get_rev_number(), 56353);
    ASSERT_EQ(tle.get_check_sum2(), 7);
}
