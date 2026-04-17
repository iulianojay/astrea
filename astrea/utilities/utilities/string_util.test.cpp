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

#include <utilities/utilities.hpp>

using namespace astrea;
using namespace utilities;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(StringUtilities, Trim)
{
    ASSERT_EQ(trim("   Hello, World!   "), "Hello, World!");
    ASSERT_EQ(trim("   Hello, World!"), "Hello, World!");
    ASSERT_EQ(trim("Hello, World!   "), "Hello, World!");
    ASSERT_EQ(trim("Hello, World!"), "Hello, World!");
    ASSERT_EQ(trim("     "), "");
    ASSERT_EQ(trim("     OnlyLeadingWhiteSpace"), "OnlyLeadingWhiteSpace");
    ASSERT_EQ(trim("OnlyTrailingWhiteSpace     "), "OnlyTrailingWhiteSpace");
    ASSERT_EQ(trim("     BothLeadingAndTrailingWhiteSpace     "), "BothLeadingAndTrailingWhiteSpace");
}

TEST(StringUtilities, ReplaceAll)
{
    ASSERT_EQ(replace_all("Hello, World!", "World", "Testers"), "Hello, Testers!");
    ASSERT_EQ(replace_all("Hello, World!", "l", "1"), "He11o, Wor1d!");
    ASSERT_EQ(replace_all("Hello, World!", "7", "?"), "Hello, World!");
    ASSERT_EQ(replace_all("Hello, World!", "w", "W"), "Hello, World!");
    ASSERT_EQ(replace_all("Hello, World!", "W", "w"), "Hello, world!");
}

TEST(StringUtilities, Split)
{
    std::vector<std::string> expected = { "Hello", "World", "Testers" };
    ASSERT_EQ(split("Hello,World,Testers", ","), expected);
    ASSERT_EQ(split("Hello, World, Testers", ", "), expected);
    ASSERT_EQ(split("Hello-World-Testers", "-"), expected);
    ASSERT_EQ(split("Hello World Testers", " "), expected);
    ASSERT_EQ(split("HelloWorldTesters", ","), std::vector<std::string>{ "HelloWorldTesters" });
    ASSERT_EQ(split("", ","), std::vector<std::string>{ "" });
}

namespace test {

class TestClass {};

namespace nested {

class NestedClass {};

} // namespace nested
} // namespace test

TEST(StringUtilities, GetTypeName)
{
    ASSERT_EQ(get_type_name<int>(), "int");
    ASSERT_EQ(get_type_name<double>(), "double");
    // ASSERT_EQ(get_type_name<std::string>(), "string");
    ASSERT_EQ(get_type_name<test::TestClass>(), "TestClass");
    ASSERT_EQ(get_type_name<test::nested::NestedClass>(), "NestedClass");
}