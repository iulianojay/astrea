#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::s;

struct TestEvent {
    std::string get_name() const { return "Test Event"; }
    Unitless measure_event(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
    {
        return 42.0 * mp_units::one;
    }
    bool is_terminal() const { return false; }
    void trigger_action(Vehicle& vehicle) const {}
};

class EventTest : public testing::Test {
  public:
    EventTest() = default;
    void SetUp() override
    {
        event   = Event(testEvent);
        vehicle = Vehicle();
        time    = Time(0.0 * s);
        state   = OrbitalElements(Cartesian());
    }
    TestEvent testEvent;
    Event event;
    Vehicle vehicle;
    Time time;
    OrbitalElements state;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(EventTest, DefaultConstructor) { ASSERT_NO_THROW(Event()); }

TEST_F(EventTest, Constructor) { ASSERT_NO_THROW(Event(testEvent)); }

TEST_F(EventTest, CopyConstructor) { ASSERT_NO_THROW(Event e(event)); }

TEST_F(EventTest, MoveConstructor) { ASSERT_NO_THROW(Event e(std::move(event))); }

TEST_F(EventTest, CopyAssignment)
{
    Event other{ testEvent };
    ASSERT_NO_THROW(other = event);
}

TEST_F(EventTest, MoveAssignment)
{
    Event other{ testEvent };
    ASSERT_NO_THROW(other = std::move(event));
}

TEST_F(EventTest, GetName) { ASSERT_EQ(event.get_name(), "Test Event"); }

TEST_F(EventTest, MeasureEvent)
{
    Unitless result = event.measure_event(time, state, vehicle);
    ASSERT_EQ(result, 42.0 * one);
}

TEST_F(EventTest, IsTerminal) { ASSERT_FALSE(event.is_terminal()); }

TEST_F(EventTest, TriggerAction) { ASSERT_NO_THROW(event.trigger_action(vehicle)); }

TEST_F(EventTest, GetPtr)
{
    ASSERT_NO_THROW(auto ptr = static_cast<TestEvent*>(event.get_ptr()));
    ASSERT_NO_THROW(const auto constPtr = static_cast<const TestEvent*>(static_cast<const Event&>(event).get_ptr()));
}

TEST_F(EventTest, Extract)
{
    ASSERT_NO_THROW(const TestEvent* ptr = static_cast<const TestEvent*>(event.extract<TestEvent>()));
}
