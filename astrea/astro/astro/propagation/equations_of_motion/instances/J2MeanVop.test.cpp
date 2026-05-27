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

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/instances/J2MeanVop.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <tests/utilities/comparisons.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class J2MeanTest : public testing::Test {
  public:
    J2MeanTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    ForceVector<frames::earth::icrf> noForce;
    Vehicle sat;
    Date epoch;
    J2MeanVop eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(J2MeanTest, GetExpectedSet)
{
    ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Keplerian<frames::earth::icrf>>());
}

TEST_F(J2MeanTest, Derivative)
{
    Keplerian<frames::earth::icrf> kep0            = Keplerian<frames::earth::icrf>::LEO();
    KeplerianPartial<frames::earth::icrf> expected = KeplerianPartial<frames::earth::icrf>(
        0.0 * km / s, 0.0 * 1 / s, 0.0 * rad / s, 0.0 * rad / s, 0.0 * rad / s, 0.0010780076129942077 * rad / s
    );

    State state(kep0, epoch);

    OrbitalElementPartials dstate = eom.compute_dynamics(state, sat, noForce, noForce);
    ASSERT_TRUE(nearly_equal(expected, dstate, REL_TOL));
}
