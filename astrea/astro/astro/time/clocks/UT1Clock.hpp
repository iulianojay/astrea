/**
 * @file UT1Clock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Clock implementation for Universal Time (UT1).
 * @date 2026-11-20
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <chrono>
#include <ratio>

namespace astrea {
namespace astro {

struct UT1Clock; // Forward declaration

/**
 * @brief A time point type for Universal Time, using the UT1Clock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with UT1Clock.
 */
template <class Duration>
using UniversalDateTime = std::chrono::time_point<UT1Clock, Duration>;

/**
 * @brief A clock implementation for Universal Time (UT1).
 *
 * UT1 is the time scale defined by Earth's rotation angle, and is the argument of sidereal time. It departs from UTC by
 * the measured UT1 - UTC (kept within +/-0.9 s by leap seconds), taken from the Earth Orientation Parameters.
 *
 * Time points count seconds since 1970-01-01 00:00:00 on the UT1 scale, sharing the system clock epoch so that a UT1
 * time point read on the system clock epoch gives the Julian date on the UT1 scale.
 */
struct UT1Clock {
    using rep        = double;        //!< The representation type, a double for sub-second precision.
    using period     = std::ratio<1>; //!< The period type, seconds.
    using duration   = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<UT1Clock>;  //!< The time point type for UT1, using UT1Clock.

    static constexpr bool is_steady = false; //!< UT1 follows Earth's irregular rotation.

    /**
     * @brief Get UT1 - UTC at a given UTC instant.
     *
     * TAI - UT1 is interpolated from the Earth Orientation Parameters rather than UT1 - UTC since it is continuous
     * across leap seconds. TAI - UTC comes from the leap-second table.
     *
     * @param utc The UTC instant.
     * @return duration UT1 - UTC at the given instant.
     *
     * @note Instants outside the range of available Earth Orientation Parameters data use the nearest tabulated TAI - UT1.
     * @note TAI - UTC is only exact from 1972 onward, when UTC adopted integer leap seconds.
     */
    static duration ut1_minus_utc(const std::chrono::sys_time<duration>& utc);

    /**
     * @brief Converts a system time point to a UT1 time point.
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return UniversalDateTime<UT1Clock::duration> The converted UT1 time point.
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto utc = time_point_cast<UT1Clock::duration>(timePoint);
        return UniversalDateTime<UT1Clock::duration>{ utc.time_since_epoch() + ut1_minus_utc(utc) };
    }

    /**
     * @brief Converts a UT1 time point to a system time point.
     *
     * UT1 - UTC is a function of UTC, so it is evaluated at an estimate of UTC and refined once. UT1 - UTC changes by
     * a few milliseconds per day, so a single refinement is exact to well below a nanosecond.
     *
     * @tparam Duration The duration type of the UT1 time point.
     * @param timePoint The UT1 time point to convert.
     * @return std::chrono::sys_time<UT1Clock::duration> The converted system time point.
     */
    template <class Duration>
    static auto to_sys(UniversalDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const sys_time<UT1Clock::duration> ut1{ duration_cast<UT1Clock::duration>(timePoint.time_since_epoch()) };
        const auto utcEstimate = ut1 - ut1_minus_utc(ut1);
        return ut1 - ut1_minus_utc(utcEstimate);
    }

    /**
     * @brief Gets the current time point in UT1 format.
     *
     * @return UT1Clock::time_point The current time point in UT1 format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for UT1 time points.
 *
 * This is a convenience type alias for UT1 time points using the UT1Clock.
 */
using UniversalTime = UT1Clock::time_point;

} // namespace astro
} // namespace astrea
