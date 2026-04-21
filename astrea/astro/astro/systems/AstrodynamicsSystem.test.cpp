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

#include <astro/frames/CartesianVector.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

using namespace astrea;
using namespace astro;
using namespace planetary_bodies;
using mp_units::si::unit_symbols::km;

class AstrodynamicsSystemTest : public testing::Test {
  public:
    AstrodynamicsSystemTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

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
    const auto& earth = sys.get_body(CelestialBodyId::EARTH);
    ASSERT_EQ(earth->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetDoesNotExist)
{
    ASSERT_ANY_THROW(sys.get_body(CelestialBodyId::MOON));
    sys.add_body(CelestialBodyId::MOON);
    ASSERT_NO_THROW(sys.get_body(CelestialBodyId::MOON));
}

TEST_F(AstrodynamicsSystemTest, GetAllBodies)
{
    const auto& bodies = sys.get_all_bodies();
    ASSERT_EQ(bodies.size(), 1);
}

TEST_F(AstrodynamicsSystemTest, BuildEachBodyByType)
{
    AstrodynamicsSystem newSys;
    ASSERT_NO_THROW(newSys.add_body<Mercury>());
    ASSERT_NO_THROW(newSys.add_body<Venus>());
    ASSERT_NO_THROW(newSys.add_body<Moon>());
    ASSERT_NO_THROW(newSys.add_body<Mars>());
    ASSERT_NO_THROW(newSys.add_body<Phobos>());
    ASSERT_NO_THROW(newSys.add_body<Deimos>());
    ASSERT_NO_THROW(newSys.add_body<Jupiter>());
    ASSERT_NO_THROW(newSys.add_body<Ganymede>());
    ASSERT_NO_THROW(newSys.add_body<Callisto>());
    ASSERT_NO_THROW(newSys.add_body<Europa>());
    ASSERT_NO_THROW(newSys.add_body<Io>());
    ASSERT_NO_THROW(newSys.add_body<Saturn>());
    ASSERT_NO_THROW(newSys.add_body<Rhea>());
    ASSERT_NO_THROW(newSys.add_body<Iapetus>());
    ASSERT_NO_THROW(newSys.add_body<Titan>());
    ASSERT_NO_THROW(newSys.add_body<Uranus>());
    ASSERT_NO_THROW(newSys.add_body<Oberon>());
    ASSERT_NO_THROW(newSys.add_body<Titania>());
    ASSERT_NO_THROW(newSys.add_body<Neptune>());
    ASSERT_NO_THROW(newSys.add_body<Triton>());
}

TEST_F(AstrodynamicsSystemTest, BuildEachBodyByTag)
{
    AstrodynamicsSystem newSys;
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::MERCURY));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::VENUS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::MOON));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::MARS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::PHOBOS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::DEIMOS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::JUPITER));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::GANYMEDE));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::CALLISTO));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::EUROPA));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::IO));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::SATURN));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::RHEA));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::IAPETUS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::TITAN));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::URANUS));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::OBERON));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::TITANIA));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::NEPTUNE));
    ASSERT_NO_THROW(newSys.add_body(CelestialBodyId::TRITON));
}

TEST_F(AstrodynamicsSystemTest, Size) { ASSERT_EQ(sys.size(), 1); }

TEST_F(AstrodynamicsSystemTest, Iterator) { ASSERT_NO_THROW(for (auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, Create)
{
    ASSERT_EQ(sys.size(), 1);
    ASSERT_NO_THROW(sys.add_body<Earth>());
    ASSERT_EQ(sys.size(), 1);
    sys.add_body<Moon>();
    ASSERT_EQ(sys.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, Clear)
{
    ASSERT_EQ(sys.size(), 1);
    sys.add_body<Jupiter>();
    ASSERT_EQ(sys.size(), 2);
    sys.clear();
    ASSERT_EQ(sys.size(), 0);
}

TEST_F(AstrodynamicsSystemTest, GetRoot)
{
    sys.add_body(CelestialBodyId::MOON);
    sys.add_body(CelestialBodyId::EARTH);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::EARTH);
    sys.add_body(CelestialBodyId::SUN);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::SUN);
    sys.add_body(CelestialBodyId::JUPITER);
    ASSERT_EQ(sys.get_system_root(), CelestialBodyId::SUN);
}

TEST_F(AstrodynamicsSystemTest, GetMuCentralBody)
{
    const auto mu = sys.get_mu();
    ASSERT_TRUE(math::nearly_equal(mu, Earth().get_mu(), REL_TOL));
}


TEST_F(AstrodynamicsSystemTest, GetRelativePosition)
{
    // const Date date("2020-02-18 15:08:47.23847");
    // AstrodynamicsSystem earthMoonSys(CelestialBodyId::EARTH, { CelestialBodyId::MOON });

    // ASSERT_NO_THROW(earthMoonSys.get_relative_position(date, CelestialBodyId::MOON, CelestialBodyId::EARTH));
    // const auto moonToEarthRelPos = earthMoonSys.get_relative_position(date, CelestialBodyId::MOON, CelestialBodyId::EARTH);

    // // Moon is roughly 384,000 km from Earth
    // const auto distance = moonToEarthRelPos.norm();
    // ASSERT_GT(distance.numerical_value_in(km), 300000.0);
    // ASSERT_LT(distance.numerical_value_in(km), 500000.0); //TODO: Fix: moons returning local position.
}

TEST_F(AstrodynamicsSystemTest, GetRelativePositionSunEarth)
{
    const Date date("2020-02-18 15:08:47.23847");
    AstrodynamicsSystem sunEarthSys(CelestialBodyId::SUN, { CelestialBodyId::EARTH });

    ASSERT_NO_THROW(sunEarthSys.get_relative_position(date, CelestialBodyId::EARTH, CelestialBodyId::SUN));
    const auto earthToSunRelPos = sunEarthSys.get_relative_position(date, CelestialBodyId::EARTH, CelestialBodyId::SUN);

    // Earth is roughly 150 million km from Sun (1 AU)
    const auto distance = earthToSunRelPos.norm();
    ASSERT_GT(distance.numerical_value_in(km), 140000000.0);
    ASSERT_LT(distance.numerical_value_in(km), 160000000.0);
}

TEST_F(AstrodynamicsSystemTest, BeginIterator)
{
    auto it = sys.begin();
    ASSERT_NE(it, sys.end());
}

TEST_F(AstrodynamicsSystemTest, IteratorIncrement)
{
    sys.add_body<Moon>();
    sys.add_body<Mars>();

    std::size_t count = 0;
    for (auto it = sys.begin(); it != sys.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, sys.size());
}

TEST_F(AstrodynamicsSystemTest, ConstBeginIterator)
{
    const auto& constSys = sys;
    auto it              = constSys.begin();
    ASSERT_NE(it, constSys.end());
}

TEST_F(AstrodynamicsSystemTest, ConstIteratorIncrement)
{
    sys.add_body<Moon>();
    sys.add_body<Mars>();

    const auto& constSys = sys;
    std::size_t count    = 0;
    for (auto it = constSys.begin(); it != constSys.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, constSys.size());
}

TEST_F(AstrodynamicsSystemTest, AddBodyReturnsPointer)
{
    const auto& moonPtr = sys.add_body<Moon>();
    ASSERT_NE(moonPtr, nullptr);
    ASSERT_EQ(moonPtr->get_name(), "Moon");
}

TEST_F(AstrodynamicsSystemTest, AddBodyByIdReturnsPointer)
{
    const auto& marsPtr = sys.add_body(CelestialBodyId::MARS);
    ASSERT_NE(marsPtr, nullptr);
    ASSERT_EQ(marsPtr->get_name(), "Mars");
}

TEST_F(AstrodynamicsSystemTest, GetCentralBodyId)
{
    ASSERT_EQ(sys.get_central_body_id(), CelestialBodyId::EARTH);

    AstrodynamicsSystem marsSys(CelestialBodyId::MARS, {});
    ASSERT_EQ(marsSys.get_central_body_id(), CelestialBodyId::MARS);
}

TEST_F(AstrodynamicsSystemTest, GetCenterType) { ASSERT_EQ(sys.get_center_type(), SystemCenter::CENTRAL_BODY); }

TEST_F(AstrodynamicsSystemTest, EarthMoonFactory)
{
    auto earthMoonSys = AstrodynamicsSystem::EarthMoon();

    ASSERT_EQ(earthMoonSys.get_central_body_id(), CelestialBodyId::EARTH);
    ASSERT_NO_THROW(earthMoonSys.get_body(CelestialBodyId::EARTH));
    ASSERT_NO_THROW(earthMoonSys.get_body(CelestialBodyId::MOON));
    ASSERT_EQ(earthMoonSys.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, SizeAfterMultipleAdds)
{
    ASSERT_EQ(sys.size(), 1);
    sys.add_body<Moon>();
    ASSERT_EQ(sys.size(), 2);
    sys.add_body<Mars>();
    ASSERT_EQ(sys.size(), 3);
    sys.add_body<Jupiter>();
    ASSERT_EQ(sys.size(), 4);
}

TEST_F(AstrodynamicsSystemTest, ClearEmpty)
{
    AstrodynamicsSystem emptySys;
    ASSERT_EQ(emptySys.size(), 1);
    emptySys.clear();
    ASSERT_EQ(emptySys.size(), 0);
}

TEST_F(AstrodynamicsSystemTest, AddSameBodyTwice)
{
    sys.add_body<Moon>();
    ASSERT_EQ(sys.size(), 2);
    sys.add_body<Moon>(); // Adding same body twice should not increase size
    ASSERT_EQ(sys.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, GetBodyPointer)
{
    sys.add_body<Moon>();
    const auto& moonPtr = sys.get_body(CelestialBodyId::MOON);
    ASSERT_NE(moonPtr, nullptr);
    ASSERT_EQ(moonPtr->get_name(), "Moon");
}

TEST_F(AstrodynamicsSystemTest, GetAllBodiesMultiple)
{
    sys.add_body<Moon>();
    sys.add_body<Mars>();
    sys.add_body<Jupiter>();

    const auto& allBodies = sys.get_all_bodies();
    ASSERT_EQ(allBodies.size(), 4);
    ASSERT_TRUE(allBodies.contains(CelestialBodyId::EARTH));
    ASSERT_TRUE(allBodies.contains(CelestialBodyId::MOON));
    ASSERT_TRUE(allBodies.contains(CelestialBodyId::MARS));
    ASSERT_TRUE(allBodies.contains(CelestialBodyId::JUPITER));
}

TEST_F(AstrodynamicsSystemTest, GetSystemRootSinglePlanet)
{
    AstrodynamicsSystem marsSys(CelestialBodyId::MARS, {});
    marsSys.add_body<Phobos>();
    marsSys.add_body<Deimos>();
    ASSERT_EQ(marsSys.get_system_root(), CelestialBodyId::MARS);
}

TEST_F(AstrodynamicsSystemTest, GetSystemRootMultiplePlanets)
{
    AstrodynamicsSystem multiPlanetSys(CelestialBodyId::EARTH, {});
    multiPlanetSys.add_body<Mars>();
    multiPlanetSys.add_body<Jupiter>();
    ASSERT_EQ(multiPlanetSys.get_system_root(), CelestialBodyId::SUN);
}

TEST_F(AstrodynamicsSystemTest, AddAllOuterPlanets)
{
    AstrodynamicsSystem outerSys;
    ASSERT_NO_THROW(outerSys.add_body<Jupiter>());
    ASSERT_NO_THROW(outerSys.add_body<Saturn>());
    ASSERT_NO_THROW(outerSys.add_body<Uranus>());
    ASSERT_NO_THROW(outerSys.add_body<Neptune>());
    ASSERT_EQ(outerSys.size(), 5);
}

TEST_F(AstrodynamicsSystemTest, AddAllInnerPlanets)
{
    AstrodynamicsSystem innerSys;
    ASSERT_NO_THROW(innerSys.add_body<Mercury>());
    ASSERT_NO_THROW(innerSys.add_body<Venus>());
    ASSERT_NO_THROW(innerSys.add_body<Earth>());
    ASSERT_NO_THROW(innerSys.add_body<Mars>());
    ASSERT_EQ(innerSys.size(), 4);
}

TEST_F(AstrodynamicsSystemTest, ConstructorWithMultipleSecondaryBodies)
{
    AstrodynamicsSystem multiSys(CelestialBodyId::EARTH, { CelestialBodyId::MOON, CelestialBodyId::MARS, CelestialBodyId::JUPITER });
    ASSERT_EQ(multiSys.size(), 4);
    ASSERT_NO_THROW(multiSys.get_body(CelestialBodyId::EARTH));
    ASSERT_NO_THROW(multiSys.get_body(CelestialBodyId::MOON));
    ASSERT_NO_THROW(multiSys.get_body(CelestialBodyId::MARS));
    ASSERT_NO_THROW(multiSys.get_body(CelestialBodyId::JUPITER));
}

TEST_F(AstrodynamicsSystemTest, GetNonExistentBody)
{
    ASSERT_ANY_THROW(sys.get_body(CelestialBodyId::MARS));
    sys.add_body<Mars>();
    ASSERT_NO_THROW(sys.get_body(CelestialBodyId::MARS));
}
