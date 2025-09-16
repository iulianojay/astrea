#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/NullVehicle.hpp>
#include <astro/state/State.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class NullVehicleTest : public testing::Test {
  public:
    NullVehicleTest() = default;
    void SetUp() override
    {
        // Default NullVehicle
        nullVehicle = NullVehicle();
        // Custom NullVehicle
        customState       = State();
        customMass        = 42.0 * kg;
        customNullVehicle = NullVehicle(customState, customMass);
    }
    NullVehicle nullVehicle;
    State customState;
    Mass customMass;
    NullVehicle customNullVehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(NullVehicleTest, DefaultConstructor)
{
    ASSERT_EQ(nullVehicle.get_state(), State());
    ASSERT_EQ(nullVehicle.get_initial_state(), State());
    ASSERT_EQ(nullVehicle.get_mass(), 0.0 * kg);
    ASSERT_EQ(nullVehicle.get_name(), "NullVehicle");
}

TEST_F(NullVehicleTest, CustomConstructor)
{
    ASSERT_EQ(customNullVehicle.get_state(), customState);
    ASSERT_EQ(customNullVehicle.get_initial_state(), customState);
    ASSERT_EQ(customNullVehicle.get_mass(), customMass);
    ASSERT_EQ(customNullVehicle.get_name(), "NullVehicle");
}

TEST_F(NullVehicleTest, UpdateState)
{
    State newState;
    customNullVehicle.update_state(newState);
    ASSERT_EQ(customNullVehicle.get_state(), newState);
}

TEST_F(NullVehicleTest, Clone)
{
    NullVehicle* clonePtr = customNullVehicle.clone();
    ASSERT_EQ(clonePtr->get_state(), customNullVehicle.get_state());
    ASSERT_EQ(clonePtr->get_mass(), customNullVehicle.get_mass());
    ASSERT_EQ(clonePtr->get_name(), customNullVehicle.get_name());
    delete clonePtr;
}

TEST_F(NullVehicleTest, GetInertialPosition)
{
    Date d;
    auto pos = nullVehicle.get_inertial_position(d);
    ASSERT_EQ(pos.get_x(), 0.0 * km);
    ASSERT_EQ(pos.get_y(), 0.0 * km);
    ASSERT_EQ(pos.get_z(), 0.0 * km);
}

TEST_F(NullVehicleTest, GetInertialVelocity)
{
    Date d;
    auto vel = nullVehicle.get_inertial_velocity(d);
    ASSERT_EQ(vel.get_x(), 0.0 * km / s);
    ASSERT_EQ(vel.get_y(), 0.0 * km / s);
    ASSERT_EQ(vel.get_z(), 0.0 * km / s);
}

TEST_F(NullVehicleTest, GetInertialAcceleration)
{
    Date d;
    auto acc = nullVehicle.get_inertial_acceleration(d);
    ASSERT_EQ(acc.get_x(), 0.0 * km / (s * s));
    ASSERT_EQ(acc.get_y(), 0.0 * km / (s * s));
    ASSERT_EQ(acc.get_z(), 0.0 * km / (s * s));
}
