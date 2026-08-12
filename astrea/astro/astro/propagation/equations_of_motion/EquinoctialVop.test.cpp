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
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/systems/system_utilities.hpp>
#include <tests/utilities/comparisons.hpp>

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class EquinoctialTest : public testing::Test {
  public:
    EquinoctialTest() :
        eom(forces)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    const GravParam mu = get_mu<frames::primary.origin>();
    ForceVector<frames::earth::icrf> noForce;
    Vehicle sat;
    Date epoch;
    ForceModel forces;
    EquinoctialVop eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(EquinoctialTest, GetExpectedSet)
{
    ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Equinoctial<frames::earth::icrf>>());
}

TEST_F(EquinoctialTest, Derivative)
{
    Equinoctial<frames::earth::icrf> equi0 = Equinoctial<frames::earth::icrf>::LEO(mu);
    EquinoctialPartial<frames::earth::icrf> expected =
        EquinoctialPartial<frames::earth::icrf>(0.0 * km / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0 * 1 / s, 0.0010780076129942077 * rad / s);
    State state(equi0, epoch);

    OrbitalElementPartials dstate = eom.compute_dynamics(state, sat, noForce, noForce);
    ASSERT_TRUE(nearly_equal(expected, dstate, REL_TOL));
}