#pragma once

#include <chrono>
#include <iostream>

#include "JulianDateClock.hpp"

class Date;

class Time {

    friend Date;
    friend std::ostream& operator<<(std::ostream&, Time const&);

public:
    Time(JulianDateClock::duration dur) : time(dur) {}
    ~Time() {}

    // conversion from double (constructor)
    Time(const double& time) : time(time) {}

    // conversion from double (assignment)
    Time& operator=(const double& time) { return *this; }

    // conversion to double (type-cast operator)
    operator double() { return time.count(); }
    
    // Addition
    Time operator+(const Time& other) {
        return time + other.time;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator+(const T& other) {
        return time + Time(other).time;
    }
    
    // Subtraction
    Time operator-(const Time& other) {
        return time - other.time;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator-(const T& other) {
        return time - Time(other).time;
    }
    
    // Comparitors
    bool operator<(const Time& other) {
        return time < other.time;
    }
    bool operator>(const Time& other) {
        return time > other.time;
    }
    bool operator==(const Time& other) {
        return time == other.time;
    }
    
    // Multiplication
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator*(const T& other) {
        return time*other;
    }
    
    // Division
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Time operator/(const T& other) {
        return time/other;
    }

    // Forward count()
    auto count() const { return time.count(); }

    // abs
    auto abs() { return std::chrono::abs(time); }

private:

    JulianDateClock::duration time;
};