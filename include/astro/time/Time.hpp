#pragma once

#ifndef SWIG

#include <chrono>
#include <iostream>

#include "JulianDateClock.hpp"
#include "time_units.hpp"

#include "Date.fwd.hpp"

class Time {

    friend Date;
    friend std::ostream& operator<<(std::ostream&, Time const&);

public:
    Time() = default;
    Time(const Time& other) = default;
    Time(JulianDateClock::duration dur) : time(dur) {}
    ~Time() {}

    // constructor from arithmetic type
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time(const T& time) : time(double(time)) {}

    // constructor from chrono::duration
    template <typename T, typename R = std::ratio<1>>
    Time(const std::chrono::duration<T, R>& dur) {
        time = std::chrono::duration_cast<JulianDateClock::duration>(dur);
    }

    // assignment from double
    Time& operator=(const double& t) {
        time = JulianDateClock::duration(t);
        return *this;
    }

    // assignment from chrono::duration
    template <typename T, typename R = std::ratio<1>>
    Time& operator=(const std::chrono::duration<T, R>& dur) {
        time = std::chrono::duration_cast<JulianDateClock::duration>(dur);
        return *this;
    }

    // cast to double
    operator double() const { return time.count(); }

    // Addition
    Time operator+(const Time& other) const {
        return time.count() + other.time.count();
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator+(const T& other) const {
        return time.count() + Time(other).time.count();
    }

    // Subtraction
    Time operator-(const Time& other) const {
        return time.count() - other.time.count();
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator-(const T& other) const {
        return time.count() - Time(other).time.count();
    }

    // Comparitors
    inline bool operator<(const Time& other) const { return time < other.time; }
    inline bool operator>(const Time& other) const { return time > other.time; }
    inline bool operator==(const Time& other) const { return time == other.time; }
    inline bool operator<=(const Time& other) const { return time <= other.time; }
    inline bool operator>=(const Time& other) const { return time >= other.time; }

    // Multiplication
    Time operator*(const Time& other) const {
        return time.count()*other.time.count();
    }
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator*(const T& other) const {
        return time.count()*Time(other).count();
    }

    // Division
    Time operator/(const Time& other) const {
        return time.count()/other.time.count();
    }
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator/(const T& other) const {
        return time.count()/Time(other).count();
    }

    // Forward count()
    double count() const { return time.count(); }

    template <typename T>
    double count() const { return std::chrono::duration_cast<T>(time).count(); }

    // abs
    JulianDateClock::duration abs() { return std::chrono::abs(time); }


private:

    JulianDateClock::duration time;
};

#else

class Time {
    friend Date;

public:

    Time() = default;
    Time(const double& time) : time(time) {}
    ~Time() {};

private:
    double time;
};

%template(TimeVector) std::vector<Time>;

#endif