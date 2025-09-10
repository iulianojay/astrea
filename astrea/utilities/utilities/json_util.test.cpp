#include <optional>

#include <gtest/gtest.h>

#include <utilities/utilities.hpp>

using namespace astrea;
using namespace utilities;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(JsonUtilities, CleanEntry)
{
    nlohmann::json data = R"({ "name": "\"John Doe\"" })"_json;
    ASSERT_EQ(clean_entry(data["name"]), "John Doe");
}

TEST(JsonUtilities, ExtractFromJson)
{
    nlohmann::json data = R"({"int": "1", "double": "2.0"})"_json;
    ASSERT_EQ(extract_from_json<int>(data, "int"), 1);
    ASSERT_EQ(extract_from_json<double>(data, "double"), 2.0);
    ASSERT_ANY_THROW(extract_from_json<int>(data, "absent"));
}

TEST(JsonUtilities, ExtractOptionalFromJson)
{
    nlohmann::json data = R"({"int": "1", "double": "2.0", "absent": null})"_json;
    ASSERT_EQ(extract_optional_from_json<int>(data, "int"), 1);
    ASSERT_EQ(extract_optional_from_json<double>(data, "double"), 2.0);
    ASSERT_EQ(extract_optional_from_json<int>(data, "absent"), std::nullopt);
    ASSERT_ANY_THROW(extract_optional_from_json<int>(data, "missing"));
}

TEST(JsonUtilities, ExtractStringFromJson)
{
    nlohmann::json data = R"({"name": "John Doe", "age": "30"})"_json;
    ASSERT_EQ(extract_string_from_json(data, "name"), "John Doe");
    ASSERT_EQ(extract_string_from_json(data, "age"), "30");
}

TEST(JsonUtilities, ExtractOptionalStringFromJson)
{
    nlohmann::json data = R"({"name": "John Doe", "age": "30", "absent": null})"_json;
    ASSERT_EQ(extract_optional_string_from_json(data, "name"), "John Doe");
    ASSERT_EQ(extract_optional_string_from_json(data, "age"), "30");
    ASSERT_EQ(extract_optional_string_from_json(data, "absent"), std::nullopt);
}