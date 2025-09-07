#include <vector>

#include <gtest/gtest.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>
#include <tests/utilities/comparisons.hpp>

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

    const Unitless REL_TOL = 1.0e-6;
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
    ASSERT_EQ_QUANTITY(tle.get_mean_motion_1st_derivative(), MeanMotion1stDer(-0.00002182 * one / pow<2>(day)), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_mean_motion_2nd_derivative(), MeanMotion2ndDer(-0.0 * one / pow<3>(day)), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_ballistic_coefficient(), BallisticCoefficient(-0.000011606 * one / EarthRadii), REL_TOL);
    ASSERT_EQ(tle.get_ephemeris_type(), 0);
    ASSERT_EQ(tle.get_element_set_number(), 292);
    ASSERT_EQ(tle.get_check_sum1(), 7);

    ASSERT_EQ_QUANTITY(tle.get_semimajor(), Distance(22919.069 * km), REL_TOL); // derived
    ASSERT_EQ_QUANTITY(tle.get_eccentricity(), Unitless(0.0006703), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_inclination(), Angle(51.6416 * deg), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_right_ascension(), Angle(247.4627 * deg), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_argument_of_perigee(), Angle(130.5360 * deg), REL_TOL);
    ASSERT_EQ_QUANTITY(tle.get_true_anomaly(), Angle(324.9847 * deg), REL_TOL); // derived

    ASSERT_EQ_QUANTITY(tle.get_mean_motion(), MeanMotion(15.72125391 * one / day), REL_TOL);

    ASSERT_EQ(tle.get_rev_number(), 56353);
    ASSERT_EQ(tle.get_check_sum2(), 7);
}
