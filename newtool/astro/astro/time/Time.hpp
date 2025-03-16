#pragma once

#ifndef SWIG

#include <chrono>
#include <iostream>

#include <astro/time/JulianDateClock.hpp>
#include <astro/time/time_units.hpp>

#include <astro/astro.fwd.hpp>

class Time {

    friend Date;
    friend std::ostream& operator<<(std::ostream&, Time const&);

  public:
    constexpr Time()                  = default;
    constexpr Time(const Time& other) = default;
    constexpr Time(JulianDateClock::duration dur) : time(dur) {}
    constexpr ~Time() {}

    // constructor from arithmetic type
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time(const T& time) : time(double(time))
    {
    }

    // constructor from chrono::duration
    template <typename T, typename R = std::ratio<1>>
    constexpr Time(const std::chrono::duration<T, R>& dur)
    {
        time = std::chrono::duration_cast<JulianDateClock::duration>(dur);
    }

    // assignment from double
    constexpr Time& operator=(const double& t)
    {
        time = JulianDateClock::duration(t);
        return *this;
    }

    // assignment from chrono::duration
    template <typename T, typename R = std::ratio<1>>
    constexpr Time& operator=(const std::chrono::duration<T, R>& dur)
    {
        time = std::chrono::duration_cast<JulianDateClock::duration>(dur);
        return *this;
    }

    // cast to double
    constexpr operator double() const { return seconds(time).count(); }

    // Addition
    constexpr Time operator+(const Time& other) const { return time.count() + other.time.count(); }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator+(const T& other) const
    {
        return time.count() + Time(other).time.count();
    }

    constexpr Time& operator+=(const Time& other)
    {
        time += other.time;
        return *this;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator+=(const T& other)
    {
        time += Time(other).time;
        return *this;
    }

    // Subtraction
    constexpr Time operator-(const Time& other) const { return time.count() - other.time.count(); }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator-(const T& other) const
    {
        return time.count() - Time(other).time.count();
    }

    constexpr Time& operator-=(const Time& other)
    {
        time -= other.time;
        return *this;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator-=(const T& other)
    {
        time -= Time(other).time;
        return *this;
    }

    // Comparitors
    constexpr inline bool operator<(const Time& other) const { return time < other.time; }
    constexpr inline bool operator>(const Time& other) const { return time > other.time; }
    constexpr inline bool operator==(const Time& other) const { return time == other.time; }
    constexpr inline bool operator<=(const Time& other) const { return time <= other.time; }
    constexpr inline bool operator>=(const Time& other) const { return time >= other.time; }

    // Multiplication
    constexpr Time operator*(const Time& other) const { return time.count() * other.time.count(); }
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator*(const T& other) const
    {
        return time.count() * Time(other).count();
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator*=(const T& other)
    {
        time *= other;
        return *this;
    }

    // Division
    constexpr Time operator/(const Time& other) const { return time.count() / other.time.count(); }
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator/(const T& other) const
    {
        return time.count() / Time(other).count();
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    constexpr Time operator/=(const T& other)
    {
        time /= other;
        return *this;
    }

    // Forward count()
    constexpr double count() const { return time.count(); }

    template <typename T>
    constexpr double count() const
    {
        return std::chrono::duration_cast<T>(time).count();
    }

    // abs
    constexpr JulianDateClock::duration abs() { return std::chrono::abs(time); }

  private:
    JulianDateClock::duration time;
};

#else

class Time {
    friend Date;

  public:
    Time() = default;
    Time(const double& time) : time(time) {}
    ~Time(){};

  private:
    double time;
};

% template(TimeVector) std::vector<Time>;

#endif