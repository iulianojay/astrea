#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class SphericalTest : public testing::Test {
  public:
    SphericalTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    AstrodynamicsSystem sys;

    Angle azimuth     = 0.0 * astrea::detail::angle_unit;
    Angle inclination = 0.0 * astrea::detail::angle_unit;
    Distance range    = 10000.0 * km;
    Spherical state{ range, inclination, azimuth };
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SphericalTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << range << ", " << inclination << ", " << azimuth << "] (Spherical)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(SphericalTest, DefaultConstructor) { ASSERT_NO_THROW(Spherical()); }

TEST_F(SphericalTest, UnitlessConstructor)
{
    Spherical zeroState;
    ASSERT_EQ_QUANTITY(zeroState.get_range(), Distance(0.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_inclination(), Angle(0.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(zeroState.get_azimuth(), Angle(0.0 * rad), REL_TOL);

    Spherical scaledState(2.0 * one);
    ASSERT_EQ_QUANTITY(scaledState.get_range(), Distance(2.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_inclination(), Angle(2.0 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_azimuth(), Angle(2.0 * rad), REL_TOL);
}

TEST_F(SphericalTest, ParameterizedConstructor) { ASSERT_NO_THROW(Spherical(range, inclination, azimuth)); }

TEST_F(SphericalTest, EciVectorConstructor)
{
    RadiusVector<ECI> rEci{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Spherical(rEci, epoch, sys.get_center().get()));
}

TEST_F(SphericalTest, EcefVectorConstructor)
{
    RadiusVector<ECEF> rEcef{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Spherical(rEcef, sys.get_center().get()));
}

TEST_F(SphericalTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Spherical(kep, sys, epoch));
}

TEST_F(SphericalTest, CopyConstructor) { ASSERT_NO_THROW(Spherical newSph(state)); }

TEST_F(SphericalTest, MoveConstructor) { ASSERT_NO_THROW(Spherical newSph(std::move(state))); }

TEST_F(SphericalTest, CopyAssignment) { ASSERT_NO_THROW(Spherical newSph = state); }

TEST_F(SphericalTest, MoveAssignment) { ASSERT_NO_THROW(Spherical newSph = std::move(state)); }

TEST_F(SphericalTest, EqualityOperator)
{
    Spherical sameState{ range, inclination, azimuth };
    Spherical diffState{ range + 1.0 * km, inclination, azimuth };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(SphericalTest, AdditionOperator)
{
    Spherical other{ 1.0 * km, 1.0 * rad, 1.0 * rad };
    Spherical result = state + other;
    ASSERT_EQ(result.get_range(), range + 1.0 * km);
    ASSERT_EQ(result.get_inclination(), inclination + 1.0 * rad);
    ASSERT_EQ(result.get_azimuth(), azimuth + 1.0 * rad);
}

TEST_F(SphericalTest, AdditionAssignmentOperator)
{
    Spherical other{ 1.0 * km, 1.0 * rad, 1.0 * rad };
    state += other;
    ASSERT_EQ(state.get_range(), range + 1.0 * km);
    ASSERT_EQ(state.get_inclination(), inclination + 1.0 * rad);
    ASSERT_EQ(state.get_azimuth(), azimuth + 1.0 * rad);
}

TEST_F(SphericalTest, SubtractionOperator)
{
    Spherical other{ 1.0 * km, 1.0 * rad, 1.0 * rad };
    Spherical result = state - other;
    ASSERT_EQ(result.get_range(), range - 1.0 * km);
    ASSERT_EQ(result.get_inclination(), inclination - 1.0 * rad);
    ASSERT_EQ(result.get_azimuth(), azimuth - 1.0 * rad);
}

TEST_F(SphericalTest, SubtractionAssignmentOperator)
{
    Spherical other{ 1.0 * km, 1.0 * rad, 1.0 * rad };
    state -= other;
    ASSERT_EQ(state.get_range(), range - 1.0 * km);
    ASSERT_EQ(state.get_inclination(), inclination - 1.0 * rad);
    ASSERT_EQ(state.get_azimuth(), azimuth - 1.0 * rad);
}

TEST_F(SphericalTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Spherical result    = state * multiplier;
    ASSERT_EQ(result.get_range(), range * multiplier);
    ASSERT_EQ(result.get_inclination(), inclination * multiplier);
    ASSERT_EQ(result.get_azimuth(), azimuth * multiplier);
}

TEST_F(SphericalTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_EQ(state.get_range(), range * multiplier);
    ASSERT_EQ(state.get_inclination(), inclination * multiplier);
    ASSERT_EQ(state.get_azimuth(), azimuth * multiplier);
}

TEST_F(SphericalTest, DivisionOperator)
{
    Unitless divisor = 2.0 * one;
    Spherical result = state / divisor;
    ASSERT_EQ(result.get_range(), range / divisor);
    ASSERT_EQ(result.get_inclination(), inclination / divisor);
    ASSERT_EQ(result.get_azimuth(), azimuth / divisor);
}

TEST_F(SphericalTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_EQ(state.get_range(), range / divisor);
    ASSERT_EQ(state.get_inclination(), inclination / divisor);
    ASSERT_EQ(state.get_azimuth(), azimuth / divisor);
}

TEST_F(SphericalTest, DivisionBySphericalOperator)
{
    Spherical other{ 2.0 * km, 2.0 * rad, 2.0 * rad };
    std::vector<Unitless> result = state / other;
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], range / other.get_range());
    ASSERT_EQ(result[1], inclination / other.get_inclination());
    ASSERT_EQ(result[2], azimuth / other.get_azimuth());
}

TEST_F(SphericalTest, GetPositionEcef)
{
    RadiusVector<ECEF> rEcef               = state.get_position(sys.get_center().get());
    auto [convRange, convInc, convAzimuth] = convert_earth_fixed_to_spherical(rEcef);
    ASSERT_EQ_QUANTITY(convRange, range, REL_TOL);
    ASSERT_EQ_QUANTITY(convInc, inclination, REL_TOL);
    ASSERT_EQ_QUANTITY(convAzimuth, azimuth, REL_TOL);
}

TEST_F(SphericalTest, GetPositionEci)
{
    RadiusVector<ECI> rEci                 = state.get_position(epoch, sys.get_center().get());
    auto [convRange, convInc, convAzimuth] = convert_earth_fixed_to_spherical(rEci.in_frame<ECEF>(epoch));
    ASSERT_EQ_QUANTITY(convRange, range, REL_TOL);
    ASSERT_EQ_QUANTITY(convInc, inclination, REL_TOL);
    ASSERT_EQ_QUANTITY(convAzimuth, azimuth, REL_TOL);
}

TEST_F(SphericalTest, Interpolate)
{
    Spherical other{ 20000.0 * km, 1.5 * rad, 1.5 * rad };
    Time thisTime    = seconds(0);
    Time otherTime   = seconds(10);
    Time targetTime  = seconds(5);
    Spherical result = state.interpolate(thisTime, otherTime, other, targetTime);
    ASSERT_EQ_QUANTITY(result.get_range(), Distance(15000.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_inclination(), Angle(0.75 * rad), REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_azimuth(), Angle(0.75 * rad), REL_TOL);
}

TEST_F(SphericalTest, Getters)
{
    ASSERT_EQ_QUANTITY(state.get_range(), range, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_inclination(), inclination, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_azimuth(), azimuth, REL_TOL);
}

TEST_F(SphericalTest, ConvertEarthFixedToSpherical)
{
    RadiusVector<ECEF> rEcef{ range, 0.0 * km, 0.0 * km };
    auto [convRange, convInc, convAzimuth] = convert_earth_fixed_to_spherical(rEcef);
    ASSERT_EQ_QUANTITY(convRange, range, REL_TOL);
    ASSERT_EQ_QUANTITY(convInc, inclination, REL_TOL);
    ASSERT_EQ_QUANTITY(convAzimuth, azimuth, REL_TOL);
}

TEST_F(SphericalTest, ConvertSphericalToEarthFixed)
{
    RadiusVector<ECEF> rEcef               = convert_spherical_to_earth_fixed(range, inclination, azimuth);
    auto [convRange, convInc, convAzimuth] = convert_earth_fixed_to_spherical(rEcef);
    ASSERT_EQ_QUANTITY(convRange, range, REL_TOL);
    ASSERT_EQ_QUANTITY(convInc, inclination, REL_TOL);
    ASSERT_EQ_QUANTITY(convAzimuth, azimuth, REL_TOL);
}
