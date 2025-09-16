#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>

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
    state.convert_to_set<Keplerian>();
    state.convert_to_set<Equinoctial>();
    state.convert_to_set<Cartesian>();
}

TEST_F(StateTest, Convert)
{
    const State constState = state;
    const State state1     = constState.convert_to_set<Keplerian>();
    const State state2     = constState.convert_to_set<Equinoctial>();
    const State state3     = constState.convert_to_set<Cartesian>();
}

TEST_F(StateTest, Stream) { ASSERT_NO_THROW(std::cout << state); }
