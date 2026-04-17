#include <gtest/gtest.h>

#include <trace/analysis/stats/RiseSetStats.hpp>

using namespace astrea;
using namespace trace;

using mp_units::si::unit_symbols::s;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(RiseSetStatsTest, ConstructorBuildsAllMetrics)
{
    const RiseSetArray risesets({ 0.0 * s, 10.0 * s, 20.0 * s, 40.0 * s });
    const RiseSetStats stats(risesets);

    ASSERT_EQ(stats.at(RiseSetMetric::ACCESS_TIME).min, 10.0 * s);
    ASSERT_EQ(stats.at(RiseSetMetric::ACCESS_TIME).max, 20.0 * s);
    ASSERT_EQ(stats.at(RiseSetMetric::GAP).avg, 10.0 * s);
}

TEST(RiseSetStatsTest, ToStringVectorHasExpectedLength)
{
    const RiseSetArray risesets({ 0.0 * s, 10.0 * s, 20.0 * s, 40.0 * s });
    const RiseSetStats stats(risesets);

    ASSERT_EQ(stats.to_string_vector().size(), ALL_RISE_SET_METRICS.size() * Stats<Time>::size());
}

TEST(RiseSetStatsTest, OperatorBracketAllowsMetricMutation)
{
    RiseSetStats stats;
    stats[RiseSetMetric::ACCESS_TIME] = Stats<Time>(std::vector<Time>{ 5.0 * s, 15.0 * s });

    ASSERT_EQ(stats.at(RiseSetMetric::ACCESS_TIME).min, 5.0 * s);
    ASSERT_EQ(stats.at(RiseSetMetric::ACCESS_TIME).max, 15.0 * s);
}
