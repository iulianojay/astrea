#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astro;

class IntervalTest : public testing::Test {
  public:
    IntervalTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(IntervalTest, None) {}
