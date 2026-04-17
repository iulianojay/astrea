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
    nlohmann::json data = R"({"int": "1", "double": "2.0", "absent": null})"_json;
    ASSERT_EQ(extract_from_json<int>(data, "int"), 1);
    ASSERT_EQ(extract_from_json<double>(data, "double"), 2.0);
    ASSERT_ANY_THROW(extract_from_json<int>(data, "absent"));
    ASSERT_ANY_THROW(extract_from_json<int>(data, "missing"));
}

TEST(JsonUtilities, ExtractOptionalFromJson)
{
    nlohmann::json data = R"({"int": "1", "double": "2.0", "absent": null})"_json;
    ASSERT_EQ(extract_optional_from_json<int>(data, "int"), 1);
    ASSERT_EQ(extract_optional_from_json<double>(data, "double"), 2.0);
    ASSERT_EQ(extract_optional_from_json<int>(data, "absent"), std::nullopt);
    ASSERT_EQ(extract_optional_from_json<int>(data, "missing"), std::nullopt);
}

TEST(JsonUtilities, ExtractStringFromJson)
{
    nlohmann::json data = R"({"name": "John Doe", "age": "30", "absent": null})"_json;
    ASSERT_EQ(extract_string_from_json(data, "name"), "John Doe");
    ASSERT_EQ(extract_string_from_json(data, "age"), "30");
    ASSERT_ANY_THROW(extract_string_from_json(data, "absent"));
    ASSERT_ANY_THROW(extract_string_from_json(data, "missing"));
}

TEST(JsonUtilities, ExtractOptionalStringFromJson)
{
    nlohmann::json data = R"({"name": "John Doe", "age": "30", "absent": null})"_json;
    ASSERT_EQ(extract_optional_string_from_json(data, "name"), "John Doe");
    ASSERT_EQ(extract_optional_string_from_json(data, "age"), "30");
    ASSERT_EQ(extract_optional_string_from_json(data, "absent"), std::nullopt);
    ASSERT_EQ(extract_optional_string_from_json(data, "missing"), std::nullopt);
}