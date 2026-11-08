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
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/state/orbital_elements/partials/KeplerianPartial.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

class KeplerianTest : public testing::Test {
  public:
    KeplerianTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    Distance a   = 7000.0 * km;
    Unitless ecc = 0.01 * one;
    Angle inc    = 98.0 * deg;
    Angle raan   = 40.0 * deg;
    Angle w      = 80.0 * deg;
    Angle theta  = 0.0 * deg;
    Keplerian<frames::earth::icrf> state{ a, ecc, inc, raan, w, theta };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(KeplerianTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is KeplerianPartial with partial derivatives
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(KeplerianTest, KeplerianPartialMultiplicationByTime)
{
    // Test KeplerianPartial operator* with Time
    Velocity aDot            = 1.0 * km / s;
    UnitlessPerTime eDot     = 0.001 / s;
    AngularVelocity incDot   = 0.1 * deg / s;
    AngularVelocity raanDot  = 0.2 * deg / s;
    AngularVelocity wDot     = 0.3 * deg / s;
    AngularVelocity thetaDot = 0.5 * deg / s;
    KeplerianPartial<frames::earth::icrf> partial(aDot, eDot, incDot, raanDot, wDot, thetaDot);

    Time dt                               = 2.0 * s;
    Keplerian<frames::earth::icrf> result = partial * dt;

    // Verify the result is a Keplerian state
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), aDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), eDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), incDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raanDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), wDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), thetaDot * dt, REL_TOL));
}

TEST_F(KeplerianTest, KeplerianPartialStream)
{
    // Test KeplerianPartial stream operator
    Velocity aDot            = 1.0 * km / s;
    UnitlessPerTime eDot     = 0.001 / s;
    AngularVelocity incDot   = 0.1 * deg / s;
    AngularVelocity raanDot  = 0.2 * deg / s;
    AngularVelocity wDot     = 0.3 * deg / s;
    AngularVelocity thetaDot = 0.5 * deg / s;
    KeplerianPartial<frames::earth::icrf> partial(aDot, eDot, incDot, raanDot, wDot, thetaDot);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("KeplerianPartial"), std::string::npos);
}
