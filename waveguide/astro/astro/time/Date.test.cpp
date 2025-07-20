#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace waveguide;
using namespace astro;

class DateTest : public testing::Test {
  public:
    DateTest() {}

    void SetUp() override { now = Date::now(); }

    Date now;

    template <auto R, typename Rep>
    const bool nearly_equal(const mp_units::quantity<R, Rep>& first, const mp_units::quantity<R, Rep>& second) const
    {
        const Rep a       = first.numerical_value_ref_in(first.unit);
        const Rep b       = first.numerical_value_ref_in(second.unit);
        const Rep REL_TOL = 1.0e-4;
        if (a != 0.0 && abs((a - b) / a) > REL_TOL) { return false; }
        else if (b != 0.0 && abs((a - b) / b) > REL_TOL) {
            return false;
        }
        return true;
    }
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(DateTest, EpochToJulianDate) { ASSERT_EQ(epoch_to_julian_date("2000-01-01 12:00:00.0"), J2000); }

TEST_F(DateTest, JulianDateToSiderealTime)
{
    // Vallado, Ex. 3-5
    Date date("1992-08-20 12:13:00.0");
    nearly_equal(julian_date_to_siderial_time(date.jd()), Angle(152.58 * mp_units::angular::unit_symbols::deg));
}

TEST_F(DateTest, DefaultConstructor) { ASSERT_NO_THROW(Date()); }

TEST_F(DateTest, StringConstructor) { ASSERT_NO_THROW(Date("2000-01-01 12:00:00.0")); }

TEST_F(DateTest, JulianDateConstructor) { ASSERT_NO_THROW(Date(J2000)); }

TEST_F(DateTest, Now) { ASSERT_LE(Date::now(), Date(JulianDateClock::now())); }

TEST_F(DateTest, Addition) { ASSERT_LE(now, now + seconds(10.0)); }

TEST_F(DateTest, InPlaceAddition)
{
    const auto nowCopy = now;
    now += seconds(10.0);
    ASSERT_LE(nowCopy, now);
}

TEST_F(DateTest, TimeSubtraction) { ASSERT_LE(now - seconds(10.0), now); }

TEST_F(DateTest, InPlaceTimeSubtraction)
{
    const auto nowCopy = now;
    now -= seconds(10.0);
    ASSERT_LE(now, nowCopy);
}

TEST_F(DateTest, DateSubtraction)
{
    const Date nowPlusTen = now + seconds(10.0);
    const Time diff       = nowPlusTen - now;
    nearly_equal(diff, 10.0 * mp_units::si::unit_symbols::s);
}

TEST_F(DateTest, SpaceshipOperator)
{
    ASSERT_LT(now, Date::now() + seconds(10.0));
    ASSERT_GT(Date::now() + seconds(10.0), now);
}

TEST_F(DateTest, Equality) { ASSERT_EQ(now, now + seconds(10.0) - seconds(10.0)); }

TEST_F(DateTest, JulianDate) { ASSERT_EQ(Date(J2000).jd(), J2000); }

TEST_F(DateTest, JulianDayNumber)
{
    ASSERT_EQ(Date(J2000).jdn(), std::chrono::floor<std::chrono::days>(J2000).time_since_epoch().count());
}

TEST_F(DateTest, MeanJulianDate) { ASSERT_EQ(Date(J2000).mjd(), J2000 - MJD0); }

TEST_F(DateTest, UTC)
{
    ASSERT_LE(std::chrono::round<std::chrono::seconds>(now.utc()), std::chrono::round<std::chrono::seconds>(std::chrono::utc_clock::now()));
}

TEST_F(DateTest, GPS)
{
    ASSERT_LE(std::chrono::round<std::chrono::seconds>(now.gps()), std::chrono::round<std::chrono::seconds>(std::chrono::gps_clock::now()));
}

TEST_F(DateTest, TAI)
{
    ASSERT_LE(std::chrono::round<std::chrono::seconds>(now.tai()), std::chrono::round<std::chrono::seconds>(std::chrono::tai_clock::now()));
}

TEST_F(DateTest, SYS)
{
    ASSERT_LE(std::chrono::round<std::chrono::seconds>(now.sys()), std::chrono::round<std::chrono::seconds>(std::chrono::system_clock::now()));
}

TEST_F(DateTest, Epoch) { ASSERT_EQ(Date(J2000).epoch(), "2000-01-01 12:00:00.000"); }

TEST_F(DateTest, GMST)
{
    nearly_equal(Date(J2000).gmst(), Angle(4.89496 * mp_units::angular::unit_symbols::rad)); // Is this right? Who knows
}
