#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/angular_coordinates/Cylindrical.hpp>
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

class CylindricalTest : public testing::Test {
  public:
    CylindricalTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    AstrodynamicsSystem sys;

    Distance range     = 10000.0 * km;
    Angle azimuth      = 0.0 * rad;
    Distance elevation = 0.0 * km;
    Cylindrical state{ range, azimuth, elevation };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CylindricalTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << range << ", " << azimuth << ", " << elevation << "] (Cylindrical)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(CylindricalTest, DefaultConstructor) { ASSERT_NO_THROW(Cylindrical()); }

TEST_F(CylindricalTest, UnitlessConstructor)
{
    Cylindrical zeroState;
    ASSERT_EQ_QUANTITY(zeroState.get_range(), Distance(0.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_azimuth(), Angle(0.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_elevation(), Distance(0.0 * km), REL_TOL);

    Cylindrical scaledState(2.0 * one);
    ASSERT_EQ_QUANTITY(scaledState.get_range(), Distance(2.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_azimuth(), Angle(2.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_elevation(), Distance(2.0 * km), REL_TOL);
}

TEST_F(CylindricalTest, ParameterizedConstructor) { ASSERT_NO_THROW(Cylindrical(range, azimuth, elevation)); }

TEST_F(CylindricalTest, EciVectorConstructor)
{
    RadiusVector<ECI> rEci{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Cylindrical(rEci, epoch, sys.get_center().get()));
}

TEST_F(CylindricalTest, EcefVectorConstructor)
{
    RadiusVector<ECEF> rEcef{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Cylindrical(rEcef, sys.get_center().get()));
}

TEST_F(CylindricalTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Cylindrical(kep, sys, epoch));
}

TEST_F(CylindricalTest, CopyConstructor) { ASSERT_NO_THROW(Cylindrical newCyl(state)); }

TEST_F(CylindricalTest, MoveConstructor) { ASSERT_NO_THROW(Cylindrical newCyl(std::move(state))); }

TEST_F(CylindricalTest, CopyAssignment) { ASSERT_NO_THROW(Cylindrical newCyl = state); }

TEST_F(CylindricalTest, MoveAssignment) { ASSERT_NO_THROW(Cylindrical newCyl = std::move(state)); }

TEST_F(CylindricalTest, EqualityOperator)
{
    Cylindrical sameState{ range, azimuth, elevation };
    Cylindrical diffState{ range + 1.0 * km, azimuth, elevation };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(CylindricalTest, AdditionOperator)
{
    Cylindrical other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    Cylindrical result = state + other;
    ASSERT_EQ(result.get_range(), range + 1.0 * km);
    ASSERT_EQ(result.get_azimuth(), azimuth + 1.0 * rad);
    ASSERT_EQ(result.get_elevation(), elevation + 1.0 * km);
}

TEST_F(CylindricalTest, AdditionAssignmentOperator)
{
    Cylindrical other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    state += other;
    ASSERT_EQ(state.get_range(), range + 1.0 * km);
    ASSERT_EQ(state.get_azimuth(), azimuth + 1.0 * rad);
    ASSERT_EQ(state.get_elevation(), elevation + 1.0 * km);
}

TEST_F(CylindricalTest, SubtractionOperator)
{
    Cylindrical other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    Cylindrical result = state - other;
    ASSERT_EQ(result.get_range(), range - 1.0 * km);
    ASSERT_EQ(result.get_azimuth(), azimuth - 1.0 * rad);
    ASSERT_EQ(result.get_elevation(), elevation - 1.0 * km);
}

TEST_F(CylindricalTest, SubtractionAssignmentOperator)
{
    Cylindrical other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    state -= other;
    ASSERT_EQ(state.get_range(), range - 1.0 * km);
    ASSERT_EQ(state.get_azimuth(), azimuth - 1.0 * rad);
    ASSERT_EQ(state.get_elevation(), elevation - 1.0 * km);
}

TEST_F(CylindricalTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Cylindrical result  = state * multiplier;
    ASSERT_EQ(result.get_range(), range * multiplier);
    ASSERT_EQ(result.get_azimuth(), azimuth * multiplier);
    ASSERT_EQ(result.get_elevation(), elevation * multiplier);
}

TEST_F(CylindricalTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_EQ(state.get_range(), range * multiplier);
    ASSERT_EQ(state.get_azimuth(), azimuth * multiplier);
    ASSERT_EQ(state.get_elevation(), elevation * multiplier);
}

TEST_F(CylindricalTest, DivisionOperator)
{
    Unitless divisor   = 2.0 * one;
    Cylindrical result = state / divisor;
    ASSERT_EQ(result.get_range(), range / divisor);
    ASSERT_EQ(result.get_azimuth(), azimuth / divisor);
    ASSERT_EQ(result.get_elevation(), elevation / divisor);
}

TEST_F(CylindricalTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_EQ(state.get_range(), range / divisor);
    ASSERT_EQ(state.get_azimuth(), azimuth / divisor);
    ASSERT_EQ(state.get_elevation(), elevation / divisor);
}

TEST_F(CylindricalTest, DivisionByCylindricalOperator)
{
    Cylindrical other{ 2.0 * km, 2.0 * rad, 2.0 * km };
    std::vector<Unitless> result = state / other;
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], range / other.get_range());
    ASSERT_EQ(result[1], azimuth / other.get_azimuth());
    ASSERT_EQ(result[2], elevation / other.get_elevation());
}

TEST_F(CylindricalTest, Interpolate)
{
    Cylindrical other{ 20000.0 * km, 1.5 * rad, 20.0 * km };
    Time thisTime      = seconds(0);
    Time otherTime     = seconds(10);
    Time targetTime    = seconds(5);
    Cylindrical result = state.interpolate(thisTime, otherTime, other, targetTime);
    ASSERT_EQ_QUANTITY(result.get_range(), Distance(15000.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_azimuth(), Angle(0.75 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_elevation(), Distance(10.0 * km), REL_TOL);
}

TEST_F(CylindricalTest, Getters)
{
    ASSERT_EQ_QUANTITY(state.get_range(), range, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_azimuth(), azimuth, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_elevation(), elevation, REL_TOL);
}
