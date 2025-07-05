#pragma once

#include <sstream>
#include <string>

#include <mp-units/systems/si/chrono.h>

#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

// General conversions
JulianDate epoch_to_julian_date(const std::string& epoch, const std::string format = "%Y-%m-%d %H:%M:%S");
Angle julian_date_to_siderial_time(const JulianDate& date);

class Date {

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Date& obj);

  public:
    // Build from string
    Date() = default;
    Date(const std::string& epoch, const std::string& format = "%Y-%m-%d %H:%M:%S") :
        _julianDate(epoch_to_julian_date(epoch, format))
    {
    }

    // Build from JulianDate
    Date(const JulianDate& jdate) :
        _julianDate(jdate)
    {
    }

    // Destructor
    ~Date() = default;

    // Static dispatch
    static const Date now() noexcept;

    // Helper operators
    Date operator+(const Time& time) const;
    Date& operator+=(const Time& time);
    Date operator-(const Time& time) const;
    Date& operator-=(const Time& time);
    Time operator-(const Date& other) const;

    // Comparitors
    auto operator<=>(const Date& other) const { return _julianDate <=> other._julianDate; }
    bool operator==(const Date& other) const { return _julianDate == other._julianDate; }

    // Clock conversions
    auto jd() const { return _julianDate; }
    auto jdn() const { return std::chrono::floor<std::chrono::days>(_julianDate).time_since_epoch().count(); }
    auto mjd() const { return _julianDate - MJD0; }
    std::chrono::time_point<std::chrono::utc_clock> utc() const { return in_clock<std::chrono::utc_clock>(); }
    std::chrono::time_point<std::chrono::gps_clock> gps() const { return in_clock<std::chrono::gps_clock>(); }
    std::chrono::time_point<std::chrono::tai_clock> tai() const { return in_clock<std::chrono::tai_clock>(); }
    // std::chrono::time_point<std::chrono::tai_clock> tt() const
    // {
    //     // TODO: Make tt clock. Find better conversion numbers
    //     using namespace std::chrono;
    //     return in_clock<tai_clock>().time_since_epoch() + milliseconds{ 32184.0 };
    // }
    std::chrono::time_point<std::chrono::system_clock> sys() const { return in_clock<std::chrono::system_clock>(); }
    std::string epoch() const;

    template <typename Clock_T>
    std::chrono::time_point<Clock_T> in_clock() const
    {
        using namespace std::chrono;
        return round<milliseconds>(clock_cast<Clock_T>(_julianDate));
    }

    // Sidereal time
    Angle gmst() const;

  private:
    JulianDate _julianDate;
};

} // namespace astro


template <>
struct mp_units::quantity_point_like_traits<astro::Date> {
    static constexpr auto reference       = non_si::day;
    static constexpr auto point_origin    = astro::J2K;
    static constexpr bool explicit_import = false;
    static constexpr bool explicit_export = true;
    using rep                             = long double;
    static constexpr rep to_numerical_value(astro::Date date) { return date.jd().time_since_epoch().count(); }
    static constexpr astro::Date from_numerical_value(rep v)
    {
        using namespace astro;
        return Date(JulianDate(JulianDateClock::duration{ v }));
    }
};