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
    ASSERT_NO_THROW(AstrodynamicsSystem(PlanetaryBody::MOON));
    ASSERT_NO_THROW(AstrodynamicsSystem(PlanetaryBody::MOON, { PlanetaryBody::EARTH, PlanetaryBody::SUN }));
}

TEST_F(AstrodynamicsSystemTest, Center) { ASSERT_EQ(sys.get_central_body()->get_name(), "Earth"); }

TEST_F(AstrodynamicsSystemTest, GetCenter)
{
    const auto& center = sys.get_central_body();
    ASSERT_EQ(center->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetExists)
{
    const auto& earth = sys.get(PlanetaryBody::EARTH);
    ASSERT_EQ(earth->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetDoesNotExist)
{
    ASSERT_ANY_THROW(sys.get(PlanetaryBody::MOON));
    sys.create(PlanetaryBody::MOON);
    ASSERT_NO_THROW(sys.get(PlanetaryBody::MOON));
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
    sys.create(PlanetaryBody::MOON);
    sys.create(PlanetaryBody::EARTH);
    ASSERT_EQ(sys.get_system_root(), PlanetaryBody::EARTH);
    sys.create(PlanetaryBody::SUN);
    ASSERT_EQ(sys.get_system_root(), PlanetaryBody::SUN);
    sys.create(PlanetaryBody::JUPITER);
    ASSERT_EQ(sys.get_system_root(), PlanetaryBody::SUN);
}
