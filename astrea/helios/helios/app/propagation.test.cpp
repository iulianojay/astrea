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

#include <helios/app/propagation.hpp>
#include <helios/helpers/database_fetcher.hpp>
#include <helios/types.hpp>

using namespace astrea;
using namespace astro;
using namespace helios;

class MultiObjectPropagationTest : public testing::Test {
  public:
    MultiObjectPropagationTest()
    {
        gpObjects = load_gp_from_db();
        gpObjects.resize(100); // Limit to 100 objects for testing purposes
    }

    void SetUp() override {}

    void propagate(const std::string& request)
    {
        const auto settings = astrea::helios::PropagationSettings(nlohmann::json::parse(request));
        const auto result   = propagate_many_objects(gpObjects, settings);
        for (const auto& frame : result.frames) {
            ASSERT_EQ(frame.size(), gpObjects.size());
        }
    }

    std::vector<GeneralPerturbations> gpObjects;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(MultiObjectPropagationTest, NoPerts)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": false,
            "fourty": false,
            "nbody": false,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, Drag)
{
    const auto request =
        R"({
            "drag": true,
            "eighty": false,
            "fourty": false,
            "nbody": false,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, SRP)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": false,
            "fourty": false,
            "nbody": false,
            "propMin": 90,
            "srp": true,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, NBody)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": false,
            "fourty": false,
            "nbody": true,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, TenByTen)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": false,
            "fourty": false,
            "nbody": false,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": true
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, FourtyByFourty)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": false,
            "fourty": true,
            "nbody": false,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, EightyByEighty)
{
    const auto request =
        R"({
            "drag": false,
            "eighty": true,
            "fourty": false,
            "nbody": false,
            "propMin": 90,
            "srp": false,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}

TEST_F(MultiObjectPropagationTest, AllPerts)
{
    const auto request =
        R"({
            "drag": true,
            "eighty": true,
            "fourty": false,
            "nbody": true,
            "propMin": 90,
            "srp": true,
            "stepMin": 5,
            "ten": false
        })";
    propagate(request);
}