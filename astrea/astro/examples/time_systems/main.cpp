#include <chrono>
#include <iostream>

#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::non_si::day;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea handles time by piggbacking ontop of mp-units time systems
    // combined with a modified version of Howard Hinnant's julian date clock.

    // The default Date is J2000
    const Date date;

    // But users can create Date objects from any supported clock type
    // or from calendar date strings
    Date now = Date::now();
    Date fromString{ "2024-01-01 00:00:00" }; // UTC by default
    Date fromFormattedString{ "2024-01-01 00:00:00", "%Y-%m-%d %H:%M:%S" };

    // Under the hood, the Date class stores time values as a Julian date, and
    // uses std::chrono to handle precision and duration arithmetic.
    std::cout << "Default Date (J2000): " << date << std::endl;
    std::cout << "Calendar Date: " << date.epoch() << std::endl;
    std::cout << "Julian Day Number: " << date.jdn() << std::endl;
    std::cout << "Modified Julian Date: " << date.mjd() << std::endl;
    std::cout << "GMST: " << date.gmst() << std::endl;

    // Convert to various clock types
    const auto julianDate = date.jd();
    const auto utc        = date.utc();
    const auto gps        = date.gps();
    const auto sys        = date.sys();

    // Users can also convert to other clock types manually
    auto highResClockTime = date.in_clock<std::chrono::high_resolution_clock>();

    // The Date class also seemlessly integrates with mp-units time quantities.
    std::cout << "One day after J2000: " << date + 1.0 * day << std::endl;
    std::cout << "7 seconds before J2000: " << date - 7.0 * s << std::endl;

    Date oneDayLater = date + 1.0 * day;
    std::cout << "Time between J2000 and 1 day after: " << (oneDayLater - date) << std::endl;

    return 0;
}