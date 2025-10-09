/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>
#include <trace/risesets/AccessArray.hpp>
#include <units/units.hpp>

using namespace astrea;
using namespace trace;

class AccessArrayTest : public testing::Test {
  public:
    AccessArrayTest() = default;
    void SetUp() override
    {
        t1 = 1.0 * mp_units::si::unit_symbols::s;
        t2 = 2.0 * mp_units::si::unit_symbols::s;
        t3 = 3.0 * mp_units::si::unit_symbols::s;
        t4 = 4.0 * mp_units::si::unit_symbols::s;

        arr1 = RiseSetArray({ t1, t2 });
        arr2 = RiseSetArray({ t3, t4 });

        senderId   = 1;
        receiverId = 2;

        access1[senderId, receiverId] = arr1;
        access2[receiverId, senderId] = arr1;
    }
    Time t1, t2, t3, t4;
    RiseSetArray arr1, arr2;
    std::size_t senderId, receiverId;
    AccessArray access1;
    AccessArray access2;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(AccessArrayTest, DefaultConstructor)
{
    AccessArray arr;
    ASSERT_EQ(arr.size(), 0);
}

TEST_F(AccessArrayTest, OperatorAccess)
{
    ASSERT_EQ((access1[senderId, receiverId]), arr1);
    ASSERT_EQ(access1.at(senderId, receiverId), arr1);
}

TEST_F(AccessArrayTest, AtMethod) { ASSERT_EQ(access1.at(senderId, receiverId), arr1); }

TEST_F(AccessArrayTest, ContainsMethod)
{
    IdPair idPair(senderId, receiverId);
    ASSERT_TRUE(access1.contains(idPair));
}

TEST_F(AccessArrayTest, EraseMethod)
{
    access1.erase(senderId, receiverId);
    ASSERT_FALSE(access1.contains(IdPair(senderId, receiverId)));
}

TEST_F(AccessArrayTest, SizeMethod) { ASSERT_EQ(access1.size(), 1); }

TEST_F(AccessArrayTest, UnionOperator)
{
    const auto res = access1 | access2;
    ASSERT_EQ(res.size(), access1.size());
    ASSERT_NO_THROW(static_cast<const AccessArray&>(access1) | access2);
}

TEST_F(AccessArrayTest, IntersectionOperator)
{
    const auto res = access1 & access2;
    ASSERT_EQ(res.size(), access1.size());
    ASSERT_NO_THROW(static_cast<const AccessArray&>(access1) & access2);
}

TEST_F(AccessArrayTest, Iterators)
{
    ASSERT_NO_THROW(for (auto& access : access1){});
    ASSERT_NO_THROW(for (const auto& access : access1){});
}

TEST_F(AccessArrayTest, Stream)
{
    std::stringstream ss;
    ss << access1;
    ASSERT_FALSE(ss.str().empty());
}
