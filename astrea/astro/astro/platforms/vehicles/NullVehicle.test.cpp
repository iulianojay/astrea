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

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/NullVehicle.hpp>

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
        customMass        = 42.0 * kg;
        customNullVehicle = NullVehicle(customMass);
    }
    NullVehicle nullVehicle;
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
    ASSERT_EQ(nullVehicle.get_mass(), 1.0 * kg);
    ASSERT_EQ(nullVehicle.get_name(), "NullVehicle");
}

TEST_F(NullVehicleTest, CustomConstructor)
{
    ASSERT_EQ(customNullVehicle.get_mass(), customMass);
    ASSERT_EQ(customNullVehicle.get_name(), "NullVehicle");
}

TEST_F(NullVehicleTest, Clone)
{
    NullVehicle* clonePtr = customNullVehicle.clone();
    ASSERT_EQ(clonePtr->get_mass(), customNullVehicle.get_mass());
    ASSERT_EQ(clonePtr->get_name(), customNullVehicle.get_name());
    delete clonePtr;
}
