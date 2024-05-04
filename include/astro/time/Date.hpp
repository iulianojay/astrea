#pragma once

#include <string>
#include <sstream>

#include "Time.hpp"
#include "JulianDateClock.hpp"

class Date {

public:
    // Build from string
    Date(const std::string calendarDate) {
        set_julian_date_from_string(calendarDate, defaultDateFormat);
    }
    Date(const std::string calendarDate, const char* dateFormat) {
        set_julian_date_from_string(calendarDate, dateFormat);
    }

    // Build from JulianDate
    Date(const JulianDate jdate) {
        julianDate = jdate;
        set_string_from_julian_date();
    }

    // Copy assignment operator
    Date& operator=(const Date& other) {
        // Guard self assignment
        if (this == &other) {
            return *this;
        }

        calendarDate = other.calendarDate;
        julianDate = other.julianDate;
        defaultDateFormat = other.defaultDateFormat;

        return *this;
    }

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        os << obj.calendarDate;
        return os;
    }

    // Destructor
    ~Date();

    // Utilities
    const auto julian_day() {
        return julianDate.time_since_epoch();
    }
    const auto utc() {
        using namespace std::chrono;
        return round<seconds>(clock_cast<system_clock>(julianDate));
    }


private:
    std::string calendarDate;
    JulianDate julianDate;

    const char* defaultDateFormat = "%Y-%m-%d %H:%M:%S%z %Z";

    void set_julian_date_from_string(const std::string dateString, const char* dateFormat) {
        // Get system time
        std::tm timeDate = {};
        std::istringstream ss(dateString);
        ss >> std::get_time(&timeDate, dateFormat);
        const auto sysTime = std::chrono::system_clock::from_time_t(mktime(&timeDate));

        // Convert to Julian date
        julianDate = JulianDateClock::from_sys(sysTime);

        // Set calendar date
        set_string_from_julian_date();
    }

    void set_string_from_julian_date() {
        using namespace std::chrono;
        const auto sysTime = round<milliseconds>(clock_cast<system_clock>(julianDate));
        std::stringstream ss;
        ss << sysTime;
        calendarDate = ss.str();
    }

};