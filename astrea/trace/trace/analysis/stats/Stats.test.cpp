#include <gtest/gtest.h>

#include <trace/analysis/stats/Stats.hpp>

using namespace astrea;
using namespace trace;

using mp_units::si::unit_symbols::s;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(StatsTest, ConstructorFromDoubleVector)
{
    const Stats<double> stats(std::vector<double>{ 1.0, 2.0, 3.0, 4.0 });

    ASSERT_DOUBLE_EQ(stats.min, 1.0);
    ASSERT_DOUBLE_EQ(stats.max, 4.0);
    ASSERT_DOUBLE_EQ(stats.avg, 2.5);
    ASSERT_EQ(stats.percentiles.size(), DEFAULT_PERCENTILES.size());
}

TEST(StatsTest, ConstructorThrowsOnEmptyVector) { ASSERT_ANY_THROW(Stats<double>(std::vector<double>{})); }

TEST(StatsTest, TimeSpecializationFromRiseSetArray)
{
    const RiseSetArray risesets({ 0.0 * s, 10.0 * s, 20.0 * s, 40.0 * s });

    const Stats<Time> accessStats(risesets, RiseSetMetric::ACCESS_TIME);
    ASSERT_EQ(accessStats.min, 10.0 * s);
    ASSERT_EQ(accessStats.max, 20.0 * s);
    ASSERT_EQ(accessStats.avg, 15.0 * s);

    const Stats<Time> gapStats(risesets, RiseSetMetric::GAP);
    ASSERT_EQ(gapStats.min, 10.0 * s);
    ASSERT_EQ(gapStats.max, 10.0 * s);
    ASSERT_EQ(gapStats.avg, 10.0 * s);
}

TEST(StatsTest, ToStringVectorHasExpectedLength)
{
    const Stats<double> stats(std::vector<double>{ 2.0, 4.0, 6.0 });
    ASSERT_EQ(stats.to_string_vector().size(), Stats<double>::size());
}
