#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <trace/trace.hpp>

using namespace astrea;
using namespace trace;

using namespace mp_units;
using mp_units::si::unit_symbols::s;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(RiseSetUtilities, Union)
{
    RiseSetArray a({ 0 * s, 2 * s });
    RiseSetArray b({ 1 * s, 2 * s });
    RiseSetArray cExp({ 0 * s, 2 * s });

    RiseSetArray c = riseset_union(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_union(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, UnionVaried)
{
    RiseSetArray a({ 0 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp({ 0 * s, 4 * s });

    RiseSetArray c = riseset_union(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_union(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, UnionNoOverlap)
{
    RiseSetArray a({ 0 * s, 1 * s, 2 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp({ 0 * s, 4 * s });

    RiseSetArray c = riseset_union(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_union(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, UnionEmpty)
{
    RiseSetArray a({ 0 * s, 1 * s });
    RiseSetArray b;
    RiseSetArray cExp({ 0 * s, 1 * s });

    RiseSetArray c = riseset_union(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_union(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, Intersection)
{
    RiseSetArray a({ 0 * s, 2 * s });
    RiseSetArray b({ 1 * s, 2 * s });
    RiseSetArray cExp({ 1 * s, 2 * s });

    RiseSetArray c = riseset_intersection(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_intersection(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, IntersectionVaried)
{
    RiseSetArray a({ 0 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp({ 1 * s, 2 * s });

    RiseSetArray c = riseset_intersection(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_intersection(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, IntersectionNoOverlap)
{
    RiseSetArray a({ 0 * s, 1 * s, 2 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp;

    RiseSetArray c = riseset_intersection(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_intersection(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, IntersectionEmpty)
{
    RiseSetArray a({ 0 * s, 1 * s });
    RiseSetArray b;
    RiseSetArray cExp;

    RiseSetArray c = riseset_intersection(a, b);
    ASSERT_EQ(c, cExp);

    c = riseset_intersection(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, Difference)
{
    RiseSetArray a({ 0 * s, 2 * s });
    RiseSetArray b({ 1 * s, 2 * s });
    RiseSetArray cExp({ 0 * s, 1 * s });

    RiseSetArray c = riseset_difference(a, b);
    ASSERT_EQ(c, cExp);

    cExp = RiseSetArray();
    c    = riseset_difference(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, DifferenceVaried)
{
    RiseSetArray a({ 0 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp({ 0 * s, 1 * s, 2 * s, 3 * s });

    RiseSetArray c = riseset_difference(a, b);
    ASSERT_EQ(c, cExp);

    cExp = RiseSetArray({ 3 * s, 4 * s });
    c    = riseset_difference(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, DifferenceNoOverlap)
{
    RiseSetArray a({ 0 * s, 1 * s, 2 * s, 3 * s });
    RiseSetArray b({ 1 * s, 2 * s, 3 * s, 4 * s });
    RiseSetArray cExp = a;

    RiseSetArray c = riseset_difference(a, b);
    ASSERT_EQ(c, cExp);

    cExp = b;
    c    = riseset_difference(b, a);
    ASSERT_EQ(c, cExp);
}


TEST(RiseSetUtilities, DifferenceEmpty)
{
    RiseSetArray a({ 0 * s, 1 * s });
    RiseSetArray b;
    RiseSetArray cExp = a;

    RiseSetArray c = riseset_difference(a, b);
    ASSERT_EQ(c, cExp);

    cExp = b;
    c    = riseset_difference(b, a);
    ASSERT_EQ(c, cExp);
}
