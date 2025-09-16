#include <array>

#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/orbital_data_formats/instances/TwoLineElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

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

    void SetUp() override
    {
        issRawTle = { "ISS (ZARYA)",
                      "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927",
                      "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537" };
        issTle    = TwoLineElements(issRawTle, sys);
    }

    const Unitless REL_TOL = 1.0e-6;
    AstrodynamicsSystem sys;

    std::array<std::string, 3> issRawTle;
    TwoLineElements issTle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(TwoLineElementsTest, DefaultConstructor) { ASSERT_NO_THROW(TwoLineElements()); }

TEST_F(TwoLineElementsTest, StringConstructorEmpty)
{
    ASSERT_ANY_THROW(TwoLineElements(std::array<std::string, 2>{}, sys));
}

TEST_F(TwoLineElementsTest, StringConstructorLinesWrongSize)
{
    std::array<std::string, 2> longTle = {
        "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927 blahblahblah",
        "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537 blahblahblah"
    };
    ASSERT_ANY_THROW(TwoLineElements(longTle, sys));

    std::array<std::string, 2> shortTle = { "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  ",
                                            "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.7212539156" };
    ASSERT_ANY_THROW(TwoLineElements(shortTle, sys));
}

TEST_F(TwoLineElementsTest, StringConstructor)
{
    std::array<std::string, 2> rawTle = { issRawTle[1], issRawTle[2] };

    TwoLineElements tle(rawTle, sys);

    ASSERT_EQ(tle.get_raw_tle()[0], rawTle[0]);
    ASSERT_EQ(tle.get_raw_tle()[1], rawTle[1]);

    ASSERT_EQ(tle.get_1st_line(), rawTle[0]);
    ASSERT_EQ(tle.get_2nd_line(), rawTle[1]);

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

TEST_F(TwoLineElementsTest, StringConstructor3Line)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle(rawTle, sys);

    ASSERT_EQ(tle.get_name(), rawTle[0]);

    ASSERT_EQ(tle.get_raw_tle()[0], rawTle[1]);
    ASSERT_EQ(tle.get_raw_tle()[1], rawTle[2]);

    ASSERT_EQ(tle.get_1st_line(), rawTle[1]);
    ASSERT_EQ(tle.get_2nd_line(), rawTle[2]);

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

TEST_F(TwoLineElementsTest, CopyConstructor)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle1(rawTle, sys);
    TwoLineElements tle2(tle1);
    ASSERT_EQ(tle1, tle2);
}

TEST_F(TwoLineElementsTest, MoveConstructor)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle1(rawTle, sys);
    TwoLineElements tle2(std::move(tle1));

    ASSERT_EQ(tle2, issTle);
}

TEST_F(TwoLineElementsTest, CopyAssignment)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle1(rawTle, sys);
    TwoLineElements tle2;
    tle2 = tle1;
    ASSERT_EQ(tle1, tle2);
}

TEST_F(TwoLineElementsTest, MoveAssignment)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle1(rawTle, sys);
    TwoLineElements tle2;
    tle2 = std::move(tle1);
    ASSERT_EQ(tle2, issTle);
}

TEST_F(TwoLineElementsTest, EqualityOperator)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle1(rawTle, sys);
    TwoLineElements tle2(rawTle, sys);
    ASSERT_TRUE(tle1 == tle2);
    ASSERT_FALSE(tle1 != tle2);

    std::array<std::string, 2> rawTleDiff = { "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927",
                                              "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563538" }; // Changed last digit
    TwoLineElements tle3(rawTleDiff, sys);
    ASSERT_FALSE(tle1 == tle3);
    ASSERT_TRUE(tle1 != tle3);
}

TEST_F(TwoLineElementsTest, Stream)
{
    const auto rawTle = issRawTle;
    TwoLineElements tle(rawTle, sys);
    std::stringstream ss;
    ss << tle;
    std::stringstream expected;
    expected << "[" << issRawTle[1] << "\n " << issRawTle[2] << "] (Tle)";
    ASSERT_EQ(ss.str(), expected.str());
}
