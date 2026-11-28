/**
 * @file BarycentricCoordinateTimeClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Barycentric Coordinate Time (TCB).
 * @date 2026-06-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <astro/time/clocks/BarycentricDynamicalTimeClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricCoordinateTimeClock; // Forward declaration

/**
 * @brief A time point type for Barycentric Coordinate Time, using the BarycentricCoordinateTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with BarycentricCoordinateTimeClock.
 */
template <class Duration>
using BarycentricCoordinateTimePoint = std::chrono::time_point<BarycentricCoordinateTimeClock, Duration>;

/**
 * @brief A clock implementation for Barycentric Coordinate Time (TCB).
 *
 * Barycentric Coordinate Time is the coordinate time of the Barycentric Celestial Reference System. It is related to
 * Barycentric Dynamical Time (TDB) by the linear transformation TDB = TCB - LB * (TCB - T0) + TDB0 (IAU 2006
 * Resolution B3), so it runs ahead of TDB by ~0.49 s per year.
 */
struct BarycentricCoordinateTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<BarycentricCoordinateTimeClock>; //!< The time point type for TCB, using BarycentricCoordinateTimeClock.

    static constexpr bool is_steady = false;          //!< TCB is not a steady clock; it is anchored to TAI.
    static constexpr rep Lb         = 1.550519768e-8; //!< The defining rate difference between TCB and TDB.
    static constexpr auto tdb0      = duration{ -6.55e-5 }; //!< The defining offset TDB0.

    /**
     * @brief Converts a system time point to a Barycentric Coordinate Time time point.
     *
     * The conversion route is: UTC → TT → TDB → TCB, with TCB - TDB = (LB * (TDB - T0) - TDB0) / (1 - LB).
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
        const auto tdb = BarycentricDynamicalTimeClock::from_sys(timePoint).time_since_epoch();
        return BarycentricCoordinateTimePoint<duration>{ tdb + (Lb * (tdb - TerrestrialTimeClock::t0.time_since_epoch()) - tdb0) /
                                                                   (1.0 - Lb) };
    }

    /**
     * @brief Converts a Barycentric Coordinate Time time point to a system time point.
     *
     * The conversion route is: TCB → TDB → TT → UTC, with TDB = TCB - LB * (TCB - T0) + TDB0.
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
        const auto tcb = std::chrono::duration_cast<duration>(timePoint.time_since_epoch());
        const auto tdb = tcb - Lb * (tcb - TerrestrialTimeClock::t0.time_since_epoch()) + tdb0;
        return BarycentricDynamicalTimeClock::to_sys(BarycentricDynamicalTimeClock::time_point{ tdb });
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
