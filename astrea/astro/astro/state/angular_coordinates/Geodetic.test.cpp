#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/angular_coordinates/Geodetic.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class GeodeticTest : public testing::Test {
  public:
    GeodeticTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    AstrodynamicsSystem sys;

    Angle latitude    = 0.0 * astrea::detail::angle_unit;
    Angle longitude   = 0.0 * astrea::detail::angle_unit;
    Distance altitude = 10000.0 * km;
    Geodetic state{ latitude, longitude, altitude };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GeodeticTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << latitude << ", " << longitude << ", " << altitude << "] (Geodetic)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(GeodeticTest, DefaultConstructor) { ASSERT_NO_THROW(Geodetic()); }

TEST_F(GeodeticTest, UnitlessConstructor)
{
    Geodetic zeroState;
    ASSERT_EQ_QUANTITY(zeroState.get_altitude(), Distance(0.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_latitude(), Angle(0.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_longitude(), Angle(0.0 * rad), REL_TOL);

    Geodetic scaledState(2.0 * one);
    ASSERT_EQ_QUANTITY(scaledState.get_altitude(), Distance(2.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_latitude(), Angle(2.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_longitude(), Angle(2.0 * rad), REL_TOL);
}

TEST_F(GeodeticTest, ParameterizedConstructor) { ASSERT_NO_THROW(Geodetic(latitude, longitude, altitude)); }

TEST_F(GeodeticTest, EciVectorConstructor)
{
    RadiusVector<ECI> rEci{ 7000.0 * km, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Geodetic(rEci, epoch, sys.get_center().get()));
}

TEST_F(GeodeticTest, EcefVectorConstructor)
{
    RadiusVector<ECEF> rEcef{ 7000.0 * km, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Geodetic(rEcef, sys.get_center().get()));
}

TEST_F(GeodeticTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Geodetic(kep, sys, epoch));
}

TEST_F(GeodeticTest, CopyConstructor) { ASSERT_NO_THROW(Geodetic newGeo(state)); }

TEST_F(GeodeticTest, MoveConstructor) { ASSERT_NO_THROW(Geodetic newGeo(std::move(state))); }

TEST_F(GeodeticTest, CopyAssignment) { ASSERT_NO_THROW(Geodetic newGeo = state); }

TEST_F(GeodeticTest, MoveAssignment) { ASSERT_NO_THROW(Geodetic newGeo = std::move(state)); }

TEST_F(GeodeticTest, EqualityOperator)
{
    Geodetic sameState{ latitude, longitude, altitude };
    Geodetic diffState{ latitude, longitude, altitude + 1.0 * km };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(GeodeticTest, AdditionOperator)
{
    Geodetic other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    Geodetic result = state + other;
    ASSERT_EQ(result.get_altitude(), altitude + 1.0 * km);
    ASSERT_EQ(result.get_latitude(), latitude + 1.0 * rad);
    ASSERT_EQ(result.get_longitude(), longitude + 1.0 * rad);
}

TEST_F(GeodeticTest, AdditionAssignmentOperator)
{
    Geodetic other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    state += other;
    ASSERT_EQ(state.get_altitude(), altitude + 1.0 * km);
    ASSERT_EQ(state.get_latitude(), latitude + 1.0 * rad);
    ASSERT_EQ(state.get_longitude(), longitude + 1.0 * rad);
}

TEST_F(GeodeticTest, SubtractionOperator)
{
    Geodetic other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    Geodetic result = state - other;
    ASSERT_EQ(result.get_altitude(), altitude - 1.0 * km);
    ASSERT_EQ(result.get_latitude(), latitude - 1.0 * rad);
    ASSERT_EQ(result.get_longitude(), longitude - 1.0 * rad);
}

TEST_F(GeodeticTest, SubtractionAssignmentOperator)
{
    Geodetic other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    state -= other;
    ASSERT_EQ(state.get_altitude(), altitude - 1.0 * km);
    ASSERT_EQ(state.get_latitude(), latitude - 1.0 * rad);
    ASSERT_EQ(state.get_longitude(), longitude - 1.0 * rad);
}

TEST_F(GeodeticTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Geodetic result     = state * multiplier;
    ASSERT_EQ(result.get_altitude(), altitude * multiplier);
    ASSERT_EQ(result.get_latitude(), latitude * multiplier);
    ASSERT_EQ(result.get_longitude(), longitude * multiplier);
}

TEST_F(GeodeticTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_EQ(state.get_altitude(), altitude * multiplier);
    ASSERT_EQ(state.get_latitude(), latitude * multiplier);
    ASSERT_EQ(state.get_longitude(), longitude * multiplier);
}

TEST_F(GeodeticTest, DivisionOperator)
{
    Unitless divisor = 2.0 * one;
    Geodetic result  = state / divisor;
    ASSERT_EQ(result.get_altitude(), altitude / divisor);
    ASSERT_EQ(result.get_latitude(), latitude / divisor);
    ASSERT_EQ(result.get_longitude(), longitude / divisor);
}

TEST_F(GeodeticTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_EQ(state.get_altitude(), altitude / divisor);
    ASSERT_EQ(state.get_latitude(), latitude / divisor);
    ASSERT_EQ(state.get_longitude(), longitude / divisor);
}

TEST_F(GeodeticTest, DivisionByGeodeticOperator)
{
    Geodetic other{ 2.0 * rad, 2.0 * rad, 2.0 * km };
    std::vector<Unitless> result = state / other;
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], latitude / other.get_latitude());
    ASSERT_EQ(result[1], longitude / other.get_longitude());
    ASSERT_EQ(result[2], altitude / other.get_altitude());
}

TEST_F(GeodeticTest, Interpolate)
{
    Geodetic other{ 1.5 * rad, 1.5 * rad, 20000.0 * km };
    Time thisTime   = seconds(0);
    Time otherTime  = seconds(10);
    Time targetTime = seconds(5);
    Geodetic result = state.interpolate(thisTime, otherTime, other, targetTime);
    ASSERT_EQ_QUANTITY(result.get_altitude(), Distance(15000.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_latitude(), Angle(0.75 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_longitude(), Angle(0.75 * rad), REL_TOL);
}

TEST_F(GeodeticTest, Getters)
{
    ASSERT_EQ_QUANTITY(state.get_altitude(), altitude, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_latitude(), latitude, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_longitude(), longitude, REL_TOL);
}
