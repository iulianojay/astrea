#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>

using namespace astrea;
using namespace astro;

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
    ASSERT_EQ(sys.get_all_bodies().size(), 2);
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

TEST_F(AstrodynamicsSystemTest, Get)
{
    const auto& earth = sys.get(PlanetaryBody::EARTH);
    ASSERT_EQ(earth->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, GetAllBodies)
{
    const auto& bodies = sys.get_all_bodies();
    ASSERT_EQ(bodies.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, Iterator) { ASSERT_NO_THROW(for (auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : sys){}); }
