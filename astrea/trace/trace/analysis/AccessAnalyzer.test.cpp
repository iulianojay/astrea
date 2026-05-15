#include <gtest/gtest.h>

#include <astro/astro.hpp>
#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class AccessAnalyzerTest : public testing::Test {
  public:
    AccessAnalyzerTest() = default;

    ViewerConstellation make_constellation()
    {
        ViewerConstellation constellation(sys, startDate, 7000.0 * km, 53.0 * deg, 1, 1, 2.0);
        Integrator integrator;
        constellation.propagate(endDate, integrator);
        return constellation;
    }

    Date startDate;
    Time resolution = 60.0 * s;
    Date endDate    = startDate + 30.0 * resolution;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(AccessAnalyzerTest, Constructor) { ASSERT_NO_THROW(AccessAnalyzer(resolution, startDate, endDate)); }

TEST_F(AccessAnalyzerTest, FindInternalAccessesWithPropagatedMultiViewerConstellation)
{
    AccessAnalyzer analyzer(resolution, startDate, endDate);
    ViewerConstellation constellation = make_constellation();

    ASSERT_EQ(constellation.size(), 1);

    const AccessArray accesses = analyzer.find_internal_accesses(constellation);
    ASSERT_GE(accesses.size(), 0);
}

TEST_F(AccessAnalyzerTest, FindAccessesWithEmptyGroundArchitectureReturnsEmpty)
{
    AccessAnalyzer analyzer(resolution, startDate, endDate);
    ViewerConstellation constellation = make_constellation();
    ASSERT_EQ(constellation.size(), 1);

    GroundArchitecture grounds(std::vector<GroundStation>{});

    const AccessArray accesses = analyzer.find_accesses(constellation, grounds, false);
    ASSERT_EQ(accesses.size(), 0);
}

TEST_F(AccessAnalyzerTest, FindAccessesWithEmptyGridReturnsEmpty)
{
    AccessAnalyzer analyzer(resolution, startDate, endDate);
    ViewerConstellation constellation = make_constellation();
    ASSERT_EQ(constellation.size(), 1);

    Grid grid;

    const AccessArray accesses = analyzer.find_accesses(constellation, grid, false);
    ASSERT_EQ(accesses.size(), 0);
}

TEST_F(AccessAnalyzerTest, IncludeInternalAccessesWithEmptyGridForPropagatedMultiViewerConstellation)
{
    AccessAnalyzer analyzer(resolution, startDate, endDate);
    ViewerConstellation constellation = make_constellation();
    ASSERT_EQ(constellation.size(), 1);

    Grid grid;

    const AccessArray accesses = analyzer.find_accesses(constellation, grid, true);
    ASSERT_GE(accesses.size(), 0);
}
