#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;

class StateTest : public testing::Test {
  public:
    StateTest() {}

    void SetUp() override { state = State(elements, epoch, sys); }

    State state;
    Date epoch;
    AstrodynamicsSystem sys;
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
    state.convert<Keplerian>();
    state.convert<Equinoctial>();
    state.convert<Cartesian>();
}

TEST_F(StateTest, Convert)
{
    const State constState = state;
    const State state1     = constState.convert<Keplerian>();
    const State state2     = constState.convert<Equinoctial>();
    const State state3     = constState.convert<Cartesian>();
}

TEST_F(StateTest, Stream) { ASSERT_NO_THROW(std::cout << state); }
