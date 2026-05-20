/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>
#include <mp-units/systems/angular/math.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/angular_elements/instances/Cylindrical.hpp>
#include <astro/systems/planets.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace astro::planets;
using namespace mp_units;

using mp_units::angular::cos;
using mp_units::angular::sin;
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

    Distance range     = 10000.0 * km;
    Angle azimuth      = 0.0 * rad;
    Distance elevation = 0.0 * km;
    Cylindrical<Earth> state{ range, azimuth, elevation };
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

TEST_F(CylindricalTest, DefaultConstructor) { ASSERT_NO_THROW(Cylindrical<Earth>()); }

TEST_F(CylindricalTest, UnitlessConstructor)
{
    Cylindrical<Earth> zeroState;
    ASSERT_TRUE(math::nearly_equal(zeroState.get_range(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(zeroState.get_azimuth(), Angle(0.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(zeroState.get_elevation(), Distance(0.0 * km), REL_TOL));

    Cylindrical<Earth> scaledState(2.0 * one);
    ASSERT_TRUE(math::nearly_equal(scaledState.get_range(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_azimuth(), Angle(2.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_elevation(), Distance(2.0 * km), REL_TOL));
}

TEST_F(CylindricalTest, ParameterizedConstructor) { ASSERT_NO_THROW(Cylindrical<Earth>(range, azimuth, elevation)); }

TEST_F(CylindricalTest, EciVectorConstructor)
{
    RadiusVector<frames::earth::icrf> rEci{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Cylindrical<Earth>(rEci, epoch));
}

TEST_F(CylindricalTest, EcefVectorConstructor)
{
    RadiusVector<frames::earth::earth_fixed> rEcef{ range, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Cylindrical<Earth>(rEcef));
}

TEST_F(CylindricalTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Cylindrical<Earth>(kep, epoch));
}

TEST_F(CylindricalTest, CopyConstructor) { ASSERT_NO_THROW(Cylindrical<Earth> newCyl(state)); }

TEST_F(CylindricalTest, MoveConstructor) { ASSERT_NO_THROW(Cylindrical<Earth> newCyl(std::move(state))); }

TEST_F(CylindricalTest, CopyAssignment) { ASSERT_NO_THROW(Cylindrical<Earth> newCyl = state); }

TEST_F(CylindricalTest, MoveAssignment) { ASSERT_NO_THROW(Cylindrical<Earth> newCyl = std::move(state)); }

TEST_F(CylindricalTest, EqualityOperator)
{
    Cylindrical<Earth> sameState{ range, azimuth, elevation };
    Cylindrical<Earth> diffState{ range + 1.0 * km, azimuth, elevation };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(CylindricalTest, AdditionOperator)
{
    Cylindrical<Earth> other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    Cylindrical<Earth> result = state + other;
    ASSERT_EQ(result.get_range(), range + 1.0 * km);
    ASSERT_EQ(result.get_azimuth(), azimuth + 1.0 * rad);
    ASSERT_EQ(result.get_elevation(), elevation + 1.0 * km);
}

TEST_F(CylindricalTest, AdditionAssignmentOperator)
{
    Cylindrical<Earth> other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    state += other;
    ASSERT_EQ(state.get_range(), range + 1.0 * km);
    ASSERT_EQ(state.get_azimuth(), azimuth + 1.0 * rad);
    ASSERT_EQ(state.get_elevation(), elevation + 1.0 * km);
}

TEST_F(CylindricalTest, SubtractionOperator)
{
    Cylindrical<Earth> other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    Cylindrical<Earth> result = state - other;
    ASSERT_EQ(result.get_range(), range - 1.0 * km);
    ASSERT_EQ(result.get_azimuth(), azimuth - 1.0 * rad);
    ASSERT_EQ(result.get_elevation(), elevation - 1.0 * km);
}

TEST_F(CylindricalTest, SubtractionAssignmentOperator)
{
    Cylindrical<Earth> other{ 1.0 * km, 1.0 * rad, 1.0 * km };
    state -= other;
    ASSERT_EQ(state.get_range(), range - 1.0 * km);
    ASSERT_EQ(state.get_azimuth(), azimuth - 1.0 * rad);
    ASSERT_EQ(state.get_elevation(), elevation - 1.0 * km);
}

TEST_F(CylindricalTest, MultiplicationOperator)
{
    Unitless multiplier       = 2.0 * one;
    Cylindrical<Earth> result = state * multiplier;
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
    Unitless divisor          = 2.0 * one;
    Cylindrical<Earth> result = state / divisor;
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
    Cylindrical<Earth> other{ 2.0 * km, 2.0 * rad, 2.0 * km };
    std::vector<Unitless> result = state / other;
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], range / other.get_range());
    ASSERT_EQ(result[1], azimuth / other.get_azimuth());
    ASSERT_EQ(result[2], elevation / other.get_elevation());
}

TEST_F(CylindricalTest, Interpolate)
{
    Cylindrical<Earth> other{ 20000.0 * km, 1.5 * rad, 20.0 * km };
    Time thisTime             = seconds(0);
    Time otherTime            = seconds(10);
    Time targetTime           = seconds(5);
    Cylindrical<Earth> result = state.interpolate(thisTime, otherTime, other, targetTime);
    ASSERT_TRUE(math::nearly_equal(result.get_range(), Distance(15000.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_azimuth(), Angle(0.75 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_elevation(), Distance(10.0 * km), REL_TOL));
}

TEST_F(CylindricalTest, Getters)
{
    ASSERT_TRUE(math::nearly_equal(state.get_range(), range, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_azimuth(), azimuth, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_elevation(), elevation, REL_TOL));
}

TEST_F(CylindricalTest, GetPositionEcef)
{
    // Test case 1: Zero azimuth (on x-axis)
    Cylindrical<Earth> cyl1{ 10000.0 * km, 0.0 * rad, 0.0 * km };
    auto pos1 = cyl1.get_position();
    ASSERT_TRUE(math::nearly_equal(pos1.get_x(), Distance(10000.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos1.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos1.get_z(), Distance(0.0 * km), REL_TOL));

    // Test case 2: 90 degree azimuth (on y-axis)
    Cylindrical<Earth> cyl2{ 5000.0 * km, 90.0 * deg, 0.0 * km };
    auto pos2 = cyl2.get_position();
    ASSERT_TRUE(math::nearly_equal(pos2.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos2.get_y(), Distance(5000.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos2.get_z(), Distance(0.0 * km), REL_TOL));

    // Test case 3: Non-zero elevation
    Cylindrical<Earth> cyl3{ 8000.0 * km, 0.0 * rad, 1500.0 * km };
    auto pos3 = cyl3.get_position();
    ASSERT_TRUE(math::nearly_equal(pos3.get_x(), Distance(8000.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos3.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos3.get_z(), Distance(1500.0 * km), REL_TOL));

    // Test case 4: Arbitrary azimuth and elevation
    Cylindrical<Earth> cyl4{ 6000.0 * km, 45.0 * deg, 2000.0 * km };
    auto pos4          = cyl4.get_position();
    Distance expectedX = 6000.0 * km * cos(45.0 * deg);
    Distance expectedY = 6000.0 * km * sin(45.0 * deg);
    ASSERT_TRUE(math::nearly_equal(pos4.get_x(), expectedX, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos4.get_y(), expectedY, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos4.get_z(), Distance(2000.0 * km), REL_TOL));

    // Test case 5: Negative azimuth
    Cylindrical<Earth> cyl5{ 7000.0 * km, -60.0 * deg, 500.0 * km };
    auto pos5           = cyl5.get_position();
    Distance expectedX5 = 7000.0 * km * cos(-60.0 * deg);
    Distance expectedY5 = 7000.0 * km * sin(-60.0 * deg);
    ASSERT_TRUE(math::nearly_equal(pos5.get_x(), expectedX5, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos5.get_y(), expectedY5, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos5.get_z(), Distance(500.0 * km), REL_TOL));
}

TEST_F(CylindricalTest, GetPositionEci)
{
    // Test basic conversion from ECEF to ECI
    Cylindrical<Earth> cyl{ 10000.0 * km, 0.0 * rad, 0.0 * km };
    Date testEpoch;

    // Get position in ECI frame
    auto posEci = cyl.get_position(testEpoch);

    // Should return a valid RadiusVector in ICRF frame
    // The actual values depend on the frame transformation, but we can verify it's non-null
    // and has reasonable magnitude
    Distance magnitude =
        sqrt(posEci.get_x() * posEci.get_x() + posEci.get_y() * posEci.get_y() + posEci.get_z() * posEci.get_z());
    ASSERT_GT(magnitude.numerical_value_in(km), 0.0);

    // Test with non-zero elevation
    Cylindrical<Earth> cyl2{ 8000.0 * km, 45.0 * deg, 1500.0 * km };
    auto posEci2 = cyl2.get_position(testEpoch);
    Distance magnitude2 =
        sqrt(posEci2.get_x() * posEci2.get_x() + posEci2.get_y() * posEci2.get_y() + posEci2.get_z() * posEci2.get_z());
    ASSERT_GT(magnitude2.numerical_value_in(km), 0.0);
}
