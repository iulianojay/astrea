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
#include <vector>

#include <astro/propagation/force_models/space_weather/file_reader.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;

namespace {
std::filesystem::path space_weather_file()
{
    return std::string(_ASTRO_ROOT_) + "/data/space_weather/SpaceWeather-All-v1.2.txt";
}
} // namespace

TEST(FileReaderTest, ThrowsForMissingFile)
{
    const std::filesystem::path missing = std::string(_ASTRO_ROOT_) + "/data/space_weather/does-not-exist.txt";
    EXPECT_THROW((void)read_space_weather_file(missing), std::runtime_error);
}

TEST(FileReaderTest, ReadsNonEmptyData)
{
    const auto data = read_space_weather_file(space_weather_file());
    EXPECT_FALSE(data.empty());
    EXPECT_GT(data.size(), 0U);
}

TEST(FileReaderTest, DateFilteringIsInclusive)
{
    const Date start("1957 10 10", "%Y %m %d");
    const Date end("1957 10 20", "%Y %m %d");

    const auto data = read_space_weather_file(space_weather_file(), start, end);
    ASSERT_FALSE(data.empty());

    for (const auto& row : data) {
        EXPECT_GE(row.date, start);
        EXPECT_LE(row.date, end);
    }

    EXPECT_EQ(data.front().date, start);
    EXPECT_EQ(data.back().date, end);
}

TEST(FileReaderTest, EarliestRecordMatchesExpectedDate)
{
    const auto data = read_space_weather_file(space_weather_file());
    ASSERT_FALSE(data.empty());
    EXPECT_EQ(data.front().date, Date("1957 10 01", "%Y %m %d"));
    EXPECT_EQ(data.front().measurement, MeasurementType::OBSERVED);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
