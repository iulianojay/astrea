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

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;

class SensorTest : public testing::Test {
  public:
    SensorTest() = default;

    void SetUp() override
    {
        fov        = CircularFieldOfView(std::numbers::pi / 4.0 * rad);
        parameters = SensorParameters(&fov);
        sensor     = new Sensor(viewer, parameters);
    }

    void TearDown() override { delete sensor; }

    CircularFieldOfView fov;
    SensorParameters parameters;
    Viewer viewer;
    Sensor* sensor;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(SensorTest, Constructor) { ASSERT_NO_THROW(Sensor(viewer, parameters)); }

TEST_F(SensorTest, GetId) { ASSERT_NO_THROW(sensor->get_id()); }

// TEST_F(SensorTest, Contains)
// {
//     RadiusVector<frames::earth::icrf> sensor2target(1.0 * km, 0.0 * km, 0.0 * km);
//     ASSERT_TRUE(sensor->contains(sensor2target, Date()));
// }

TEST_F(SensorTest, GetFov) { ASSERT_EQ(parameters.get_fov(), static_cast<const FieldOfView*>(&fov)); }

TEST_F(SensorTest, SetFov)
{
    CircularFieldOfView newFov(0.5 * std::numbers::pi * rad);
    parameters.set_fov(&newFov);
    ASSERT_EQ(parameters.get_fov(), static_cast<const FieldOfView*>(&newFov));
}
