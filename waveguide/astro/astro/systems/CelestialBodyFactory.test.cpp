#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astro;

class CelestialBodyFactoryTest : public testing::Test {
  public:
    CelestialBodyFactoryTest() {}

    void SetUp() override { factory.clear(); }

    CelestialBodyFactory factory;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CelestialBodyFactoryTest, Create)
{
    ASSERT_EQ(factory.size(), 0);
    ASSERT_NO_THROW(factory.create("Earth"));
    ASSERT_EQ(factory.size(), 1);
    factory.create("Earth");
    ASSERT_EQ(factory.size(), 1);
}

TEST_F(CelestialBodyFactoryTest, Get)
{
    ASSERT_ANY_THROW(factory.get("Earth"));
    factory.create("Earth");
    ASSERT_NO_THROW(factory.get("Earth"));
}

TEST_F(CelestialBodyFactoryTest, GetOrCreate)
{
    ASSERT_EQ(factory.size(), 0);
    ASSERT_NO_THROW(factory.get_or_create("Earth"));
    ASSERT_EQ(factory.size(), 1);
    ASSERT_NO_THROW(factory.get("Earth"));
}

TEST_F(CelestialBodyFactoryTest, Clear)
{
    ASSERT_EQ(factory.size(), 0);
    factory.create("Earth");
    ASSERT_EQ(factory.size(), 1);
    factory.clear();
    ASSERT_EQ(factory.size(), 0);
}

TEST_F(CelestialBodyFactoryTest, PropagateBodies) {}

TEST_F(CelestialBodyFactoryTest, GetRoot)
{
    factory.create("Moon");
    factory.create("Earth");
    ASSERT_EQ(factory.get_root(), "Earth");
    factory.create("Sun");
    ASSERT_EQ(factory.get_root(), "Sun");
    factory.create("Jupiter");
    ASSERT_EQ(factory.get_root(), "Sun");
}

TEST_F(CelestialBodyFactoryTest, Iterator) { ASSERT_NO_THROW(for (auto& body : factory){}); }

TEST_F(CelestialBodyFactoryTest, ConstIterator) { ASSERT_NO_THROW(for (const auto& body : factory){}); }
