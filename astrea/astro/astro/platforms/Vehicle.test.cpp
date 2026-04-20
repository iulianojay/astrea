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

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/StateHistory.hpp>

using namespace astrea;
using namespace astro;

class VehicleTest : public testing::Test {
  public:
    VehicleTest() = default;

    void SetUp() override
    {
        StateHistory history;
        history.insert(State());
        satWithHistory.set_state_history(history);

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

TEST_F(VehicleTest, GetInertialPosition)
{
    ASSERT_NO_THROW({ auto v = vehicle.get_inertial_position(Date()); });
    ASSERT_NO_THROW({ auto v = vehicleWithHistory.get_inertial_position(Date()); });
}

TEST_F(VehicleTest, GetInertialVelocity)
{
    ASSERT_NO_THROW({ auto v = vehicle.get_inertial_velocity(Date()); });
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

TEST_F(VehicleTest, ExtractMutableReference)
{
    // Test extracting the correct type (Spacecraft)
    auto* spacecraftPtr = vehicle.extract_mutable_reference<Spacecraft>();
    ASSERT_NE(spacecraftPtr, nullptr);
    ASSERT_EQ(spacecraftPtr->get_mass(), sat.get_mass());

    // Test with vehicle that has history
    auto* spacecraftWithHistoryPtr = vehicleWithHistory.extract_mutable_reference<Spacecraft>();
    ASSERT_NE(spacecraftWithHistoryPtr, nullptr);
    ASSERT_EQ(spacecraftWithHistoryPtr->get_mass(), satWithHistory.get_mass());

    // Test extracting wrong type - should return nullptr
    // Note: This would need a different vehicle type to test properly,
    // but for now we test that the method doesn't crash
    ASSERT_NO_THROW({ auto ptr = vehicle.extract_mutable_reference<Spacecraft>(); });
}
