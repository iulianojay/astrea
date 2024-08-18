#pragma once

#ifndef SWIG

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

    // Addition operator
    Date operator+(const Time& time) {
        const auto newTime = julianDate.time_since_epoch() + time.time;
        return Date(JulianDate(newTime));
    }

    // Subtraction operator
    Time operator-(const Date& other) {
        const auto diff = other.julianDate - julianDate; 
        return Time(diff);
    }

    // Stream
    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        os << obj.calendarDate;
        return os;
    }

    // Destructor
    ~Date() {}

    // Utilities
    const auto julian_day() const {
        return julianDate.time_since_epoch().count();
    }
    const auto utc() const {
        return round<std::chrono::seconds>(clock_cast<std::chrono::system_clock>(julianDate));
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
        const auto sysTime = round<std::chrono::milliseconds>(clock_cast<std::chrono::system_clock>(julianDate));
        std::stringstream ss;
        ss << sysTime;
        calendarDate = ss.str();
    }

};

#else

struct Date {
public:
    Date(std::string date) : calendarDate(date) {};
    ~Date() {};

private:
    std::string calendarDate;
};

#endif