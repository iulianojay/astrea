/**
 * @file BarycentricCoordinateTimeClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Barycentric Coordinate Time (TCB).
 * @date 2026-06-02
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
#include <numbers>
#include <ratio>

#include <astro/time/clocks/BarycentricDynamicalTimeClock.hpp>
#include <astro/time/clocks/JulianDateClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricCoordinateTimeClock; // Forward declaration

/**
 * @brief A time point type for Geocentric Coordinate Time, using the BarycentricCoordinateTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with BarycentricCoordinateTimeClock.
 */
template <class Duration>
using BarycentricCoordinateTimePoint = std::chrono::time_point<BarycentricCoordinateTimeClock, Duration>;

/**
 * @brief A clock implementation for Barycentric Coordinate Time (TCB).
 *
 * Geocentric Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a
 * linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly
 * used in astrodynamics for high-precision timekeeping in the vicinity of Earth.
 */
struct BarycentricCoordinateTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<BarycentricCoordinateTimeClock>; //!< The time point type for TCB, using BarycentricCoordinateTimeClock.

    static constexpr bool is_steady = false;          //!< TCB is not a steady clock; it is anchored to TAI.
    static constexpr rep Lb         = 1.550519768e-8; //!< The rate difference between TCB and TT, defined by the IAU.
    static constexpr auto P0        = duration{ 6.55e-5 };
    static constexpr auto jdRef     = JulianDateClock::duration{ 2443144.5 };

    /**
     * @brief Converts a system time point to a Barycentric Coordinate Time time point.
     *
     * The conversion route is: UTC → TT → TCB
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return BarycentricCoordinateTimePoint The converted TCB time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tdb = duration_cast<duration>(BarycentricDynamicalTimeClock::from_sys(timePoint).time_since_epoch());
        const auto jd  = JulianDateClock::from_sys(timePoint).time_since_epoch();
        const auto jdDiff = duration_cast<days>(jd - jdRef).count();
        return BarycentricCoordinateTimePoint{ tdb + duration{ Lb * jdDiff + P0.count() } };
    }

    /**
     * @brief Converts a Barycentric Coordinate Time time point to a system time point.
     *
     * The conversion route is: TCB → TAI (- 32.184 s) → UTC (via clock_cast, handling leap seconds).
     *
     * @tparam Duration The duration type of the TCB time point.
     * @param timePoint The TCB time point to convert.
     * @return std::chrono::sys_time<std::chrono::tai_clock::duration> The converted system time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto to_sys(BarycentricCoordinateTimePoint<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tcbRef = BarycentricCoordinateTimeClock::from_sys(sysRef);
        const auto jdDiff        = duration_cast<days>(timePoint - tcbRef).count();
        const auto tdb           = timePoint.time_since_epoch() - duration{ Lb * jdDiff + P0.count() };
        return BarycentricDynamicalTimeClock::to_sys(
            BarycentricDynamicalTimeClock::time_point{ BarycentricDynamicalTimeClock::duration{ tdb } }
        );
    }

    /**
     * @brief Gets the current time point in Barycentric Coordinate Time format.
     *
     * @return BarycentricCoordinateTimeClock::time_point The current time point in TCB format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for Barycentric Coordinate Time time points.
 *
 * This is a convenience type alias for TCB time points using the BarycentricCoordinateTimeClock.
 */
using BarycentricCoordinateTime = BarycentricCoordinateTimeClock::time_point;

} // namespace astro
} // namespace astrea
