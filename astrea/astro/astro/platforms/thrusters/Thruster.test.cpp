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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class ThrusterTest : public testing::Test {
  public:
    ThrusterTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Force thrust{ 1.0 * N };
    ThrusterParameters params{ thrust };
    Spacecraft sat;
    Thruster thruster{ sat, params };
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ThrusterTest, GetId) { ASSERT_EQ(thruster.get_id(), 0); }

TEST_F(ThrusterTest, GetImpulsiveDeltaV)
{
    ASSERT_EQ_QUANTITY(thruster.get_impulsive_delta_v(), thrust / sat.get_mass() * 1.0 * s, REL_TOL);
}
