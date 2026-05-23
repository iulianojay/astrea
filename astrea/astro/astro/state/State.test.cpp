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

#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;

class StateTest : public testing::Test {
  public:
    StateTest() {}

    void SetUp() override { state = State(elements, epoch); }

    State state;
    Date epoch;
    OrbitalElements elements;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(StateTest, DefaultConstructor) { ASSERT_NO_THROW(State()); }

TEST_F(StateTest, Constructor) { ASSERT_NO_THROW(State(elements)); }

TEST_F(StateTest, ConvertInPlace)
{
    state.convert_to_set<Keplerian<frames::earth::icrf>>();
    state.convert_to_set<Equinoctial<frames::earth::icrf>>();
    state.convert_to_set<Cartesian<frames::earth::icrf>>();
}

TEST_F(StateTest, Convert)
{
    const State constState = state;
    const State state1     = constState.convert_to_set<Keplerian<frames::earth::icrf>>();
    const State state2     = constState.convert_to_set<Equinoctial<frames::earth::icrf>>();
    const State state3     = constState.convert_to_set<Cartesian<frames::earth::icrf>>();
}

TEST_F(StateTest, Stream) { ASSERT_NO_THROW(std::cout << state); }
