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
 * have received a copy of the GNU General Public License along with Astrea. If not, see <htcgps://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <units/units.hpp>

#include <astro/time/clocks/BarycentricCoordinateTimeClock.hpp>

using namespace astrea;
using namespace astro;

class BarycentricCoordinateTimeClockTest : public testing::Test {
  public:
    BarycentricCoordinateTimeClockTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(BarycentricCoordinateTimeClockTest, FromSys)
{
    auto sys = std::chrono::system_clock::now();
    BarycentricCoordinateTime tcg;
    ASSERT_NO_THROW(tcg = BarycentricCoordinateTimeClock::from_sys(sys));
}

TEST_F(BarycentricCoordinateTimeClockTest, ToSys)
{
    BarycentricCoordinateTime tcg = BarycentricCoordinateTimeClock::now();
    ASSERT_NO_THROW(BarycentricCoordinateTimeClock::to_sys(tcg));
}

TEST_F(BarycentricCoordinateTimeClockTest, Now)
{
    auto sysNow                      = std::chrono::system_clock::now();
    BarycentricCoordinateTime tcgNow = BarycentricCoordinateTimeClock::now();
    ASSERT_GT(
        std::chrono::duration<double>(tcgNow.time_since_epoch()).count(),
        std::chrono::duration<double>(sysNow.time_since_epoch()).count()
    );
}

TEST_F(BarycentricCoordinateTimeClockTest, RoundTrip)
{
    const auto sys = std::chrono::system_clock::now();
    std::cout << "From sys: \n";
    const auto tcg = BarycentricCoordinateTimeClock::from_sys(sys);
    std::cout << "To sys: \n";
    const auto sys2 = BarycentricCoordinateTimeClock::to_sys(tcg);
    const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(sys2 - sys);
    ASSERT_EQ(diff.count(), 0);
}
