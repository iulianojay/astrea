/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <filesystem>
#include <stdexcept>

#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;

namespace {
std::filesystem::path space_weather_file()
{
    return std::string(_ASTRO_ROOT_) + "/data/space_weather/SpaceWeather-All-v1.2.txt";
}
} // namespace

TEST(SpaceWeatherDataTest, DefaultConstructorCreatesEmptyData)
{
    SpaceWeatherData data;
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(data.size(), 0U);
    EXPECT_TRUE(data.infile().empty());
    EXPECT_FALSE(data.startDate().has_value());
    EXPECT_FALSE(data.endDate().has_value());
}

TEST(SpaceWeatherDataTest, FileConstructorLoadsDataAndStoresMetadata)
{
    const std::filesystem::path infile = space_weather_file();
    SpaceWeatherData data(infile);

    EXPECT_FALSE(data.empty());
    EXPECT_GT(data.size(), 0U);
    EXPECT_EQ(data.infile(), infile);
    EXPECT_FALSE(data.startDate().has_value());
    EXPECT_FALSE(data.endDate().has_value());
}

TEST(SpaceWeatherDataTest, FileConstructorWithDateRangeFiltersRows)
{
    const Date start("1957 10 10", "%Y %m %d");
    const Date end("1957 10 20", "%Y %m %d");

    SpaceWeatherData data(space_weather_file(), start, end);
    ASSERT_FALSE(data.empty());

    EXPECT_TRUE(data.startDate().has_value());
    EXPECT_TRUE(data.endDate().has_value());
    EXPECT_EQ(*data.startDate(), start);
    EXPECT_EQ(*data.endDate(), end);

    for (const auto& row : data.data()) {
        EXPECT_GE(row.date, start);
        EXPECT_LE(row.date, end);
    }
}

TEST(SpaceWeatherDataTest, AtThrowsWhenOutOfRange)
{
    SpaceWeatherData data(space_weather_file());
    ASSERT_FALSE(data.empty());

    EXPECT_THROW((void)data.at(data.size()), std::out_of_range);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
