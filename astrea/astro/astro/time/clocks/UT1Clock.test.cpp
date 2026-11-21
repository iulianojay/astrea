#include <gtest/gtest.h>

#include <chrono>
#include <cmath>

#include <astro/time/Date.hpp>
#include <astro/time/clocks/UT1Clock.hpp>

using namespace astrea;
using namespace astro;

namespace {

double ut1_minus_utc_seconds(const Date& date) { return UT1Clock::ut1_minus_utc(date.sys()).count(); }

} // namespace

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(UT1ClockTest, Ut1MinusUtcMatchesValladoExample)
{
    // D. Vallado, "Fundamentals of Astrodynamics and Applications," 4th ed., Example 3-15 uses dUT1 = -0.4399619 s
    // on 2004-04-06 07:51:28.386 UTC. The tabulated value changes by about 1 ms/day.
    const Date valladoDate{ "2004-04-06 07:51:28.386", "%Y-%m-%d %H:%M:%S" };
    EXPECT_NEAR(ut1_minus_utc_seconds(valladoDate), -0.4399619, 2.0e-3);
}

TEST(UT1ClockTest, Ut1MinusUtcStepsByLeapSecond)
{
    // A leap second was inserted at the end of 2016-12-31, stepping UT1 - UTC up by 1 s while UT1 stays continuous.
    const Date beforeLeap{ "2016-12-31 23:59:00", "%Y-%m-%d %H:%M:%S" };
    const Date afterLeap{ "2017-01-01 00:01:00", "%Y-%m-%d %H:%M:%S" };
    const double beforeValue = ut1_minus_utc_seconds(beforeLeap);
    const double afterValue  = ut1_minus_utc_seconds(afterLeap);
    EXPECT_NEAR(afterValue - beforeValue, 1.0, 1.0e-2);
    EXPECT_LT(std::abs(beforeValue), 0.9);
    EXPECT_LT(std::abs(afterValue), 0.9);
}

TEST(UT1ClockTest, RoundTripThroughSystemClock)
{
    using namespace std::chrono;
    const Date date{ "2024-03-15 06:30:00", "%Y-%m-%d %H:%M:%S" };
    const sys_time<UT1Clock::duration> utc{ date.sys() };

    const auto ut1       = UT1Clock::from_sys(utc);
    const auto roundTrip = UT1Clock::to_sys(ut1);
    // Seconds since 1970 in a double resolve to ~0.2 us
    EXPECT_NEAR((roundTrip - utc).count(), 0.0, 1.0e-6);
    EXPECT_NEAR((ut1.time_since_epoch() - utc.time_since_epoch()).count(), UT1Clock::ut1_minus_utc(utc).count(), 1.0e-6);
}

TEST(UT1ClockTest, DateUt1MatchesClockCast)
{
    const Date date{ "2024-03-15 06:30:00", "%Y-%m-%d %H:%M:%S" };
    const auto offset =
        date.ut1().time_since_epoch() - std::chrono::sys_time<UT1Clock::duration>{ date.sys() }.time_since_epoch();
    EXPECT_NEAR(offset.count(), ut1_minus_utc_seconds(date), 1.0e-3);
}
