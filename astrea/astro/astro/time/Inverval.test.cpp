#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/time/Interval.hpp>

using namespace astrea;
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
