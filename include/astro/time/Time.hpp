#pragma once

#include <chrono>

#include "JulianDateClock.hpp"

class Date;

class Time {

    friend Date;

public:
    Time(double time) : time(time) {}
    Time(JulianDateClock::duration dur) : time(dur) {}
    ~Time() {}
    
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

private:

    JulianDateClock::duration time;
};