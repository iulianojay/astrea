#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyFactory.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

using namespace astrea;
using namespace astro;
using namespace planetary_bodies;

class CelestialBodyFactoryTest : public testing::Test {
  public:
    CelestialBodyFactoryTest() {}

    void SetUp() override { factory.clear(); }

    CelestialBodyFactory factory;
    AstrodynamicsSystem sys;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CelestialBodyFactoryTest, Create)
{
    ASSERT_EQ(factory.size(), 0);
    ASSERT_NO_THROW(factory.create<Earth>(sys));
    ASSERT_EQ(factory.size(), 1);
    factory.create<Earth>(sys);
    ASSERT_EQ(factory.size(), 1);
}

TEST_F(CelestialBodyFactoryTest, Get)
{
    ASSERT_ANY_THROW(factory.get(PlanetaryBody::EARTH));
    factory.create(PlanetaryBody::EARTH, sys);
    ASSERT_NO_THROW(factory.get(PlanetaryBody::EARTH));
}

TEST_F(CelestialBodyFactoryTest, GetOrCreate)
{
    ASSERT_EQ(factory.size(), 0);
    ASSERT_NO_THROW(factory.get_or_create(PlanetaryBody::EARTH, sys));
    ASSERT_EQ(factory.size(), 1);
    ASSERT_NO_THROW(factory.get(PlanetaryBody::EARTH));
}

TEST_F(CelestialBodyFactoryTest, Clear)
{
    ASSERT_EQ(factory.size(), 0);
    factory.create<Earth>(sys);
    ASSERT_EQ(factory.size(), 1);
    factory.clear();
    ASSERT_EQ(factory.size(), 0);
}

TEST_F(CelestialBodyFactoryTest, PropagateBodies) {}

// TEST_F(CelestialBodyFactoryTest, GetRoot) // TODO: Move to astro system
// {
//     factory.create("Moon", sys);
//     factory.create(PlanetaryBody::EARTH, sys);
//     ASSERT_EQ(factory.get_root(), PlanetaryBody::EARTH);
//     factory.create("Sun", sys);
//     ASSERT_EQ(factory.get_root(), "Sun");
//     factory.create("Jupiter", sys);
//     ASSERT_EQ(factory.get_root(), "Sun");
// }

TEST_F(CelestialBodyFactoryTest, Iterator) { ASSERT_NO_THROW(for (auto& body : factory){}); }

TEST_F(CelestialBodyFactoryTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : factory){}); }
