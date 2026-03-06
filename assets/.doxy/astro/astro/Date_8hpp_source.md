

# File Date.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**Date.hpp**](Date_8hpp.md)

[Go to the documentation of this file](Date_8hpp.md)


```C++

#pragma once

#include <iosfwd>
#include <string>

#include <mp-units/systems/si/chrono.h>

#include <units/units.hpp>

#include <astro/time/JulianDateClock.hpp>

namespace astrea {
namespace astro {

JulianDate epoch_to_julian_date(const std::string& epoch, const std::string format = "%Y-%m-%d %H:%M:%S");

Angle julian_date_to_sidereal_time(const JulianDate& date);

class Date {

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Date& obj);

  public:
    Date(const JulianDate& jdate = J2000) :
        _julianDate(jdate)
    {
    }

    Date(const std::string& epoch, const std::string& format = "%Y-%m-%d %H:%M:%S") :
        _julianDate(epoch_to_julian_date(epoch, format))
    {
    }

    ~Date() = default;

    static const Date now() noexcept;

    Date operator+(const Time& time) const;

    Date& operator+=(const Time& time);

    Date operator-(const Time& time) const;

    Date& operator-=(const Time& time);

    Time operator-(const Date& other) const;

    auto operator<=>(const Date& other) const
    {
        using std::chrono::floor;
        using std::chrono::milliseconds;
        return floor<milliseconds>(_julianDate) <=> floor<milliseconds>(other._julianDate);
    }

    bool operator==(const Date& other) const
    {
        using std::chrono::floor;
        using std::chrono::milliseconds;
        return floor<milliseconds>(_julianDate) == floor<milliseconds>(other._julianDate);
    }

    JulianDate jd() const { return _julianDate; }

    double jdn() const { return std::chrono::floor<std::chrono::days>(_julianDate).time_since_epoch().count(); }

    std::chrono::duration<double, std::ratio<86400>> mjd() const { return _julianDate - MJD0; }

    std::chrono::time_point<std::chrono::utc_clock> utc() const { return in_clock<std::chrono::utc_clock>(); }

    std::chrono::time_point<std::chrono::gps_clock> gps() const { return in_clock<std::chrono::gps_clock>(); }

    std::chrono::time_point<std::chrono::tai_clock> tai() const { return in_clock<std::chrono::tai_clock>(); }

    // std::chrono::time_point<std::chrono::tai_clock> tt() const
    // {
    //     // TODO: Make tt clock. Find better conversion numbers
    //     using namespace std::chrono;
    //     return in_clock<tai_clock>().time_since_epoch() + std::chrono::milliseconds{ 32184.0 };
    // }

    std::chrono::time_point<std::chrono::system_clock> sys() const { return in_clock<std::chrono::system_clock>(); }

    std::string epoch() const;

    template <typename Clock_T>
    std::chrono::time_point<Clock_T> in_clock() const
    {
        using namespace std::chrono;
        return round<std::chrono::milliseconds>(clock_cast<Clock_T>(_julianDate));
    }

    Angle gmst() const;

  private:
    JulianDate _julianDate; 
};

} // namespace astro
} // namespace astrea


template <>
struct mp_units::quantity_point_like_traits<astrea::astro::Date> {
    static constexpr auto reference       = non_si::day;
    static constexpr auto point_origin    = astrea::astro::J2K;
    static constexpr bool explicit_import = false;
    static constexpr bool explicit_export = true;
    using rep                             = long double;
    static constexpr rep to_numerical_value(astrea::astro::Date date) { return date.jd().time_since_epoch().count(); }
    static constexpr astrea::astro::Date from_numerical_value(rep v)
    {
        using namespace astrea;
        using namespace astro;
        return Date(JulianDate(JulianDateClock::duration{ v }));
    }
};
```


