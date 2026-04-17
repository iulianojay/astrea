#include <gtest/gtest.h>

#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/risesets/AccessArray.hpp>

using namespace astrea;
using namespace trace;

using mp_units::si::unit_symbols::s;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(AccessStatsTest, ConstructorBuildsReceiverLevelStats)
{
    AccessArray accesses;
    accesses[1, 100] = RiseSetArray({ 0.0 * s, 10.0 * s, 20.0 * s, 40.0 * s });
    accesses[2, 100] = RiseSetArray({ 5.0 * s, 15.0 * s, 25.0 * s, 35.0 * s });
    accesses[3, 200] = RiseSetArray({ 0.0 * s, 8.0 * s, 12.0 * s, 20.0 * s });

    const AccessStats stats(accesses);

    ASSERT_EQ(stats.get_riseset_statistics().size(), 2);
    ASSERT_NO_THROW(stats.get_riseset_statistics(100));
    ASSERT_NO_THROW(stats.get_riseset_statistics(200));

    ASSERT_NO_THROW(stats.get_access_metric(100, AccessMetric::MTTA));
    ASSERT_NO_THROW(stats.get_access_metric(100, AccessMetric::AVG_DAILY_VIS));
    ASSERT_NO_THROW(stats.get_access_statistics(AccessMetric::MTTA));
    ASSERT_NO_THROW(stats.get_hyper_statistics(RiseSetMetric::ACCESS_TIME));
}

TEST(AccessStatsTest, ToStringVectorHasExpectedLength)
{
    AccessArray accesses;
    accesses[1, 100] = RiseSetArray({ 0.0 * s, 10.0 * s, 20.0 * s, 40.0 * s });
    accesses[2, 100] = RiseSetArray({ 5.0 * s, 15.0 * s, 25.0 * s, 35.0 * s });
    accesses[3, 200] = RiseSetArray({ 0.0 * s, 8.0 * s, 12.0 * s, 20.0 * s });

    const AccessStats stats(accesses);

    const std::size_t nReceivers      = stats.get_riseset_statistics().size();
    const std::size_t nStats          = Stats<Time>::size();
    const std::size_t nHyperStats     = HyperStats<Time>::size();
    const std::size_t nRiseSetMetrics = ALL_RISE_SET_METRICS.size();
    const std::size_t nAccessMetrics  = ALL_ACCESS_METRICS.size();

    const std::size_t expectedSize = nRiseSetMetrics * nReceivers * nStats + nRiseSetMetrics * nHyperStats +
                                     nAccessMetrics * nReceivers + nAccessMetrics * nStats;

    ASSERT_EQ(stats.to_string_vector().size(), expectedSize);
}
