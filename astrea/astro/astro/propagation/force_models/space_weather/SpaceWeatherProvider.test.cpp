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
#include <memory>
#include <type_traits>

#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>
#include <astro/propagation/force_models/space_weather/SpaceWeatherProvider.hpp>

using namespace astrea;
using namespace astro;

static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<SpaceWeatherProvider::DataPtr>())>>, "SpaceWeatherProvider::DataPtr must point to const SpaceWeatherData");

namespace {
std::filesystem::path space_weather_file()
{
    return std::string(_ASTRO_ROOT_) + "/data/space_weather/SpaceWeather-All-v1.2.txt";
}
} // namespace

TEST(SpaceWeatherProviderTest, DefaultConstructorIsEmpty)
{
    SpaceWeatherProvider provider;
    EXPECT_TRUE(provider.empty());
    EXPECT_EQ(provider.size(), 0U);
    EXPECT_EQ(provider.data(), nullptr);
}

TEST(SpaceWeatherProviderTest, ConstructFromSharedPointerPreservesIdentity)
{
    auto snapshot = std::make_shared<const SpaceWeatherData>(space_weather_file());
    SpaceWeatherProvider provider(snapshot);

    EXPECT_FALSE(provider.empty());
    EXPECT_EQ(provider.data(), snapshot);
    EXPECT_EQ(provider.size(), snapshot->size());
}

TEST(SpaceWeatherProviderTest, ConstructFromValueCreatesSnapshot)
{
    SpaceWeatherData data(space_weather_file());
    SpaceWeatherProvider provider(std::move(data));

    ASSERT_NE(provider.data(), nullptr);
    EXPECT_FALSE(provider.empty());
    EXPECT_GT(provider.size(), 0U);
}

TEST(SpaceWeatherProviderTest, InPlaceConstructorBuildsSnapshot)
{
    SpaceWeatherProvider provider(std::in_place, space_weather_file());

    ASSERT_NE(provider.data(), nullptr);
    EXPECT_FALSE(provider.empty());
    EXPECT_GT(provider.size(), 0U);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
