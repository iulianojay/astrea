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

#include <algorithm>

#include <gtest/gtest.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/propagation/force_models/LegendreCache.hpp>

using namespace astrea;
using namespace astro;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(LegendreCacheTest, ConstructCacheForSupportedPlanets)
{
    ASSERT_NO_THROW(LegendreCache<planets::Mercury>());
    ASSERT_NO_THROW(LegendreCache<planets::Venus>());
    ASSERT_NO_THROW(LegendreCache<planets::Earth>());
    ASSERT_NO_THROW(LegendreCache<moons::Moon>());
    ASSERT_NO_THROW(LegendreCache<planets::Mars>());
}

TEST(LegendreCacheTest, TruncatedOrdersMatchFullCoefficientCache)
{
    const LegendreCache<planets::Earth, 4, 4> full;
    const LegendreCache<planets::Earth, 4, 0> zonal;
    const LegendreCache<planets::Earth, 4, 1> partial;
    for (std::size_t n = 0; n <= 4; ++n) {
        EXPECT_EQ(zonal.get_cosine_coefficient(n, 0), full.get_cosine_coefficient(n, 0));
        for (std::size_t m = 0; m <= std::min(n, std::size_t{ 1 }); ++m) {
            EXPECT_EQ(partial.get_cosine_coefficient(n, m), full.get_cosine_coefficient(n, m));
            EXPECT_EQ(partial.get_sine_coefficient(n, m), full.get_sine_coefficient(n, m));
        }
    }
}

TEST(LegendreCacheTest, ConstructCacheForUnsupportedPlanets)
{
    ASSERT_THROW(LegendreCache<planets::Jupiter>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<planets::Saturn>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<planets::Uranus>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<planets::Neptune>(), std::invalid_argument);
}

TEST(LegendreCacheTest, ConstructCacheForUnsupportedMoons)
{
    ASSERT_THROW(LegendreCache<moons::Io>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Europa>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Ganymede>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Callisto>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Titan>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Rhea>(), std::invalid_argument);
    ASSERT_THROW(LegendreCache<moons::Iapetus>(), std::invalid_argument);
}

TEST(LegendreCacheTest, ConstructFileNotFound)
{
    // TODO: This
}

TEST(LegendreCacheTest, ConstructFileTooShort)
{
    // TODO: This
}
