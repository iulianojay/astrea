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

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>
#include <astro/systems/system_utilities>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class SpacecraftTest : public testing::Test {
  public:
    SpacecraftTest() = default;
    void SetUp() override
    {
        StateHistory history;
        history.insert(State());
        spacecraftWithHistory.set_state_history(history);
    }

    CelestialBody sys;
    Spacecraft spacecraft;
    Spacecraft spacecraftWithHistory;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(SpacecraftTest, DefaultConstructor) { ASSERT_NO_THROW(Spacecraft()); }

TEST_F(SpacecraftTest, CopyConstructor) { ASSERT_NO_THROW(Spacecraft s(spacecraft)); }

TEST_F(SpacecraftTest, GpConstructor)
{
    GeneralPerturbations gp;
    ASSERT_ANY_THROW(Spacecraft s(gp, sys));

    gp.NORAD_CAT_ID   = 25544;
    gp.OBJECT_NAME    = "ISS";
    gp.SEMIMAJOR_AXIS = 6786.0;
    gp.ECCENTRICITY   = 0.001;
    gp.INCLINATION    = 51.6;
    gp.RA_OF_ASC_NODE = 0.0;
    ASSERT_ANY_THROW(Spacecraft s(gp, sys));

    gp.ARG_OF_PERICENTER = 0.0;
    gp.MEAN_ANOMALY      = 0.0;
    ASSERT_NO_THROW(Spacecraft s(gp, sys));
}

TEST_F(SpacecraftTest, AssignmentOperator)
{
    Spacecraft other;
    ASSERT_NO_THROW(other = spacecraft);
}

TEST_F(SpacecraftTest, EqualityOperator)
{
    Spacecraft other = spacecraft;
    ASSERT_TRUE(spacecraft == other);
    other.set_name("DifferentName");
    ASSERT_FALSE(spacecraft == other);
}

TEST_F(SpacecraftTest, GetMass) { ASSERT_EQ(spacecraft.get_mass(), Spacecraft::DEFAULT_MASS); }

TEST_F(SpacecraftTest, GetRamArea) { ASSERT_EQ(spacecraft.get_ram_area(), Spacecraft::DEFAULT_RAM_AREA); }

TEST_F(SpacecraftTest, GetLiftArea) { ASSERT_EQ(spacecraft.get_lift_area(), Spacecraft::DEFAULT_LIFT_AREA); }

TEST_F(SpacecraftTest, GetSolarArea) { ASSERT_EQ(spacecraft.get_solar_area(), Spacecraft::DEFAULT_SOLAR_AREA); }

TEST_F(SpacecraftTest, GetCoefficientOfDrag)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_drag(), Spacecraft::DEFAULT_COEFFICIENT_OF_DRAG);
}

TEST_F(SpacecraftTest, GetCoefficientOfLift)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_lift(), Spacecraft::DEFAULT_COEFFICIENT_OF_LIFT);
}

TEST_F(SpacecraftTest, GetCoefficientOfReflectivity)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_reflectivity(), Spacecraft::DEFAULT_COEFFICIENT_OF_REFLECTIVITY);
}

TEST_F(SpacecraftTest, GetName) { ASSERT_TRUE(spacecraft.get_name().empty()); }

TEST_F(SpacecraftTest, GetId) { ASSERT_NO_THROW(spacecraft.get_id()); }

TEST_F(SpacecraftTest, SetMass)
{
    Mass newMass = 1234.5 * kg;
    spacecraft.set_mass(newMass);
    ASSERT_EQ(spacecraft.get_mass(), newMass);
}

TEST_F(SpacecraftTest, SetCoefficientOfDrag)
{
    Unitless newCd = 3.3 * mp_units::one;
    spacecraft.set_coefficient_of_drag(newCd);
    ASSERT_EQ(spacecraft.get_coefficient_of_drag(), newCd);
}

TEST_F(SpacecraftTest, SetCoefficientOfLift)
{
    Unitless newCl = 2.2 * mp_units::one;
    spacecraft.set_coefficient_of_lift(newCl);
    ASSERT_EQ(spacecraft.get_coefficient_of_lift(), newCl);
}

TEST_F(SpacecraftTest, SetCoefficientOfReflectivity)
{
    Unitless newCr = 4.4 * mp_units::one;
    spacecraft.set_coefficient_of_reflectivity(newCr);
    ASSERT_EQ(spacecraft.get_coefficient_of_reflectivity(), newCr);
}

TEST_F(SpacecraftTest, SetRamArea)
{
    SurfaceArea newArea = 5.5 * mp_units::pow<2>(m);
    spacecraft.set_ram_area(newArea);
    ASSERT_EQ(spacecraft.get_ram_area(), newArea);
}

TEST_F(SpacecraftTest, SetSolarArea)
{
    SurfaceArea newArea = 6.6 * mp_units::pow<2>(m);
    spacecraft.set_solar_area(newArea);
    ASSERT_EQ(spacecraft.get_solar_area(), newArea);
}

TEST_F(SpacecraftTest, SetLiftArea)
{
    SurfaceArea newArea = 7.7 * mp_units::pow<2>(m);
    spacecraft.set_lift_area(newArea);
    ASSERT_EQ(spacecraft.get_lift_area(), newArea);
}

TEST_F(SpacecraftTest, SetName)
{
    std::string newName = "TestCraft";
    spacecraft.set_name(newName);
    ASSERT_EQ(spacecraft.get_name(), newName);
}

TEST_F(SpacecraftTest, GetStateHistory)
{
    ASSERT_EQ(spacecraftWithHistory.get_state_history().get_state_at(Date(), true), State());
    ASSERT_EQ(static_cast<const Spacecraft&>(spacecraftWithHistory).get_state_history().get_state_at(Date(), true), State());
}

TEST_F(SpacecraftTest, GetInertialPosition)
{
    ASSERT_ANY_THROW(spacecraft.get_inertial_position(Date()));
    ASSERT_NO_THROW(spacecraftWithHistory.get_inertial_position(Date()));
}

TEST_F(SpacecraftTest, GetInertialVelocity)
{
    ASSERT_ANY_THROW(spacecraft.get_inertial_velocity(Date()));
    ASSERT_NO_THROW(spacecraftWithHistory.get_inertial_velocity(Date()));
}

TEST_F(SpacecraftTest, AddPayload)
{
    ThrusterParameters thrusterParams(100.0 * N);

    // Test adding a payload
    ASSERT_NO_THROW(spacecraft.attach_payload(thrusterParams));

    // Verify the payload was added
    auto payloads = spacecraft.get_payloads();
    ASSERT_EQ(payloads.size(), 1);
}

TEST_F(SpacecraftTest, GetPayloads)
{
    // Initially should have no payloads
    auto payloads = spacecraft.get_payloads();
    ASSERT_EQ(payloads.size(), 0);

    // Add multiple thrusters
    ThrusterParameters thrusterParams1(100.0 * N);
    ThrusterParameters thrusterParams2(200.0 * N);

    spacecraft.attach_payload(thrusterParams1);
    spacecraft.attach_payload(thrusterParams2);

    // Verify we have 2 payloads
    payloads = spacecraft.get_payloads();
    ASSERT_EQ(payloads.size(), 2);

    // Test const version
    const Spacecraft& constSpacecraft = spacecraft;
    auto constPayloads                = constSpacecraft.get_payloads();
    ASSERT_EQ(constPayloads.size(), 2);
}

TEST_F(SpacecraftTest, ThrusterManagement)
{
    // Add thrusters to spacecraft
    ThrusterParameters thrusterParams1(100.0 * N);
    ThrusterParameters thrusterParams2(200.0 * N);

    spacecraft.attach_payload(thrusterParams1);
    spacecraft.attach_payload(thrusterParams2);

    auto payloads = spacecraft.get_payloads();
    ASSERT_EQ(payloads.size(), 2);

    // Test initial state (should be off)
    for (const auto& thruster : payloads) {
        ASSERT_FALSE(thruster.is_on());
    }

    // Turn all thrusters on
    for (auto& thruster : payloads) {
        thruster.switch_on();
        ASSERT_TRUE(thruster.is_on());
    }

    // Turn all thrusters off
    for (auto& thruster : payloads) {
        thruster.switch_off();
        ASSERT_FALSE(thruster.is_on());
    }
}
