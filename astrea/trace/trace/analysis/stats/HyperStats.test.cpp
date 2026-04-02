#include <gtest/gtest.h>

#include <trace/analysis/stats/HyperStats.hpp>

using namespace astrea;
using namespace trace;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(HyperStatsTest, ConstructorAggregatesStats)
{
    const Stats<double> s1(std::vector<double>{ 1.0, 2.0, 3.0 });
    const Stats<double> s2(std::vector<double>{ 4.0, 5.0, 6.0 });

    const HyperStats<double> hyper(std::vector<Stats<double>>{ s1, s2 });

    ASSERT_DOUBLE_EQ(hyper.min.min, 1.0);
    ASSERT_DOUBLE_EQ(hyper.min.max, 4.0);
    ASSERT_DOUBLE_EQ(hyper.min.avg, 2.5);

    ASSERT_DOUBLE_EQ(hyper.max.min, 3.0);
    ASSERT_DOUBLE_EQ(hyper.max.max, 6.0);
    ASSERT_DOUBLE_EQ(hyper.max.avg, 4.5);
    ASSERT_EQ(hyper.percentiles.size(), DEFAULT_PERCENTILES.size());
}

TEST(HyperStatsTest, ToStringVectorHasExpectedLength)
{
    const Stats<double> s1(std::vector<double>{ 1.0, 2.0, 3.0 });
    const Stats<double> s2(std::vector<double>{ 4.0, 5.0, 6.0 });
    const HyperStats<double> hyper(std::vector<Stats<double>>{ s1, s2 });

    ASSERT_EQ(hyper.to_string_vector().size(), HyperStats<double>::size());
}
