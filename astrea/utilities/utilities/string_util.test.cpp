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
}

TEST(StringUtilities, ReplaceAll)
{
    ASSERT_EQ(replace_all("Hello, World!", "World", "Testers"), "Hello, Testers!");
    ASSERT_EQ(replace_all("Hello, World!", "l", "1"), "He11o, Wor1d!");
    ASSERT_EQ(replace_all("Hello, World!", "7", "?"), "Hello, World!");
    ASSERT_EQ(replace_all("Hello, World!", "w", "W"), "Hello, World!");
    ASSERT_EQ(replace_all("Hello, World!", "W", "w"), "Hello, world!");
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
    ASSERT_EQ(get_type_name<std::string>(), "string");
    ASSERT_EQ(get_type_name<test::TestClass>(), "TestClass");
    ASSERT_EQ(get_type_name<test::nested::NestedClass>(), "NestedClass");
}