#include <gtest/gtest.h>

#include <trace/analysis/PositionCache.hpp>

using namespace astrea;
using namespace trace;

using mp_units::si::unit_symbols::km;

class PositionCacheTest : public testing::Test {
  public:
    PositionCacheTest() = default;

    EcefRadiusVec r1{ 1.0 * km, 2.0 * km, 3.0 * km };
    EcefRadiusVec r2{ 4.0 * km, 5.0 * km, 6.0 * km };
    EcefRadiusVec r3{ 7.0 * km, 8.0 * km, 9.0 * km };
    EcefRadiusVec r4{ 10.0 * km, 11.0 * km, 12.0 * km };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(PositionCacheTest, DefaultState)
{
    PositionCache cache;
    ASSERT_EQ(cache.n_platforms(), 0);
    ASSERT_EQ(cache.n_timesteps(), 0);
}

TEST_F(PositionCacheTest, AddSetGetByIdAndIndex)
{
    PositionCache cache;
    cache.reserve(2);

    const std::size_t idxA = cache.add_platform(1001, 2);
    const std::size_t idxB = cache.add_platform(1002, 2);

    cache.set_position(idxA, 0, r1);
    cache.set_position(idxA, 1, r2);
    cache.set_position(idxB, 0, r3);
    cache.set_position(idxB, 1, r4);

    ASSERT_EQ(idxA, 0);
    ASSERT_EQ(idxB, 1);
    ASSERT_EQ(cache.n_platforms(), 2);
    ASSERT_EQ(cache.n_timesteps(), 2);

    ASSERT_EQ(cache.get_index(1001), idxA);
    ASSERT_EQ(cache.get_index(1002), idxB);
    ASSERT_EQ(cache.get_platform_id(idxA), 1001);
    ASSERT_EQ(cache.get_platform_id(idxB), 1002);

    ASSERT_EQ(cache.get_position_by_id(1001, 0), r1);
    ASSERT_EQ(cache.get_position_by_id(1001, 1), r2);
    ASSERT_EQ(cache.get_position_by_index(idxB, 0), r3);
    ASSERT_EQ(cache.get_position_by_index(idxB, 1), r4);
}

TEST_F(PositionCacheTest, SingleTimestepBehavesAsFixedPosition)
{
    PositionCache cache;
    const std::size_t idx = cache.add_platform(42, 1);
    cache.set_position(idx, 0, r1);

    ASSERT_EQ(cache.get_position_by_id(42, 0), r1);
    ASSERT_EQ(cache.get_position_by_id(42, 99), r1);
    ASSERT_EQ(cache.get_position_by_index(idx, 123), r1);
}

TEST_F(PositionCacheTest, ClearRemovesData)
{
    PositionCache cache;
    const std::size_t idx = cache.add_platform(777, 1);
    cache.set_position(idx, 0, r1);

    cache.clear();

    ASSERT_EQ(cache.n_platforms(), 0);
    ASSERT_EQ(cache.n_timesteps(), 0);
    ASSERT_ANY_THROW(cache.get_index(777));
}
