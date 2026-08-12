/**
 * @file BarycentricDynamicalTimeClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Barycentric Dynamical Time (TDB).
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
#include <numbers>
#include <ratio>

#include <astro/time/clocks/JulianDateClock.hpp>
#include <astro/time/clocks/TerrestrialTimeClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricDynamicalTimeClock; // Forward declaration

/**
 * @brief A time point type for Geocentric Coordinate Time, using the BarycentricDynamicalTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with BarycentricDynamicalTimeClock.
 */
template <class Duration>
using BarycentricDynamicalTimePoint = std::chrono::time_point<BarycentricDynamicalTimeClock, Duration>;

/**
 * @brief A clock implementation for Barycentric Dynamical Time (TDB).
 *
 * Geocentric Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a
 * linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly
 * used in astrodynamics for high-precision timekeeping in the vicinity of Earth.
 */
struct BarycentricDynamicalTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<BarycentricDynamicalTimeClock>; //!< The time point type for TDB, using BarycentricDynamicalTimeClock.

    static constexpr bool is_steady = false; //!< TDB is not a steady clock; it is anchored to TAI.
    static constexpr auto jdRef     = JulianDateClock::duration{ 2451545.0 };

    /**
     * @brief Converts a system time point to a Barycentric Dynamical Time time point.
     *
     * The conversion route is: UTC → TT → TDB
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return BarycentricDynamicalTimePoint The converted TDB time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tt     = duration_cast<duration>(TerrestrialTimeClock::from_sys(timePoint).time_since_epoch());
        const auto jd     = JulianDateClock::from_sys(timePoint).time_since_epoch();
        const auto jdDiff = duration_cast<days>(jd - jdRef).count();
        const auto Me = (357.53 + 0.9856003 * jdDiff) * (std::numbers::pi / 180.0); // Mean anomaly of the Earth in rad
        return BarycentricDynamicalTimePoint<duration>{ tt + duration{ 0.001658 * std::sin(Me) + 0.00001385 * std::sin(2 * Me) } };
    }

    /**
     * @brief Converts a Barycentric Dynamical Time time point to a system time point.
     *
     * The conversion route is: TDB → TAI (- 32.184 s) → UTC (via clock_cast, handling leap seconds).
     *
     * @tparam Duration The duration type of the TDB time point.
     * @param timePoint The TDB time point to convert.
     * @return std::chrono::sys_time<std::chrono::tai_clock::duration> The converted system time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto to_sys(BarycentricDynamicalTimePoint<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tbdRef = BarycentricDynamicalTimeClock::from_sys(sysRef);
        const auto Me = (357.53 + 0.9856003 * duration_cast<days>(timePoint - tbdRef).count()) * (std::numbers::pi / 180.0); // Mean anomaly of the Earth in rad
        const auto tt = timePoint.time_since_epoch() - duration{ 0.001658 * std::sin(Me) + 0.00001385 * std::sin(2 * Me) };
        return TerrestrialTimeClock::to_sys(TerrestrialTimeClock::time_point{ TerrestrialTimeClock::duration{ tt } });
    }

    /**
     * @brief Gets the current time point in Barycentric Dynamical Time format.
     *
     * @return BarycentricDynamicalTimeClock::time_point The current time point in TDB format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for Barycentric Dynamical Time time points.
 *
 * This is a convenience type alias for TDB time points using the BarycentricDynamicalTimeClock.
 */
using BarycentricDynamicalTime = BarycentricDynamicalTimeClock::time_point;

} // namespace astro
} // namespace astrea
