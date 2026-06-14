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

#include <units/units.hpp>

#include <astro/time/clocks/TerrestrialTimeClock.hpp>

using namespace astrea;
using namespace astro;

class TerrestrialTimeClockTest : public testing::Test {
  public:
    TerrestrialTimeClockTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(TerrestrialTimeClockTest, FromSys)
{
    auto sys = std::chrono::system_clock::now();
    TerrestrialTime tt;
    ASSERT_NO_THROW(tt = TerrestrialTimeClock::from_sys(sys));
}

TEST_F(TerrestrialTimeClockTest, ToSys)
{
    TerrestrialTime tt = TerrestrialTimeClock::now();
    ASSERT_NO_THROW(TerrestrialTimeClock::to_sys(tt));
}

TEST_F(TerrestrialTimeClockTest, Now)
{
    auto sysNow           = std::chrono::system_clock::now();
    TerrestrialTime ttNow = TerrestrialTimeClock::now();
    // TT runs ahead of UTC (by TAI offset + 32.184 s), so TT time_since_epoch > sys time_since_epoch
    ASSERT_GT(
        std::chrono::duration<double>(ttNow.time_since_epoch()).count(),
        std::chrono::duration<double>(sysNow.time_since_epoch()).count()
    );
}

TEST_F(TerrestrialTimeClockTest, RoundTrip)
{
    auto sys  = std::chrono::system_clock::now();
    auto tt   = TerrestrialTimeClock::from_sys(sys);
    auto sys2 = TerrestrialTimeClock::to_sys(tt);
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(sys2 - sys);
    ASSERT_EQ(diff.count(), 0);
}

TEST_F(TerrestrialTimeClockTest, TTTAIOffset)
{
    // TT = TAI + 32.184 s (IAU definition)
    auto sys = std::chrono::system_clock::now();
    auto tt  = TerrestrialTimeClock::from_sys(sys);
    auto tai = std::chrono::clock_cast<std::chrono::tai_clock>(sys);

    const double tt_secs  = std::chrono::duration<double>(tt.time_since_epoch()).count();
    const double tai_secs = std::chrono::duration<double>(tai.time_since_epoch()).count();

    ASSERT_NEAR(tt_secs - tai_secs, TerrestrialTimeClock::tt_tai_offset.count(), 1e-3);
}
