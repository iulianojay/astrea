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
#include <astro/propagation/equations_of_motion/instances/CowellsMethod.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class CowellsMethodTest : public testing::Test {
  public:
    CowellsMethodTest() :
        eom(forces)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    ForceVector<frames::earth::icrf> noForce;
    Vehicle sat;
    Date epoch;
    ForceModel forces;
    CowellsMethod eom;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CowellsMethodTest, GetExpectedSet)
{
    ASSERT_EQ(eom.get_expected_set_id(), OrbitalElements::get_set_id<Cartesian<frames::earth::icrf>>());
}

TEST_F(CowellsMethodTest, Derivative)
{
    Cartesian<frames::earth::icrf> cart0           = Cartesian<frames::earth::icrf>::LEO(get_mu<planets::Earth>());
    CartesianPartial<frames::earth::icrf> expected = CartesianPartial<frames::earth::icrf>(
        cart0.get_vx(), cart0.get_vy(), cart0.get_vz(), -0.0081347028957142863 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s)
    );
    State state0(cart0, epoch);

    OrbitalElementPartials dstate = eom.compute_dynamics(state0, sat, noForce, noForce);
    ASSERT_TRUE(nearly_equal(expected, dstate, REL_TOL));
}

// Vallado, Ex. 8.5
TEST_F(CowellsMethodTest, DerivativeValladoEx85)
{
    Cartesian<frames::earth::icrf> cart0{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                                          -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    CartesianPartial<frames::earth::icrf> expected = CartesianPartial<frames::earth::icrf>(
        cart0.get_vx(), cart0.get_vy(), cart0.get_vz(), 0.00074873079 * km / (s * s), 0.00725534667 * km / (s * s), -0.00431725847 * km / (s * s)
    );
    State state0(cart0, epoch);

    OrbitalElementPartials dstate = eom.compute_dynamics(state0, sat, noForce, noForce);
    ASSERT_TRUE(nearly_equal(expected, dstate, REL_TOL));
}