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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

using namespace astrea;
using namespace astro;
using namespace planetary_bodies;

class AstrodynamicsSystemTest : public testing::Test {
  public:
    AstrodynamicsSystemTest() {}

    void SetUp() override {}

    AstrodynamicsSystem sys;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(AstrodynamicsSystemTest, DefaultConstructor)
{
    ASSERT_NO_THROW(AstrodynamicsSystem());
    ASSERT_EQ(sys.get_all_bodies().size(), 1);
    ASSERT_EQ(sys.get_central_body()->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, Constructor)
{
    ASSERT_NO_THROW(AstrodynamicsSystem(CelestialBodyId::MOON));
    ASSERT_NO_THROW(AstrodynamicsSystem(CelestialBodyId::MOON, { CelestialBodyId::EARTH, CelestialBodyId::SUN }));
}

TEST_F(AstrodynamicsSystemTest, Center) { ASSERT_EQ(sys.get_central_body()->get_name(), "Earth"); }

TEST_F(AstrodynamicsSystemTest, GetCenter)
{
    const auto& center = sys.get_central_body();
    ASSERT_EQ(center->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetExists)
{
    const auto& earth = sys.get(CelestialBodyId::EARTH);
    ASSERT_EQ(earth->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetDoesNotExist)
{
    ASSERT_ANY_THROW(sys.get(CelestialBodyId::MOON));
    sys.create(CelestialBodyId::MOON);
    ASSERT_NO_THROW(sys.get(CelestialBodyId::MOON));
}

TEST_F(AstrodynamicsSystemTest, GetAllBodies)
{
    const auto& bodies = sys.get_all_bodies();
    ASSERT_EQ(bodies.size(), 1);
}

TEST_F(AstrodynamicsSystemTest, Iterator) { ASSERT_NO_THROW(for (auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, Create)
{
    ASSERT_EQ(sys.size(), 1);
    ASSERT_NO_THROW(sys.create<Earth>());
    ASSERT_EQ(sys.size(), 1);
    sys.create<Moon>();
    ASSERT_EQ(sys.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, Clear)
{
    ASSERT_EQ(sys.size(), 1);
    sys.create<Jupiter>();
    ASSERT_EQ(sys.size(), 2);
    sys.clear();
    ASSERT_EQ(sys.size(), 0);
}

TEST_F(AstrodynamicsSystemTest, PropagateBodies) {}

TEST_F(AstrodynamicsSystemTest, GetRoot)
{
    sys.create(CelestialBodyId::MOON);
    sys.create(CelestialBodyId::EARTH);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::EARTH);
    sys.create(CelestialBodyId::SUN);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::SUN);
    sys.create(CelestialBodyId::JUPITER);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::SUN);
}
