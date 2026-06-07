/**
 * @file TerrestrialTimeClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Terrestrial Time (TT).
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

struct TerrestrialTimeClock; // Forward declaration

/**
 * @brief A time point type for Terrestrial Time, using the TerrestrialTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with TerrestrialTimeClock.
 */
template <class Duration>
using TerrestrialDateTime = std::chrono::time_point<TerrestrialTimeClock, Duration>;

/**
 * @brief A clock implementation for Terrestrial Time (TT).
 *
 * Terrestrial Time is a continuous time scale defined by the IAU. It is related to International
 * Atomic Time (TAI) by a fixed offset: TT = TAI + 32.184 seconds. TT is commonly used in
 * astrodynamics as the independent variable for planetary motion equations.
 *
 * This clock provides conversions to and from the system clock via the TAI clock, accounting
 * for the fixed TT-TAI offset. Leap seconds are handled transparently through std::chrono::tai_clock.
 */
struct TerrestrialTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<TerrestrialTimeClock>; //!< The time point type for TT, using TerrestrialTimeClock.

    static constexpr bool is_steady = false; //!< TT is not a steady clock; it is anchored to TAI.

    /**
     * @brief The fixed offset between Terrestrial Time and International Atomic Time.
     *
     * TT = TAI + 32.184 s (as defined by the IAU).
     */
    static constexpr duration tt_tai_offset{ 32.184 };

    /**
     * @brief Converts a system time point to a Terrestrial Time time point.
     *
     * The conversion route is: UTC (sys) → TAI (via clock_cast, handling leap seconds) → TT (+ 32.184 s).
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return TerrestrialDateTime<TerrestrialTimeClock::duration> The converted TT time point.
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        auto const tai = clock_cast<tai_clock>(timePoint);
        return TerrestrialDateTime<TerrestrialTimeClock::duration>{
            duration_cast<TerrestrialTimeClock::duration>(tai.time_since_epoch()) + tt_tai_offset
        };
    }

    /**
     * @brief Converts a Terrestrial Time time point to a system time point.
     *
     * The conversion route is: TT → TAI (- 32.184 s) → UTC (via clock_cast, handling leap seconds).
     *
     * @tparam Duration The duration type of the TT time point.
     * @param timePoint The TT time point to convert.
     * @return std::chrono::sys_time<std::chrono::tai_clock::duration> The converted system time point.
     */
    template <class Duration>
    static auto to_sys(TerrestrialDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        return sys_time{ timePoint - clock_cast<TerrestrialTimeClock>(sys_days{}) };
    }

    /**
     * @brief Gets the current time point in Terrestrial Time format.
     *
     * @return TerrestrialTimeClock::time_point The current time point in TT format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for Terrestrial Time time points.
 *
 * This is a convenience type alias for TT time points using the TerrestrialTimeClock.
 */
using TerrestrialTime = TerrestrialTimeClock::time_point;

} // namespace astro
} // namespace astrea
