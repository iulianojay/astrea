/**
 * @file JulianDateClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Julian Dates. Adapted from https://stackoverflow.com/questions/33964461/handling-julian-days-in-c11-14.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <chrono>

#include <mp-units/systems/si/chrono.h>

namespace waveguide {
namespace astro {

struct JulianDateClock; // Forward declaration

/**
 * @brief A time point type for Julian Dates, using the JulianDateClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with JulianDateClock.
 */
template <class Duration>
using JulianDateTime = std::chrono::time_point<JulianDateClock, Duration>;

/**
 * @brief A clock implementation for Julian Dates.
 *
 * This clock is used to represent time points in Julian Date format, which is commonly used in astronomy.
 * It provides conversions to and from system clocks and supports arithmetic operations on Julian Dates.
 */
struct JulianDateClock {
    using rep    = double; //<! The representation type for the Julian Date, typically a double for fractional days.
    using period = std::chrono::days::period;            //<! The period type for the Julian Date, typically days.
    using duration = std::chrono::duration<rep, period>; //<! The duration type for the Julian Date, representing the time in days.
    using time_point = std::chrono::time_point<JulianDateClock>; //<! The time point type for the Julian Date, using the JulianDateClock.

    static constexpr bool is_steady =
        false; //!< Indicates that the clock is not steady, meaning it can be adjusted or may have leap seconds.

    /**
     * @brief Converts a system time point to a Julian Date time point.
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return JulianDateTime<Duration> The converted Julian Date time point.
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std;
        using namespace chrono;
        auto constexpr epoch = sys_days{ November / 24 / -4713 } + 12h;
        using ddays          = std::chrono::duration<long double, std::chrono::days::period>;
        if constexpr (sys_time<ddays>{ sys_time<Duration>::min() } < sys_time<ddays>{ epoch }) {
            return JulianDateTime{ timePoint - epoch };
        }
        else {
            // Duration overflows at the epoch.  Sub in new Duration that won't overflow.
            using D = std::chrono::duration<int64_t, ratio<1, 10'000'000>>;
            return JulianDateTime{ round<D>(timePoint) - epoch };
        }
    }

    /**
     * @brief Converts a Julian Date time point to a system time point.
     *
     * @tparam Duration The duration type of the Julian Date time point.
     * @param timePoint The Julian Date time point to convert.
     * @return std::chrono::sys_time<Duration> The converted system time point.
     */
    template <class Duration>
    static auto to_sys(JulianDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        return sys_time{ timePoint - clock_cast<JulianDateClock>(sys_days{}) };
    }

    /**
     * @brief Gets the current time point in Julian Date format.
     *
     * @return JulianDateClock::time_point The current time point in Julian Date format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for Julian Date time points.
 *
 * This is a convenience type alias for Julian Date time points using the JulianDateClock.
 */
using JulianDate = JulianDateClock::time_point;

/**
 * @brief A constant representing the J2000 epoch in Julian Date format.
 *
 * This is a commonly used epoch in astronomy, representing January 1, 2000, at 12:00 TT.
 */
static constexpr JulianDate J2000(JulianDateClock::duration{ 2451545.0 });

/**
 * @brief A constant representing the J2000 epoch in Julian Date format, used as a reference point.
 *
 * This is the same as J2000 but is defined for clarity in contexts where a reference point is needed.
 */
static constexpr mp_units::quantity_point J2K = J2000;

/**
 * @brief A constant representing the Modified Julian Date epoch in Julian Date format.
 *
 * This is used as a reference point for Modified Julian Dates.
 */
static constexpr JulianDate MJD0(JulianDateClock::duration{ 2400000.5 });

/**
 * @brief A constant representing the start of the Modified Julian Date epoch.
 *
 * This is used as a reference point for Modified Julian Dates.
 */
static constexpr mp_units::quantity_point MJDStart = MJD0;

} // namespace astro
} // namespace waveguide