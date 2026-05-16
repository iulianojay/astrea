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

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/angular_elements/instances/Geocentric.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class GeocentricTest : public testing::Test {
  public:
    GeocentricTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;

    Angle latitude    = 0.0 * astrea::detail::angle_unit;
    Angle longitude   = 0.0 * astrea::detail::angle_unit;
    Distance altitude = 10000.0 * km;
    Geocentric state{ latitude, longitude, altitude };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GeocentricTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << latitude.in(deg) << ", " << longitude.in(deg) << ", " << altitude << "] (Geocentric)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(GeocentricTest, DefaultConstructor) { ASSERT_NO_THROW(Geocentric()); }

TEST_F(GeocentricTest, UnitlessConstructor)
{
    Geocentric zeroState;
    ASSERT_TRUE(math::nearly_equal(zeroState.get_altitude(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(zeroState.get_latitude(), Angle(0.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(zeroState.get_longitude(), Angle(0.0 * rad), REL_TOL));

    Geocentric scaledState(2.0 * one);
    ASSERT_TRUE(math::nearly_equal(scaledState.get_altitude(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_latitude(), Angle(2.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_longitude(), Angle(2.0 * rad), REL_TOL));
}

TEST_F(GeocentricTest, ParameterizedConstructor) { ASSERT_NO_THROW(Geocentric(latitude, longitude, altitude)); }

TEST_F(GeocentricTest, EciVectorConstructor)
{
    RadiusVector<frames::earth::icrf> rEci{ 7000.0 * km, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Geocentric(rEci, epoch.get_central_body().get()));
}

TEST_F(GeocentricTest, EcefVectorConstructor)
{
    RadiusVector<frames::earth::earth_fixed> rEcef{ 7000.0 * km, 0.0 * km, 0.0 * km };
    ASSERT_NO_THROW(Geocentric(rEcef.get_central_body().get()));
}

TEST_F(GeocentricTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Geocentric(kep, epoch));
}

TEST_F(GeocentricTest, CopyConstructor) { ASSERT_NO_THROW(Geocentric newGeo(state)); }

TEST_F(GeocentricTest, MoveConstructor) { ASSERT_NO_THROW(Geocentric newGeo(std::move(state))); }

TEST_F(GeocentricTest, CopyAssignment) { ASSERT_NO_THROW(Geocentric newGeo = state); }

TEST_F(GeocentricTest, MoveAssignment) { ASSERT_NO_THROW(Geocentric newGeo = std::move(state)); }

TEST_F(GeocentricTest, EqualityOperator)
{
    Geocentric sameState{ latitude, longitude, altitude };
    Geocentric diffState{ latitude, longitude, altitude + 1.0 * km };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(GeocentricTest, AdditionOperator)
{
    Geocentric other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    Geocentric result = state + other;
    ASSERT_EQ(result.get_altitude(), altitude + 1.0 * km);
    ASSERT_EQ(result.get_latitude(), latitude + 1.0 * rad);
    ASSERT_EQ(result.get_longitude(), longitude + 1.0 * rad);
}

TEST_F(GeocentricTest, AdditionAssignmentOperator)
{
    Geocentric other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    state += other;
    ASSERT_EQ(state.get_altitude(), altitude + 1.0 * km);
    ASSERT_EQ(state.get_latitude(), latitude + 1.0 * rad);
    ASSERT_EQ(state.get_longitude(), longitude + 1.0 * rad);
}

TEST_F(GeocentricTest, SubtractionOperator)
{
    Geocentric other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    Geocentric result = state - other;
    ASSERT_EQ(result.get_altitude(), altitude - 1.0 * km);
    ASSERT_EQ(result.get_latitude(), latitude - 1.0 * rad);
    ASSERT_EQ(result.get_longitude(), longitude - 1.0 * rad);
}

TEST_F(GeocentricTest, SubtractionAssignmentOperator)
{
    Geocentric other{ 1.0 * rad, 1.0 * rad, 1.0 * km };
    state -= other;
    ASSERT_EQ(state.get_altitude(), altitude - 1.0 * km);
    ASSERT_EQ(state.get_latitude(), latitude - 1.0 * rad);
    ASSERT_EQ(state.get_longitude(), longitude - 1.0 * rad);
}

TEST_F(GeocentricTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Geocentric result   = state * multiplier;
    ASSERT_EQ(result.get_altitude(), altitude * multiplier);
    ASSERT_EQ(result.get_latitude(), latitude * multiplier);
    ASSERT_EQ(result.get_longitude(), longitude * multiplier);
}

TEST_F(GeocentricTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_EQ(state.get_altitude(), altitude * multiplier);
    ASSERT_EQ(state.get_latitude(), latitude * multiplier);
    ASSERT_EQ(state.get_longitude(), longitude * multiplier);
}

TEST_F(GeocentricTest, DivisionOperator)
{
    Unitless divisor  = 2.0 * one;
    Geocentric result = state / divisor;
    ASSERT_EQ(result.get_altitude(), altitude / divisor);
    ASSERT_EQ(result.get_latitude(), latitude / divisor);
    ASSERT_EQ(result.get_longitude(), longitude / divisor);
}

TEST_F(GeocentricTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_EQ(state.get_altitude(), altitude / divisor);
    ASSERT_EQ(state.get_latitude(), latitude / divisor);
    ASSERT_EQ(state.get_longitude(), longitude / divisor);
}

TEST_F(GeocentricTest, DivisionByGeocentricOperator)
{
    Geocentric other{ 2.0 * rad, 2.0 * rad, 2.0 * km };
    std::vector<Unitless> result = state / other;
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], latitude / other.get_latitude());
    ASSERT_EQ(result[1], longitude / other.get_longitude());
    ASSERT_EQ(result[2], altitude / other.get_altitude());
}

TEST_F(GeocentricTest, Interpolate)
{
    Geocentric other{ 1.5 * rad, 1.5 * rad, 20000.0 * km };
    Time thisTime     = seconds(0);
    Time otherTime    = seconds(10);
    Time targetTime   = seconds(5);
    Geocentric result = state.interpolate(thisTime, otherTime, other, targetTime);
    ASSERT_TRUE(math::nearly_equal(result.get_altitude(), Distance(15000.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_latitude(), Angle(0.75 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_longitude(), Angle(0.75 * rad), REL_TOL));
}

TEST_F(GeocentricTest, Getters)
{
    ASSERT_TRUE(math::nearly_equal(state.get_altitude(), altitude, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_latitude(), latitude, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_longitude(), longitude, REL_TOL));
}
