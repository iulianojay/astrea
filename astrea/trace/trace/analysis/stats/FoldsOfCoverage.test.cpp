#include <gtest/gtest.h>

#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/risesets/AccessArray.hpp>

using namespace astrea;
using namespace trace;

using mp_units::si::unit_symbols::s;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(FoldsOfCoverageTest, ConstructorBuildsFoldsAndStats)
{
    AccessArray accesses;
    accesses[1, 10] = RiseSetArray({ 0.0 * s, 10.0 * s, 20.0 * s, 30.0 * s });
    accesses[2, 10] = RiseSetArray({ 5.0 * s, 15.0 * s, 25.0 * s, 35.0 * s });
    accesses[3, 20] = RiseSetArray({ 0.0 * s, 5.0 * s });

    const FoldsOfCoverage folds(accesses, 5.0 * s, 40.0 * s);

    ASSERT_NO_THROW(folds.get_stats(10));
    ASSERT_NO_THROW(folds.get_stats(20));
    ASSERT_GE(folds.get_stats(10).max, 1.0);
    ASSERT_GE(folds.get_stats(10).avg, 0.0);
}

TEST(FoldsOfCoverageTest, IteratorCoverage)
{
    AccessArray accesses;
    accesses[1, 10] = RiseSetArray({ 0.0 * s, 10.0 * s });
    accesses[2, 20] = RiseSetArray({ 0.0 * s, 5.0 * s });

    const FoldsOfCoverage folds(accesses, 5.0 * s, 10.0 * s);

    std::size_t nReceivers = 0;
    for (const auto& [id, foldVec] : folds) {
        (void)id;
        (void)foldVec;
        ++nReceivers;
    }

    ASSERT_EQ(nReceivers, 2);
}

TEST(FoldsOfCoverageTest, MissingIdThrows)
{
    AccessArray accesses;
    accesses[1, 10] = RiseSetArray({ 0.0 * s, 10.0 * s });

    const FoldsOfCoverage folds(accesses, 5.0 * s, 10.0 * s);
    ASSERT_ANY_THROW(folds.get_stats(999));
}
