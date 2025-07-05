#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astro;

class StateTest : public testing::Test {
  public:
    StateTest() {}

    void SetUp() override { state = State(time, elements); }

    State state;
    Time time;
    OrbitalElements elements;
    AstrodynamicsSystem sys;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(StateTest, DefaultConstructor) { ASSERT_NO_THROW(State()); }

TEST_F(StateTest, Constructor) { ASSERT_NO_THROW(State(time, elements)); }

TEST_F(StateTest, ConvertInPlace)
{
    state.convert<Keplerian>(sys);
    state.convert<Equinoctial>(sys);
    state.convert<Cartesian>(sys);
}

TEST_F(StateTest, Convert)
{
    const State constState = state;
    const State state1     = constState.convert<Keplerian>(sys);
    const State state2     = constState.convert<Equinoctial>(sys);
    const State state3     = constState.convert<Cartesian>(sys);
}

TEST_F(StateTest, Stream) { ASSERT_NO_THROW(std::cout << state); }
