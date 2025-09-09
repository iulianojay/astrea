#include <astro/astro.hpp>
#include <astro/propagation/event_detection/events/NullEvent.hpp>
#include <gtest/gtest.h>

using namespace astrea;
using namespace astro;

class NullEventTest : public testing::Test {
  public:
    NullEventTest() = default;
    void SetUp() override
    {
        event   = NullEvent();
        time    = Time(0.0 * mp_units::si::unit_symbols::s);
        state   = OrbitalElements(Cartesian());
        vehicle = Vehicle();
    }
    NullEvent event;
    Time time;
    OrbitalElements state;
    Vehicle vehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(NullEventTest, GetName) { ASSERT_EQ(event.get_name(), "NullEvent"); }

TEST_F(NullEventTest, MeasureEvent)
{
    Unitless result = event.measure_event(time, state, vehicle);
    ASSERT_EQ(result, 1.0 * mp_units::one);
}

TEST_F(NullEventTest, IsTerminal) { ASSERT_FALSE(event.is_terminal()); }
