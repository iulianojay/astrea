/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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

#include <astro/frames.hpp>
#include <astro/state/orbital_elements/partials/CartesianPartial.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

class CartesianPartialTest : public testing::Test {
  public:
    CartesianPartialTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    Distance x  = 7000.0 * km;
    Distance y  = 0.0 * km;
    Distance z  = 0.0 * km;
    Velocity vx = 0.0 * km / s;
    Velocity vy = 7.546 * km / s;
    Velocity vz = 0.0 * km / s;
    Cartesian<frames::earth::icrf> state{ x, y, z, vx, vy, vz };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CartesianPartialTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is CartesianPartial with velocity and acceleration components
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(CartesianPartialTest, CartesianPartialMultiplicationByTime)
{
    // Test CartesianPartial operator* with Time
    VelocityVector<frames::earth::icrf> vel{ 1.0 * km / s, 2.0 * km / s, 3.0 * km / s };
    AccelerationVector<frames::earth::icrf> acc{ 0.1 * km / s / s, 0.2 * km / s / s, 0.3 * km / s / s };
    CartesianPartial<frames::earth::icrf> partial(vel, acc);

    Time dt                               = 2.0 * s;
    Cartesian<frames::earth::icrf> result = partial * dt;

    // Verify the result is a Cartesian state
    ASSERT_TRUE(math::nearly_equal(result.get_x(), vel.get_x() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_y(), vel.get_y() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_z(), vel.get_z() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vx(), acc.get_x() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vy(), acc.get_y() * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_vz(), acc.get_z() * dt, REL_TOL));
}

TEST_F(CartesianPartialTest, CartesianPartialStream)
{
    // Test CartesianPartial stream operator
    VelocityVector<frames::earth::icrf> vel{ 1.0 * km / s, 2.0 * km / s, 3.0 * km / s };
    AccelerationVector<frames::earth::icrf> acc{ 0.1 * km / s / s, 0.2 * km / s / s, 0.3 * km / s / s };
    CartesianPartial<frames::earth::icrf> partial(vel, acc);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("CartesianPartial"), std::string::npos);
}
