#include <astro/time/Date.hpp>

#include <chrono>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <date/date.h> // NOTE: This is standard in std::chrono as of GNU 13.2
#include <mp-units/math.h>

#include <astro/utilities/conversions.hpp>

using namespace mp_units;

namespace astrea {
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
    const auto newTime = _julianDate.time_since_epoch() + JulianDateClock::duration(time);
    return Date(JulianDate(newTime));
}
Date& Date::operator+=(const Time& time)
{
    const auto newTime = _julianDate.time_since_epoch() + JulianDateClock::duration(time);
    _julianDate        = JulianDate(newTime);
    return *this;
}
Date Date::operator-(const Time& time) const
{
    const auto newTime = _julianDate.time_since_epoch() - JulianDateClock::duration(time);
    return Date(JulianDate(newTime));
}
Date& Date::operator-=(const Time& time)
{
    const auto newTime = _julianDate.time_since_epoch() - JulianDateClock::duration(time);
    _julianDate        = JulianDate(newTime);
    return *this;
}

Time Date::operator-(const Date& other) const { return _julianDate - other._julianDate; }

// Conversions
std::string Date::epoch() const
{
    using namespace std::chrono;

    const auto sysTime = round<std::chrono::milliseconds>(clock_cast<system_clock>(_julianDate));
    std::stringstream ss;
    ss << sysTime;
    return ss.str();
}

Angle Date::gmst() const { return julian_date_to_siderial_time(_julianDate); }

// General conversions
JulianDate epoch_to_julian_date(const std::string& epoch, const std::string format)
{
    using namespace std::chrono;

    // Stream date string into time point
    std::istringstream epochStream{ epoch };
    sys_time<std::chrono::milliseconds> systemTime;
    epochStream >> date::parse(format, systemTime);

    // Convert with clock cast
    return round<std::chrono::milliseconds>(clock_cast<JulianDateClock>(systemTime));
}


const Date Date::now() noexcept { return JulianDateClock::now(); }


Angle julian_date_to_siderial_time(const JulianDate& _julianDate)
{
    using mp_units::angular::unit_symbols::deg;
    using mp_units::non_si::day;

    const Time julianDay = _julianDate.time_since_epoch().count() * day;

    // UT = (fraction of current Julian Day since 00:00:00 in days) / (body rotation rate in deg/day ratioed to Earth's)
    static const Time halfDay = 0.5 * day;
    const Time universalTime  = (julianDay - (floor<day>(julianDay + halfDay) - halfDay));

    // Greenwich Universal Time
    const Time julianDay0 = julianDay - universalTime; // julian day number on this julian date

    // TODO: This difference can be done, somehow, with mp_units mechanisms
    const quantity<JulianCentury> T0JulianCenturies = julianDay0 - J2000.time_since_epoch().count() * day;
    const quantity<one> T0                          = T0JulianCenturies / JulianCentury;

    const Angle greenwichUniversalTime =
        (100.4606184 * one + 36000.77005361 * T0 + 0.00038793 * T0 * T0 - 2.583e-8 * T0 * T0 * T0) * deg;

    // GST
    static const AngularRate earthRotRate = 1.002737909350795 * 360.0 * deg / day;
    const Angle greenwichSiderealTime     = sanitize_angle(greenwichUniversalTime + earthRotRate * universalTime);

    return greenwichSiderealTime;
}

} // namespace astro
} // namespace astrea