#include <astro/astro.hpp>
#include <gtest/gtest.h>
#include <trace/platforms/ground/Grid.hpp>
#include <trace/platforms/ground/GroundPoint.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

class GridTest : public testing::Test {
  public:
    GridTest() = default;

    void SetUp() override
    {
        Angle lat1 = 0.0 * mp_units::angular::unit_symbols::deg;
        Angle lon1 = 0.0 * mp_units::angular::unit_symbols::deg;
        Angle lat4 = 10.0 * mp_units::angular::unit_symbols::deg;
        Angle lon4 = 10.0 * mp_units::angular::unit_symbols::deg;

        corner1 = { lat1, lon1 };
        corner4 = { lat4, lon4 };

        spacing = 5.0 * mp_units::angular::unit_symbols::deg;
        weight  = 0.0 * mp_units::one;

        parent         = sys.get("Earth").get();
        grid           = Grid(parent, corner1, corner4, GridType::UNIFORM, spacing, weight);
        groundStations = { GroundPoint(parent, lat1, lon1, 0.0 * mp_units::si::unit_symbols::km),
                           GroundPoint(parent, lat4, lon4, 0.0 * mp_units::si::unit_symbols::km) };
    }

    AstrodynamicsSystem sys;
    const CelestialBody* parent;

    Angle spacing;
    LatLon corner1;
    LatLon corner4;
    Unitless weight;

    std::vector<GroundPoint> groundStations;

    Grid grid;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GridTest, DefaultConstructor) { ASSERT_NO_THROW(Grid()); }

TEST_F(GridTest, ManualConstructor)
{
    Grid manualGrid(groundStations);
    for (std::size_t ii = 0; ii < groundStations.size(); ++ii) {
        ASSERT_EQ(manualGrid[ii], groundStations[ii]);
    }
}

TEST_F(GridTest, TypedConstructors)
{
    ASSERT_NO_THROW(Grid(parent, corner1, corner4, GridType::UNIFORM, spacing, weight));
    ASSERT_ANY_THROW(Grid(parent, corner1, corner4, GridType::EQUAL_AREA, spacing, weight));  // Not implemented
    ASSERT_ANY_THROW(Grid(parent, corner1, corner4, GridType::WEIGHTED_NS, spacing, weight)); // Not implemented
    ASSERT_ANY_THROW(Grid(parent, corner1, corner4, GridType::WEIGHTED_EW, spacing, weight)); // Not implemented
}

TEST_F(GridTest, Iterators)
{
    ASSERT_NO_THROW(for (auto& point : grid){});
    ASSERT_NO_THROW(for (const auto& point : grid){});
}
