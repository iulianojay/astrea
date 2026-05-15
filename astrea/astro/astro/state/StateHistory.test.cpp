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
#include <astro/state/StateHistory.hpp>
#include <astro/systems/system_utilities>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class StateHistoryTest : public testing::Test {
  public:
    StateHistoryTest() {}

    void SetUp() override
    {
        time0 = 0.0 * s;
        time1 = 1.0 * s;
        time2 = 2.0 * s;

        state0 = State(Cartesian(0.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch);
        state1 = State(Cartesian(1.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch + time1);
        state2 = State(Cartesian(2.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch + time2);

        history.insert(state0);
        history.insert(state1);
    }

    StateHistory history;
    Date epoch;
    Time time0, time1, time2;
    State state0, state1, state2;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(StateHistoryTest, DefaultConstructor) { ASSERT_NO_THROW(StateHistory()); }

TEST_F(StateHistoryTest, IdConstructor) { ASSERT_NO_THROW(StateHistory(0)); }

TEST_F(StateHistoryTest, GetStateAtExact)
{
    // Test getting exact states that exist
    ASSERT_EQ(history.get_state_at(epoch + time0, true), state0);
    ASSERT_EQ(history.get_state_at(epoch + time1, true), state1);

    // Test inserting a new state
    ASSERT_EQ(history.size(), 2);
    history.insert(state2);
    ASSERT_EQ(history.size(), 3);

    ASSERT_EQ(history.get_state_at(epoch + time2, true), state2);
}

TEST_F(StateHistoryTest, GetStateAtWithoutApproximation)
{
    // Test getting exact states with allowApproximation=false
    ASSERT_EQ(history.get_state_at(epoch + time0, false), state0);
    ASSERT_EQ(history.get_state_at(epoch + time1, false), state1);
    // Should throw when state doesn't exist and no approximation allowed
    ASSERT_ANY_THROW(history.get_state_at(epoch + time2, false));
}

TEST_F(StateHistoryTest, Insert)
{
    ASSERT_EQ(history.size(), 2);
    history.insert(state2);
    ASSERT_EQ(history.size(), 3);

    ASSERT_EQ(history.get_state_at(epoch + time2, true), state2);
}

TEST_F(StateHistoryTest, Size)
{
    ASSERT_EQ(history.size(), 2);
    const StateHistory newHistory;
    ASSERT_EQ(newHistory.size(), 0);
}

TEST_F(StateHistoryTest, Clear)
{
    ASSERT_EQ(history.size(), 2);
    history.clear();
    ASSERT_EQ(history.size(), 0);
}

TEST_F(StateHistoryTest, First) { ASSERT_EQ(history.first(), state0); }

TEST_F(StateHistoryTest, Last) { ASSERT_EQ(history.last(), state1); }

TEST_F(StateHistoryTest, SetObjectId)
{
    ASSERT_EQ(history.get_object_id(), 0);
    history.set_object_id(1);
    ASSERT_EQ(history.get_object_id(), 1);
}

TEST_F(StateHistoryTest, GetObjectId) { ASSERT_EQ(history.get_object_id(), 0); }

TEST_F(StateHistoryTest, GetClosestState)
{
    ASSERT_EQ(history.get_closest_state(epoch + 0.25 * s), state0);
    ASSERT_EQ(history.get_closest_state(epoch + 0.75 * s), state1);
}

TEST_F(StateHistoryTest, GetClosestStateBeforeFirstEpoch)
{
    ASSERT_EQ(history.get_closest_state(epoch - time1), state0);
}

TEST_F(StateHistoryTest, GetClosestStateAfterLastEpoch)
{
    ASSERT_EQ(history.get_closest_state(epoch + 2.0 * time1), state1);
}

TEST_F(StateHistoryTest, GetStateAt)
{
    StateHistory newHistory;
    newHistory.insert(state0);
    newHistory.insert(state2);
    ASSERT_EQ(newHistory.get_state_at(epoch + time1), state1);
}

TEST_F(StateHistoryTest, GetStateAtBeforeFirstEpoch) { ASSERT_ANY_THROW(history.get_state_at(epoch - time2)); }

TEST_F(StateHistoryTest, GetStateAtAfterLastEpoch) { ASSERT_ANY_THROW(history.get_state_at(epoch + 2.0 * time1)); }

TEST_F(StateHistoryTest, Iterator)
{
    ASSERT_NO_THROW(for (auto& state : history) { (void)state; });
}

TEST_F(StateHistoryTest, ConstIterator)
{
    ASSERT_NO_THROW(for (const auto& state : history) { (void)state; });
}

TEST_F(StateHistoryTest, FastAppend)
{
    StateHistory newHistory;
    ASSERT_EQ(newHistory.size(), 0);

    newHistory.fast_append(state0);
    ASSERT_EQ(newHistory.size(), 1);
    ASSERT_EQ(newHistory.first(), state0);

    newHistory.fast_append(state1);
    ASSERT_EQ(newHistory.size(), 2);
    ASSERT_EQ(newHistory.last(), state1);
}

TEST_F(StateHistoryTest, FastPrepend)
{
    StateHistory newHistory;
    ASSERT_EQ(newHistory.size(), 0);

    newHistory.fast_prepend(state1);
    ASSERT_EQ(newHistory.size(), 1);
    ASSERT_EQ(newHistory.first(), state1);

    newHistory.fast_prepend(state0);
    ASSERT_EQ(newHistory.size(), 2);
    ASSERT_EQ(newHistory.first(), state0);
}
