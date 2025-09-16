#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
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

        state0 = State(Cartesian(0.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch, sys);
        state1 = State(Cartesian(1.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch, sys);
        state2 = State(Cartesian(2.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 0.0 * km / s, 0.0 * km / s), epoch, sys);

        history.insert(epoch + time0, state0);
        history.insert(epoch + time1, state1);
    }

    StateHistory history;
    AstrodynamicsSystem sys;
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

TEST_F(StateHistoryTest, SubscriptOperator)
{
    ASSERT_EQ(history[epoch + time0], state0);
    ASSERT_EQ(history[epoch + time1], state1);

    ASSERT_EQ(history.size(), 2);
    history[epoch + time2] = state2;
    ASSERT_EQ(history.size(), 3);

    ASSERT_EQ(history[epoch + time2], state2);
}

TEST_F(StateHistoryTest, At)
{
    ASSERT_EQ(history.at(epoch + time0), state0);
    ASSERT_EQ(history.at(epoch + time1), state1);
    ASSERT_ANY_THROW(history.at(epoch + time2));
}

TEST_F(StateHistoryTest, Insert)
{
    ASSERT_EQ(history.size(), 2);
    history.insert(epoch + time2, state2);
    ASSERT_EQ(history.size(), 3);

    ASSERT_EQ(history.at(epoch + time2), state2);
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

TEST_F(StateHistoryTest, GetStateAt)
{

    StateHistory newHistory;
    newHistory.insert(epoch + time0, state0);
    newHistory.insert(epoch + time2, state2);
    ASSERT_EQ(history.get_state_at(epoch + time1), state1);
}

TEST_F(StateHistoryTest, Iterator) { ASSERT_NO_THROW(for (auto& [t, s] : history)); }

TEST_F(StateHistoryTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& [t, s] : history)); }
