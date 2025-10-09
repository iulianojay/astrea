/*
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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/time/JulianDateClock.hpp>

using namespace astrea;
using namespace astro;

class JulianDateClockTest : public testing::Test {
  public:
    JulianDateClockTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(JulianDateClockTest, FromSys)
{
    auto now = std::chrono::system_clock::now();
    JulianDate jd;
    ASSERT_NO_THROW(jd = JulianDateClock::from_sys(now));
}

TEST_F(JulianDateClockTest, ToSys)
{
    JulianDate jd = JulianDateClock::now();
    ASSERT_NO_THROW(JulianDateClock::to_sys(jd));
}

TEST_F(JulianDateClockTest, Now)
{
    auto sysNow      = std::chrono::system_clock::now();
    JulianDate jdNow = JulianDateClock::now();
    ASSERT_LE(
        std::chrono::duration<double>(sysNow.time_since_epoch()).count(),
        std::chrono::duration<double>(jdNow.time_since_epoch()).count()
    );
}