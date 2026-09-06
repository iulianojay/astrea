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
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/state/orbital_elements/partials/EquinoctialPartial.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

class EquinoctialTest : public testing::Test {
  public:
    EquinoctialTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    Distance p = 7000.0 * km;
    Unitless f = 0.01 * one;
    Unitless g = 0.0 * one;
    Unitless h = 0.0 * one;
    Unitless k = 0.0 * one;
    Angle L    = 0.0 * rad;
    Equinoctial<frames::earth::icrf> state{ p, f, g, h, k, L };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(EquinoctialTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is EquinoctialPartial with partial derivatives
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(EquinoctialTest, EquinoctialPartialMultiplicationByTime)
{
    // Test EquinoctialPartial operator* with Time
    Velocity pDot        = 1.0 * km / s;
    UnitlessPerTime fDot = 0.001 / s;
    UnitlessPerTime gDot = 0.002 / s;
    UnitlessPerTime hDot = 0.003 / s;
    UnitlessPerTime kDot = 0.004 / s;
    AngularVelocity LDot = 0.5 * rad / s;
    EquinoctialPartial<frames::earth::icrf> partial(pDot, fDot, gDot, hDot, kDot, LDot);

    Time dt                                 = 2.0 * s;
    Equinoctial<frames::earth::icrf> result = partial * dt;

    // Verify the result is an Equinoctial state
    ASSERT_TRUE(math::nearly_equal(result.get_semilatus(), pDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_f(), fDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_g(), gDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_h(), hDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_k(), kDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_longitude(), LDot * dt, REL_TOL));
}

TEST_F(EquinoctialTest, EquinoctialPartialStream)
{
    // Test EquinoctialPartial stream operator
    Velocity pDot        = 1.0 * km / s;
    UnitlessPerTime fDot = 0.001 / s;
    UnitlessPerTime gDot = 0.002 / s;
    UnitlessPerTime hDot = 0.003 / s;
    UnitlessPerTime kDot = 0.004 / s;
    AngularVelocity LDot = 0.5 * rad / s;
    EquinoctialPartial<frames::earth::icrf> partial(pDot, fDot, gDot, hDot, kDot, LDot);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("EquinoctialPartial"), std::string::npos);
}
