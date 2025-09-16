#include <gtest/gtest.h>

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>

using namespace astrea;
using namespace astro;

class VehicleTest : public testing::Test {
  public:
    VehicleTest() = default;

    void SetUp() override
    {
        StateHistory history;
        history[Date()] = State();
        satWithHistory.store_state_history(history);

        vehicle            = Vehicle(sat);
        vehicleWithHistory = Vehicle(satWithHistory);
    }

    Spacecraft sat;
    Spacecraft satWithHistory;
    Vehicle vehicle;
    Vehicle vehicleWithHistory;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(VehicleTest, DefaultConstructor) { ASSERT_NO_THROW(Vehicle()); }

TEST_F(VehicleTest, CopyConstructor) { ASSERT_NO_THROW(Vehicle v(vehicle)); }

TEST_F(VehicleTest, MoveConstructor) { ASSERT_NO_THROW(Vehicle v(std::move(vehicle))); }

TEST_F(VehicleTest, AssignmentOperator)
{
    Vehicle other;
    ASSERT_NO_THROW(other = vehicle);
}

TEST_F(VehicleTest, MoveAssignment)
{
    Vehicle other;
    ASSERT_NO_THROW(other = std::move(vehicle));
}

TEST_F(VehicleTest, UpdateState)
{
    State state;
    ASSERT_NO_THROW(vehicle.update_state(state));
}

TEST_F(VehicleTest, GetState)
{
    State& vehicleState = vehicle.get_state();
    State& satState     = sat.get_state();
    ASSERT_EQ(vehicleState, satState);
}

TEST_F(VehicleTest, GetInitialState)
{
    const State& vehicleInitState = vehicle.get_initial_state();
    const State& satInitState     = sat.get_initial_state();
    ASSERT_EQ(vehicleInitState, satInitState);
}

TEST_F(VehicleTest, GetMass)
{
    Mass vehicleMass = vehicle.get_mass();
    Mass satMass     = sat.get_mass();
    ASSERT_EQ(vehicleMass, satMass);
}

TEST_F(VehicleTest, GetRamArea)
{
    SurfaceArea vehicleRamArea = vehicle.get_ram_area();
    SurfaceArea satRamArea     = sat.get_ram_area();
    ASSERT_EQ(vehicleRamArea, satRamArea);
}

TEST_F(VehicleTest, GetLiftArea)
{
    SurfaceArea vehicleLiftArea = vehicle.get_lift_area();
    SurfaceArea satLiftArea     = sat.get_lift_area();
    ASSERT_EQ(vehicleLiftArea, satLiftArea);
}

TEST_F(VehicleTest, GetSolarArea)
{
    SurfaceArea vehicleSolarArea = vehicle.get_solar_area();
    SurfaceArea satSolarArea     = sat.get_solar_area();
    ASSERT_EQ(vehicleSolarArea, satSolarArea);
}

TEST_F(VehicleTest, GetCoefficientOfDrag)
{
    Unitless vehicleDragCoefficient = vehicle.get_coefficient_of_drag();
    Unitless satDragCoefficient     = sat.get_coefficient_of_drag();
    ASSERT_EQ(vehicleDragCoefficient, satDragCoefficient);
}

TEST_F(VehicleTest, GetCoefficientOfLift)
{
    Unitless vehicleLiftCoefficient = vehicle.get_coefficient_of_lift();
    Unitless satLiftCoefficient     = sat.get_coefficient_of_lift();
    ASSERT_EQ(vehicleLiftCoefficient, satLiftCoefficient);
}

TEST_F(VehicleTest, GetCoefficientOfReflectivity)
{
    Unitless vehicleReflectivityCoefficient = vehicle.get_coefficient_of_reflectivity();
    Unitless satReflectivityCoefficient     = sat.get_coefficient_of_reflectivity();
    ASSERT_EQ(vehicleReflectivityCoefficient, satReflectivityCoefficient);
}

TEST_F(VehicleTest, Clear) { ASSERT_NO_THROW(vehicle.clear()); }

TEST_F(VehicleTest, GetInertialPosition)
{
    ASSERT_ANY_THROW({ auto v = vehicle.get_inertial_position(Date()); });
    ASSERT_NO_THROW({ auto v = vehicleWithHistory.get_inertial_position(Date()); });
}

TEST_F(VehicleTest, GetInertialVelocity)
{
    ASSERT_ANY_THROW({ auto v = vehicle.get_inertial_velocity(Date()); });
    ASSERT_NO_THROW({ auto v = vehicleWithHistory.get_inertial_velocity(Date()); });
}

TEST_F(VehicleTest, GetInertialAcceleration)
{
    ASSERT_NO_THROW({ auto v = vehicle.get_inertial_acceleration(Date()); }); // This function is defaulted so it shouldn't error
    ASSERT_NO_THROW({ auto v = vehicleWithHistory.get_inertial_acceleration(Date()); });
}

TEST_F(VehicleTest, GetName)
{
    std::string vehicleName = vehicle.get_name();
    std::string satName     = sat.get_name();
    ASSERT_EQ(vehicleName, satName);
}

TEST_F(VehicleTest, GetPtr)
{
    ASSERT_NO_THROW({ const void* p = static_cast<const Vehicle&>(vehicle).get_ptr(); });
    ASSERT_NO_THROW({ void* p = vehicle.get_ptr(); });
}
