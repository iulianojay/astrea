/**
 * @file Date.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Date class for handling time in the waveguide astro library.
 * @details This class provides functionality for handling dates, including conversions to and from Julian dates,
 *          sidereal time calculations, and various clock conversions.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <sstream>
#include <string>

#include <mp-units/systems/si/chrono.h>

#include <units/units.hpp>

#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Convert a string representation of a date to a JulianDate object.
 *
 * @param epoch The date string to convert.
 * @param format The format of the date string, default is "%Y-%m-%d %H:%M:%S".
 * @return JulianDate The JulianDate representation of the input date.
 */
JulianDate epoch_to_julian_date(const std::string& epoch, const std::string format = "%Y-%m-%d %H:%M:%S");

/**
 * @brief Convert a JulianDate to a string representation.
 *
 * @param date The JulianDate to convert.
 * @param format The format of the output string, default is "%Y-%m-%d %H:%M:%S".
 * @return std::string The string representation of the JulianDate.
 */
Angle julian_date_to_siderial_time(const JulianDate& date);

/**
 * @brief Class representing a date in the waveguide astro library.
 *
 * This class provides functionality for handling dates, including conversions to and from Julian dates,
 * sidereal time calculations, and various clock conversions.
 */
class Date {

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Date& obj);

  public:
    /**
     * @brief Default constructor for Date.
     */
    Date() = default;

    /**
     * @brief Construct a Date object from a JulianDate.
     *
     * @param epoch The JulianDate to initialize the Date object.
     * @param format The format of the date string, default is "%Y-%m-%d %H:%M:%S".
     */
    Date(const std::string& epoch, const std::string& format = "%Y-%m-%d %H:%M:%S") :
        _julianDate(epoch_to_julian_date(epoch, format))
    {
    }

    /**
     * @brief Construct a Date object from a JulianDate.
     *
     * @param jdate The JulianDate to initialize the Date object.
     */
    Date(const JulianDate& jdate) :
        _julianDate(jdate)
    {
    }

    /**
     * @brief Destructor for Date.
     */
    ~Date() = default;

    /**
     * @brief Get the current date and time as a Date object.
     *
     * @return const Date The current date and time.
     */
    static const Date now() noexcept;

    /**
     * @brief Add a Time object to this Date object.
     *
     * @param time The Time object to add.
     * @return Date A new Date object representing the result of the addition.
     */
    Date operator+(const Time& time) const;

    /**
     * @brief Add a Time object to this Date object in place.
     *
     * @param time The Time object to add.
     * @return Date& A reference to this Date object after the addition.
     */
    Date& operator+=(const Time& time);

    /**
     * @brief Subtract a Time object from this Date object.
     *
     * @param time The Time object to subtract.
     * @return Date A new Date object representing the result of the subtraction.
     */
    Date operator-(const Time& time) const;

    /**
     * @brief Subtract a Time object from this Date object in place.
     *
     * @param time The Time object to subtract.
     * @return Date& A reference to this Date object after the subtraction.
     */
    Date& operator-=(const Time& time);

    /**
     * @brief Subtract another Date object from this Date object.
     *
     * @param other The Date object to subtract.
     * @return Time A Time object representing the difference between the two dates.
     */
    Time operator-(const Date& other) const;

    /**
     * @brief Compare this Date object with another Date object.
     *
     * @param other The Date object to compare with.
     * @return std::strong_ordering A strong ordering result indicating the comparison.
     */
    auto operator<=>(const Date& other) const { return _julianDate <=> other._julianDate; }

    /**
     * @brief Check if this Date object is equal to another Date object.
     *
     * @param other The Date object to compare with.
     * @return bool True if the two Date objects are equal, false otherwise.
     */
    bool operator==(const Date& other) const { return _julianDate == other._julianDate; }

    /**
     * @brief Get the Julian date representation of this Date object.
     *
     * @return JulianDate The Julian date representation of this Date object.
     */
    JulianDate jd() const { return _julianDate; }

    /**
     * @brief Get the Julian date in days since the epoch.
     *
     * @return double The Julian date in days since the epoch.
     */
    double jdn() const { return std::chrono::floor<std::chrono::days>(_julianDate).time_since_epoch().count(); }

    /**
     * @brief Get the Modified Julian Date (MJD) representation of this Date object.
     *
     * @return std::chrono::duration<double, std::ratio<86400>> The Modified Julian Date representation of this Date object.
     */
    std::chrono::duration<double, std::ratio<86400>> mjd() const { return _julianDate - MJD0; }

    /**
     * @brief Get the Date in UTC clock format.
     *
     * @return std::chrono::time_point<std::chrono::utc_clock>
     */
    std::chrono::time_point<std::chrono::utc_clock> utc() const { return in_clock<std::chrono::utc_clock>(); }

    /**
     * @brief Get the Date in GPS clock format.
     *
     * @return std::chrono::time_point<std::chrono::gps_clock>
     */
    std::chrono::time_point<std::chrono::gps_clock> gps() const { return in_clock<std::chrono::gps_clock>(); }

    /**
     * @brief Get the Date in TAI clock format.
     *
     * @return std::chrono::time_point<std::chrono::tai_clock>
     */
    std::chrono::time_point<std::chrono::tai_clock> tai() const { return in_clock<std::chrono::tai_clock>(); }

    /**
     * @brief Get the Date in TT clock format.
     *
     * @return std::chrono::time_point<std::chrono::tt_clock>
     */
    // std::chrono::time_point<std::chrono::tai_clock> tt() const
    // {
    //     // TODO: Make tt clock. Find better conversion numbers
    //     using namespace std::chrono;
    //     return in_clock<tai_clock>().time_since_epoch() + std::chrono::milliseconds{ 32184.0 };
    // }

    /**
     * @brief Get the Date in sys clock format.
     *
     * @return std::chrono::time_point<std::chrono::system_clock>
     */
    std::chrono::time_point<std::chrono::system_clock> sys() const { return in_clock<std::chrono::system_clock>(); }

    /**
     * @brief Get the epoch of this Date object as a string.
     *
     * @return std::string The epoch of this Date object formatted as a string.
     */
    std::string epoch() const;

    /**
     * @brief Get the Date in a specified clock format.
     *
     * @tparam Clock_T The clock type to convert to.
     * @return std::chrono::time_point<Clock_T> The Date in the specified clock format.
     */
    template <typename Clock_T>
    std::chrono::time_point<Clock_T> in_clock() const
    {
        using namespace std::chrono;
        return round<std::chrono::milliseconds>(clock_cast<Clock_T>(_julianDate));
    }

    /**
     * @brief Get the Greenwich Mean Sidereal Time (GMST) for this Date object.
     *
     * @return Angle The Greenwich Mean Sidereal Time for this Date object.
     */
    Angle gmst() const;

  private:
    JulianDate _julianDate; //<! Julian date representation of the Date object
};

} // namespace astro
} // namespace waveguide


/**
 * @brief Specialization of mp_units::quantity_point_like_traits for the Date class.
 *
 * This specialization provides the necessary traits for using Date with mp-units.
 */
template <>
struct mp_units::quantity_point_like_traits<waveguide::astro::Date> {
    static constexpr auto reference       = non_si::day;
    static constexpr auto point_origin    = waveguide::astro::J2K;
    static constexpr bool explicit_import = false;
    static constexpr bool explicit_export = true;
    using rep                             = long double;
    static constexpr rep to_numerical_value(waveguide::astro::Date date)
    {
        return date.jd().time_since_epoch().count();
    }
    static constexpr waveguide::astro::Date from_numerical_value(rep v)
    {
        using namespace waveguide;
        using namespace astro;
        return Date(JulianDate(JulianDateClock::duration{ v }));
    }
};