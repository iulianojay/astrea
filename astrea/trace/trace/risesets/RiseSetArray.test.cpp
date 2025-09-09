#include <gtest/gtest.h>
#include <trace/risesets/RiseSetArray.hpp>
#include <units/units.hpp>

using namespace astrea;
using namespace trace;

class RiseSetArrayTest : public testing::Test {
  public:
    RiseSetArrayTest() = default;
    void SetUp() override
    {
        t1   = 1.0 * mp_units::si::unit_symbols::s;
        t2   = 2.0 * mp_units::si::unit_symbols::s;
        t3   = 3.0 * mp_units::si::unit_symbols::s;
        t4   = 4.0 * mp_units::si::unit_symbols::s;
        arr1 = RiseSetArray({ t1, t2 });
        arr2 = RiseSetArray({ t3, t4 });
    }
    Time t1, t2, t3, t4;
    RiseSetArray arr1, arr2;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(RiseSetArrayTest, DefaultConstructor) { ASSERT_NO_THROW(RiseSetArray()); }

TEST_F(RiseSetArrayTest, VectorConstructor) { ASSERT_NO_THROW(RiseSetArray({ t1, t2 })); }

TEST_F(RiseSetArrayTest, CopyConstructor)
{
    RiseSetArray arrCopy(arr1);
    ASSERT_EQ(arrCopy, arr1);
}

TEST_F(RiseSetArrayTest, MoveConstructor)
{
    RiseSetArray arrMove(std::move(arr2));
    ASSERT_EQ(arrMove.size(), 2);
}

TEST_F(RiseSetArrayTest, AssignmentOperators)
{
    RiseSetArray arr;
    arr = arr1;
    ASSERT_EQ(arr, arr1);
    arr = std::move(arr1);
    ASSERT_EQ(arr.size(), 2);
}

TEST_F(RiseSetArrayTest, AppendPrependInsert)
{
    RiseSetArray arr;
    arr.append(t1, t2);
    arr.prepend(t3, t4);
    arr.insert(t1, t2);
    ASSERT_EQ(arr.size(), 4);
}

TEST_F(RiseSetArrayTest, OperatorAccess)
{
    ASSERT_EQ(arr1[0], t1);
    ASSERT_EQ(arr1[1], t2);
    const RiseSetArray arrConst(arr1);
    ASSERT_EQ(arrConst[0], t1);
}

TEST_F(RiseSetArrayTest, EqualityOperator)
{
    RiseSetArray arr(arr1);
    ASSERT_TRUE(arr == arr1);
}

TEST_F(RiseSetArrayTest, DifferenceOperators) { ASSERT_NO_THROW(arr1 - arr2); }

TEST_F(RiseSetArrayTest, UnionOperators) { ASSERT_NO_THROW(arr1 | arr2); }

TEST_F(RiseSetArrayTest, IntersectionOperators) { ASSERT_NO_THROW(arr1 & arr2); }

TEST_F(RiseSetArrayTest, GapAndAccessTime)
{
    const auto arr = arr1 | arr2;
    ASSERT_EQ(arr.gap(Stat::MIN), t3 - t2);
    ASSERT_EQ(arr.access_time(Stat::MAX), t2 - t1);
}

TEST_F(RiseSetArrayTest, Iterators)
{
    ASSERT_NO_THROW(for (auto& time : arr1){});
    ASSERT_NO_THROW(for (const auto& time : arr1){});
}

TEST_F(RiseSetArrayTest, ToStringVector) { ASSERT_NO_THROW(arr1.to_string_vector()); }
