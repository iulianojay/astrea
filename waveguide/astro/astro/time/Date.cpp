#include <astro/time/Date.hpp>

#include <chrono>
#include <iostream>
#include <sstream>

#include <date/date.h> // NOTE: This is standard in std::chrono as of GNU 13.2
#include <mp-units/math.h>

using namespace mp_units;

namespace astro {

// Stream
std::ostream& operator<<(std::ostream& os, const Date& obj)
{
    os << obj.epoch();
    return os;
}

// Utility operators
Date Date::operator+(const Time& time) const
{
    const auto newTime = julianDate.time_since_epoch() + JulianDateClock::duration(time);
    return Date(JulianDate(newTime));
}
Date& Date::operator+=(const Time& time)
{
    const auto newTime = julianDate.time_since_epoch() + JulianDateClock::duration(time);
    julianDate         = JulianDate(newTime);
    return *this;
}
Date Date::operator-(const Time& time) const
{
    const auto newTime = julianDate.time_since_epoch() - JulianDateClock::duration(time);
    return Date(JulianDate(newTime));
}
Date& Date::operator-=(const Time& time)
{
    const auto newTime = julianDate.time_since_epoch() - JulianDateClock::duration(time);
    julianDate         = JulianDate(newTime);
    return *this;
}

Time Date::operator-(const Date& other) const
{
    const auto diff = other.julianDate - julianDate;
    return Time(diff);
}

// Conversions
std::string Date::epoch() const
{
    using namespace std::chrono;

    const auto sysTime = round<milliseconds>(clock_cast<system_clock>(julianDate));
    std::stringstream ss;
    ss << sysTime;
    return ss.str();
}

Angle Date::gmst() const { return julian_date_to_siderial_time(julianDate); }

// General conversions
JulianDate epoch_to_julian_date(const std::string& epoch, const std::string format)
{
    using namespace std::chrono;

    // Stream date string into time point
    std::istringstream epochStream{ epoch };
    sys_time<milliseconds> systemTime;
    epochStream >> date::parse(format, systemTime);

    // Convert with clock cast
    return round<milliseconds>(clock_cast<JulianDateClock>(systemTime));
}

Angle julian_date_to_siderial_time(const JulianDate& julianDate)
{
    using mp_units::angular::unit_symbols::deg;
    using mp_units::non_si::day;

    Time julianDay = julianDate.time_since_epoch().count() * day;

    // UT = (fraction of current Julian Day since 00:00:00 in days) / (body rotation rate in deg/day ratioed to Earth's)
    const Time halfDay = 0.5 * day;
    Time universalTime = (julianDay - (floor<day>(julianDay + halfDay) - halfDay));

    // Greenwich Universal Time
    Time julianDay0            = julianDay - universalTime; // julian day number on this julian date
    quantity<JulianCentury> T0 = julianDay0 - J2000.time_since_epoch().count() *
                                                  day; // TODO: This difference can be done, somehow, with mp_units mechanisms
    const Angle greenwichUniversalTime =
        (100.4606184 * one + 36000.77004 * T0 * pow<1>(one / JulianCentury) +
         0.000387933 * T0 * T0 * pow<2>(one / JulianCentury) - 2.583e-8 * T0 * T0 * T0 * pow<3>(one / JulianCentury)) *
        deg;

    // GST
    const AngularRate earthRotRate    = 3.609851887442813e+02 * deg / day;
    const Angle greenwichSiderealTime = (greenwichUniversalTime + earthRotRate * universalTime);

    return greenwichSiderealTime;
}

} // namespace astro