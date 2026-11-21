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
#include <cmath>
#include <numbers>
#include <ratio>

#include <astro/time/clocks/TerrestrialTimeClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricDynamicalTimeClock; // Forward declaration

/**
 * @brief A time point type for Barycentric Dynamical Time, using the BarycentricDynamicalTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with BarycentricDynamicalTimeClock.
 */
template <class Duration>
using BarycentricDynamicalTimePoint = std::chrono::time_point<BarycentricDynamicalTimeClock, Duration>;

/**
 * @brief A clock implementation for Barycentric Dynamical Time (TDB).
 *
 * Barycentric Dynamical Time is the independent time argument of barycentric ephemerides. It differs from Terrestrial
 * Time (TT) only by periodic terms caused by the eccentricity of Earth's orbit, the largest of which is ~1.66 ms. This
 * clock uses the two leading periodic terms, which agree with the full series to ~30 us.
 */
struct BarycentricDynamicalTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<BarycentricDynamicalTimeClock>; //!< The time point type for TDB, using BarycentricDynamicalTimeClock.

    static constexpr bool is_steady = false; //!< TDB is not a steady clock; it is anchored to TAI.

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
        const auto tt = TerrestrialTimeClock::from_sys(timePoint).time_since_epoch();
        return BarycentricDynamicalTimePoint<duration>{ tt + tdb_minus_tt(tt) };
    }

    /**
     * @brief Converts a Barycentric Dynamical Time time point to a system time point.
     *
     * The conversion route is: TDB → TT → UTC. The periodic terms are evaluated at TDB rather than TT, which changes
     * them by less than a nanosecond.
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
        const auto tdb = std::chrono::duration_cast<duration>(timePoint.time_since_epoch());
        return TerrestrialTimeClock::to_sys(TerrestrialTimeClock::time_point{ tdb - tdb_minus_tt(tdb) });
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

  private:
    /**
     * @brief Computes TDB - TT from the mean anomaly of the Earth.
     *
     * @param time Time on the TT (or TDB) scale, measured from the TerrestrialTimeClock epoch.
     * @return duration TDB - TT.
     */
    static duration tdb_minus_tt(const TerrestrialTimeClock::duration& time) noexcept
    {
        using days_d  = std::chrono::duration<rep, std::chrono::days::period>;
        const auto dt = std::chrono::duration_cast<days_d>(time - TerrestrialTimeClock::j2000.time_since_epoch());
        const auto mEarth = (357.53 + 0.9856003 * dt.count()) * (std::numbers::pi / 180.0); // Mean anomaly of the Earth in rad
        return duration{ 0.001658 * std::sin(mEarth) + 0.00001385 * std::sin(2.0 * mEarth) };
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
