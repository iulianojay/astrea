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

#include <math/comparisons.hpp>
#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
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

class CartesianTest : public testing::Test {
  public:
    CartesianTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    AstrodynamicsSystem sys;

    Distance x  = 7000.0 * km;
    Distance y  = 0.0 * km;
    Distance z  = 0.0 * km;
    Velocity vx = 0.0 * km / s;
    Velocity vy = 7.546 * km / s;
    Velocity vz = 0.0 * km / s;
    Cartesian state{ x, y, z, vx, vy, vz };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CartesianTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << x << ", " << y << ", " << z << ", " << vx << ", " << vy << ", " << vz << "] (Cartesian)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(CartesianTest, DefaultConstructor)
{
    Cartesian defaultState;
    ASSERT_TRUE(math::nearly_equal(defaultState.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_z(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_vx(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_vy(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_vz(), Velocity(0.0 * km / s), REL_TOL));
}

TEST_F(CartesianTest, UnitlessConstructor)
{
    Cartesian scaledState(2.0 * one);
    ASSERT_TRUE(math::nearly_equal(scaledState.get_x(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_y(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_z(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_vx(), Velocity(2.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_vy(), Velocity(2.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_vz(), Velocity(2.0 * km / s), REL_TOL));
}

TEST_F(CartesianTest, VectorConstructor)
{
    RadiusVector<frames::earth::icrf> r{ x, y, z };
    VelocityVector<frames::earth::icrf> v{ vx, vy, vz };
    ASSERT_NO_THROW(Cartesian(r, v));
}

TEST_F(CartesianTest, ParameterizedConstructor) { ASSERT_NO_THROW(Cartesian(x, y, z, vx, vy, vz)); }

TEST_F(CartesianTest, CartesianConstructor)
{
    Cartesian other{ 5000.0 * km, 1000.0 * km, 2000.0 * km, 1.0 * km / s, 2.0 * km / s, 3.0 * km / s };
    ASSERT_NO_THROW(Cartesian(other, sys.get_mu()));
}

TEST_F(CartesianTest, KeplerianConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Cartesian(kep, sys.get_mu()));
}

TEST_F(CartesianTest, EquinoctialConstructor)
{
    Equinoctial equi{ 7000.0 * km, 0.01 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad };
    ASSERT_NO_THROW(Cartesian(equi, sys.get_mu()));
}

TEST_F(CartesianTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    OrbitalElements elements(kep);
    ASSERT_NO_THROW(Cartesian(elements, sys.get_mu()));
}

TEST_F(CartesianTest, LEOStaticMethod)
{
    ASSERT_NO_THROW(Cartesian::LEO(sys.get_mu()));
    auto leo = Cartesian::LEO(sys.get_mu());
    ASSERT_GT(leo.get_x().numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, LMEOStaticMethod)
{
    ASSERT_NO_THROW(Cartesian::LMEO(sys.get_mu()));
    auto lmeo = Cartesian::LMEO(sys.get_mu());
    ASSERT_GT(lmeo.get_x().numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, GPSStaticMethod)
{
    ASSERT_NO_THROW(Cartesian::GPS(sys.get_mu()));
    auto gps = Cartesian::GPS(sys.get_mu());
    ASSERT_GT(gps.get_x().numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, HMEOStaticMethod)
{
    ASSERT_NO_THROW(Cartesian::HMEO(sys.get_mu()));
    auto hmeo = Cartesian::HMEO(sys.get_mu());
    ASSERT_GT(hmeo.get_x().numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, GEOStaticMethod)
{
    ASSERT_NO_THROW(Cartesian::GEO(sys.get_mu()));
    auto geo = Cartesian::GEO(sys.get_mu());
    ASSERT_GT(geo.get_x().numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, CopyConstructor)
{
    ASSERT_NO_THROW(Cartesian newCart(state));
    Cartesian newCart(state);
    ASSERT_TRUE(math::nearly_equal(newCart.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, MoveConstructor)
{
    Cartesian temp{ x, y, z, vx, vy, vz };
    ASSERT_NO_THROW(Cartesian newCart(std::move(temp)));
}

TEST_F(CartesianTest, CopyAssignment)
{
    ASSERT_NO_THROW(Cartesian newCart = state);
    Cartesian newCart = state;
    ASSERT_TRUE(math::nearly_equal(newCart.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newCart.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, MoveAssignment)
{
    Cartesian temp{ x, y, z, vx, vy, vz };
    ASSERT_NO_THROW(Cartesian newCart = std::move(temp));
}

TEST_F(CartesianTest, EqualityOperator)
{
    Cartesian sameState{ x, y, z, vx, vy, vz };
    Cartesian diffState{ x + 1.0 * km, y, z, vx, vy, vz };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(CartesianTest, AdditionOperator)
{
    Cartesian other{ 1000.0 * km, 500.0 * km, 250.0 * km, 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    Cartesian result = state + other;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y + 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z + 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx + 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy + 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz + 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, AdditionOperatorRadiusVector)
{
    RadiusVector<frames::earth::icrf> r{ 1000.0 * km, 500.0 * km, 250.0 * km };
    Cartesian result = state + r;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y + 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z + 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, AdditionOperatorVelocityVector)
{
    VelocityVector<frames::earth::icrf> v{ 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    Cartesian result = state + v;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx + 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy + 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz + 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, AdditionAssignmentOperator)
{
    Cartesian other{ 1000.0 * km, 500.0 * km, 250.0 * km, 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    state += other;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y + 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z + 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx + 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy + 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz + 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, AdditionAssignmentOperatorRadiusVector)
{
    RadiusVector<frames::earth::icrf> r{ 1000.0 * km, 500.0 * km, 250.0 * km };
    state += r;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y + 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z + 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, AdditionAssignmentOperatorVelocityVector)
{
    VelocityVector<frames::earth::icrf> v{ 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    state += v;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx + 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy + 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz + 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, SubtractionOperator)
{
    Cartesian other{ 1000.0 * km, 500.0 * km, 250.0 * km, 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    Cartesian result = state - other;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y - 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z - 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx - 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy - 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz - 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, SubtractionOperatorRadiusVector)
{
    RadiusVector<frames::earth::icrf> r{ 1000.0 * km, 500.0 * km, 250.0 * km };
    Cartesian result = state - r;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y - 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z - 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, SubtractionOperatorVelocityVector)
{
    VelocityVector<frames::earth::icrf> v{ 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    Cartesian result = state - v;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx - 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy - 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz - 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, SubtractionAssignmentOperator)
{
    Cartesian other{ 1000.0 * km, 500.0 * km, 250.0 * km, 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    state -= other;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y - 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z - 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx - 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy - 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz - 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, SubtractionAssignmentOperatorRadiusVector)
{
    RadiusVector<frames::earth::icrf> r{ 1000.0 * km, 500.0 * km, 250.0 * km };
    state -= r;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y - 500.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z - 250.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz, REL_TOL));
}

TEST_F(CartesianTest, SubtractionAssignmentOperatorVelocityVector)
{
    VelocityVector<frames::earth::icrf> v{ 0.1 * km / s, 0.2 * km / s, 0.3 * km / s };
    state -= v;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx - 0.1 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy - 0.2 * km / s, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz - 0.3 * km / s, REL_TOL));
}

TEST_F(CartesianTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Cartesian result    = state * multiplier;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz * multiplier, REL_TOL));
}

TEST_F(CartesianTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz * multiplier, REL_TOL));
}

TEST_F(CartesianTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is CartesianPartial with velocity and acceleration components
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(CartesianTest, DivisionByScalarOperator)
{
    Unitless divisor = 2.0 * one;
    Cartesian result = state / divisor;
    ASSERT_TRUE(math::nearly_equal(result.get_x(), x / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), y / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), z / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), vx / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), vy / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), vz / divisor, REL_TOL));
}

TEST_F(CartesianTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_TRUE(math::nearly_equal(state.get_x(), x / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_y(), y / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_z(), z / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz / divisor, REL_TOL));
}

TEST_F(CartesianTest, GetPosition)
{
    const auto& pos = state.get_position();
    ASSERT_TRUE(math::nearly_equal(pos.get_x(), x, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos.get_y(), y, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(pos.get_z(), z, REL_TOL));
}

TEST_F(CartesianTest, GetVelocity)
{
    const auto& vel = state.get_velocity();
    ASSERT_TRUE(math::nearly_equal(vel.get_x(), vx, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vel.get_y(), vy, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vel.get_z(), vz, REL_TOL));
}

TEST_F(CartesianTest, GetX) { ASSERT_TRUE(math::nearly_equal(state.get_x(), x, REL_TOL)); }

TEST_F(CartesianTest, GetY) { ASSERT_TRUE(math::nearly_equal(state.get_y(), y, REL_TOL)); }

TEST_F(CartesianTest, GetZ) { ASSERT_TRUE(math::nearly_equal(state.get_z(), z, REL_TOL)); }

TEST_F(CartesianTest, GetVx) { ASSERT_TRUE(math::nearly_equal(state.get_vx(), vx, REL_TOL)); }

TEST_F(CartesianTest, GetVy) { ASSERT_TRUE(math::nearly_equal(state.get_vy(), vy, REL_TOL)); }

TEST_F(CartesianTest, GetVz) { ASSERT_TRUE(math::nearly_equal(state.get_vz(), vz, REL_TOL)); }

TEST_F(CartesianTest, ToVector)
{
    std::vector<Unitless> vec = state.force_to_vector();
    ASSERT_EQ(vec.size(), 6);
    ASSERT_TRUE(math::nearly_equal(vec[0], x / (1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[1], y / (1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[2], z / (1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[3], vx / (1.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[4], vy / (1.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[5], vz / (1.0 * km / s), REL_TOL));
}

TEST_F(CartesianTest, Interpolate)
{
    Cartesian other{ 14000.0 * km, 2000.0 * km, 500.0 * km, 1.0 * km / s, 5.0 * km / s, 1.0 * km / s };
    Time thisTime    = 0.0 * s;
    Time otherTime   = 10.0 * s;
    Time targetTime  = 5.0 * s;
    Cartesian result = state.interpolate(thisTime, otherTime, other, sys.get_mu(), targetTime);

    // At t=5s (midpoint), expect average of start and end values
    ASSERT_TRUE(math::nearly_equal(result.get_x(), (x + 14000.0 * km) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), (y + 2000.0 * km) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), (z + 500.0 * km) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), (vx + 1.0 * km / s) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), (vy + 5.0 * km / s) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), (vz + 1.0 * km / s) / 2.0, REL_TOL));
}

TEST_F(CartesianTest, FromKeplerianConversion)
{
    // Test conversion from Keplerian to Cartesian and back
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    Cartesian cart(kep, sys.get_mu());

    // Verify the Cartesian state is non-zero
    Distance r_mag = sqrt(cart.get_x() * cart.get_x() + cart.get_y() * cart.get_y() + cart.get_z() * cart.get_z());
    ASSERT_GT(r_mag.numerical_value_in(km), 0.0);

    Velocity v_mag = sqrt(cart.get_vx() * cart.get_vx() + cart.get_vy() * cart.get_vy() + cart.get_vz() * cart.get_vz());
    ASSERT_GT(v_mag.numerical_value_in(km / s), 0.0);
}

TEST_F(CartesianTest, FromEquinoctialConversion)
{
    // Test conversion from Equinoctial to Cartesian
    Equinoctial equi{ 7000.0 * km, 0.01 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad };
    Cartesian cart(equi, sys.get_mu());

    // Verify the Cartesian state is non-zero
    Distance r_mag = sqrt(cart.get_x() * cart.get_x() + cart.get_y() * cart.get_y() + cart.get_z() * cart.get_z());
    ASSERT_GT(r_mag.numerical_value_in(km), 0.0);
}

TEST_F(CartesianTest, ZeroSemimajorKeplerianConversion)
{
    // Test edge case with zero semimajor axis
    Keplerian kep{ 0.0 * km, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg };
    Cartesian cart(kep, sys.get_mu());

    ASSERT_TRUE(math::nearly_equal(cart.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_z(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vx(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vy(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vz(), Velocity(0.0 * km / s), REL_TOL));
}

TEST_F(CartesianTest, ZeroSemilatusEquinoctialConversion)
{
    // Test edge case with zero semilatus
    Equinoctial equi{ 0.0 * km, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad };
    Cartesian cart(equi, sys.get_mu());

    ASSERT_TRUE(math::nearly_equal(cart.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_z(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vx(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vy(), Velocity(0.0 * km / s), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(cart.get_vz(), Velocity(0.0 * km / s), REL_TOL));
}

TEST_F(CartesianTest, CartesianPartialMultiplicationByTime)
{
    // Test CartesianPartial operator* with Time
    VelocityVector<frames::earth::icrf> vel{ 1.0 * km / s, 2.0 * km / s, 3.0 * km / s };
    AccelerationVector<frames::earth::icrf> acc{ 0.1 * km / s / s, 0.2 * km / s / s, 0.3 * km / s / s };
    CartesianPartial partial(vel, acc);

    Time dt          = 2.0 * s;
    Cartesian result = partial * dt;

    // Verify the result is a Cartesian state
    ASSERT_TRUE(math::nearly_equal(result.get_x(), vel.get_x() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), vel.get_y() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), vel.get_z() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), acc.get_x() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), acc.get_y() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), acc.get_z() * dt, REL_TOL));
}

TEST_F(CartesianTest, CartesianPartialStream)
{
    // Test CartesianPartial stream operator
    VelocityVector<frames::earth::icrf> vel{ 1.0 * km / s, 2.0 * km / s, 3.0 * km / s };
    AccelerationVector<frames::earth::icrf> acc{ 0.1 * km / s / s, 0.2 * km / s / s, 0.3 * km / s / s };
    CartesianPartial partial(vel, acc);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("CartesianPartial"), std::string::npos);
}
