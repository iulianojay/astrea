#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace waveguide;
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
    ASSERT_EQ(sys.all_bodies().size(), 2);
    ASSERT_EQ(sys.center(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, Constructor)
{
    ASSERT_NO_THROW(AstrodynamicsSystem("Moon"));
    ASSERT_NO_THROW(AstrodynamicsSystem("Moon", { "Earth", "Moon", "Sun" }));
    ASSERT_NO_THROW(AstrodynamicsSystem("Moon", { "Earth", "Moon", "Sun" }, Date("2030-01-01 00:00:00.0")));
}

TEST_F(AstrodynamicsSystemTest, Center) { ASSERT_EQ(sys.center(), "Earth"); }

TEST_F(AstrodynamicsSystemTest, GetCenter)
{
    const auto& center = sys.get_center();
    ASSERT_EQ(center->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, Get)
{
    const auto& earth = sys.get("Earth");
    ASSERT_EQ(earth->get_name(), "Earth");
}

TEST_F(AstrodynamicsSystemTest, AllBodies)
{
    const auto bodies = sys.all_bodies();
    ASSERT_EQ(bodies.size(), 2);
}

TEST_F(AstrodynamicsSystemTest, Iterator) { ASSERT_NO_THROW(for (auto& body : sys){}); }

TEST_F(AstrodynamicsSystemTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : sys){}); }
