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
 * have received a copy of the GNU General Public License along with Astrea. If not, see <htcgps://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <units/units.hpp>

#include <astro/time/clocks/GeocentricCoordinateTimeClock.hpp>

using namespace astrea;
using namespace astro;

class GeocentricCoordinateTimeClockTest : public testing::Test {
  public:
    GeocentricCoordinateTimeClockTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(GeocentricCoordinateTimeClockTest, FromSys)
{
    auto sys = std::chrono::system_clock::now();
    GeocentricCoordinateTime tcg;
    ASSERT_NO_THROW(tcg = GeocentricCoordinateTimeClock::from_sys(sys));
}

TEST_F(GeocentricCoordinateTimeClockTest, ToSys)
{
    GeocentricCoordinateTime tcg = GeocentricCoordinateTimeClock::now();
    ASSERT_NO_THROW(GeocentricCoordinateTimeClock::to_sys(tcg));
}

TEST_F(GeocentricCoordinateTimeClockTest, Now)
{
    auto sysNow                     = std::chrono::system_clock::now();
    GeocentricCoordinateTime tcgNow = GeocentricCoordinateTimeClock::now();
    ASSERT_GT(
        std::chrono::duration<double>(tcgNow.time_since_epoch()).count(),
        std::chrono::duration<double>(sysNow.time_since_epoch()).count()
    );
}

TEST_F(GeocentricCoordinateTimeClockTest, RoundTrip)
{
    auto sys  = std::chrono::system_clock::now();
    auto tcg  = GeocentricCoordinateTimeClock::from_sys(sys);
    auto sys2 = GeocentricCoordinateTimeClock::to_sys(tcg);
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(sys2 - sys);
    ASSERT_EQ(diff.count(), 0);
}
