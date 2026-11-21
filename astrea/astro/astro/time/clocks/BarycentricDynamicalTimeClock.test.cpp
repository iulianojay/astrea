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

#include <astro/time/clocks/BarycentricDynamicalTimeClock.hpp>

using namespace astrea;
using namespace astro;

class BarycentricDynamicalTimeClockTest : public testing::Test {
  public:
    BarycentricDynamicalTimeClockTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(BarycentricDynamicalTimeClockTest, FromSys)
{
    auto sys = std::chrono::system_clock::now();
    BarycentricDynamicalTime tcg;
    ASSERT_NO_THROW(tcg = BarycentricDynamicalTimeClock::from_sys(sys));
}

TEST_F(BarycentricDynamicalTimeClockTest, ToSys)
{
    BarycentricDynamicalTime tcg = BarycentricDynamicalTimeClock::now();
    ASSERT_NO_THROW(BarycentricDynamicalTimeClock::to_sys(tcg));
}

TEST_F(BarycentricDynamicalTimeClockTest, Now)
{
    auto sysNow                     = std::chrono::system_clock::now();
    BarycentricDynamicalTime tcgNow = BarycentricDynamicalTimeClock::now();
    ASSERT_GT(
        std::chrono::duration<double>(tcgNow.time_since_epoch()).count(),
        std::chrono::duration<double>(sysNow.time_since_epoch()).count()
    );
}

TEST_F(BarycentricDynamicalTimeClockTest, RoundTrip)
{
    const auto sys = std::chrono::system_clock::now();
    std::cout << "From sys: \n";
    const auto tcg = BarycentricDynamicalTimeClock::from_sys(sys);
    std::cout << "To sys: \n";
    const auto sys2 = BarycentricDynamicalTimeClock::to_sys(tcg);
    const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(sys2 - sys);
    ASSERT_EQ(diff.count(), 0);
}

TEST_F(BarycentricDynamicalTimeClockTest, OffsetFromTTAtJ2000)
{
    // J2000.0 TT = 2000-01-01T11:58:55.816 UTC. TDB - TT = 0.001657 sin(M) + 0.00001385 sin(2M) with M = 357.53 deg.
    using namespace std::chrono;
    const std::chrono::sys_time<std::chrono::milliseconds> sys{ std::chrono::sys_days{ std::chrono::year{ 2000 } / 1 / 1 } +
                                                                11h + 58min + 55s + 816ms };
    const auto tt  = TerrestrialTimeClock::from_sys(sys).time_since_epoch();
    const auto clk = BarycentricDynamicalTimeClock::from_sys(sys).time_since_epoch();
    ASSERT_NEAR(duration<double>(clk - tt).count(), -7.26e-5, 2e-6);
    const auto sys2 = BarycentricDynamicalTimeClock::to_sys(BarycentricDynamicalTimeClock::from_sys(sys));
    ASSERT_NEAR(duration<double>(sys2 - sys).count(), 0.0, 1e-6);
}
