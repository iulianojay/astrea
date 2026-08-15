/**
 * @file GeocentricCoordinateTimeClock.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A clock implementation for Geocentric Coordinate Time (TCG).
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

#include <astro/time/clocks/JulianDateClock.hpp>
#include <astro/time/clocks/TerrestrialTimeClock.hpp>

namespace astrea {
namespace astro {

struct GeocentricCoordinateTimeClock; // Forward declaration

/**
 * @brief A time point type for Geocentric Coordinate Time, using the GeocentricCoordinateTimeClock.
 *
 * @tparam Duration The duration type to use for the time point. This should be a duration type that is compatible with GeocentricCoordinateTimeClock.
 */
template <class Duration>
using GeocentricCoordinateDateTime = std::chrono::time_point<GeocentricCoordinateTimeClock, Duration>;

/**
 * @brief A clock implementation for Geocentric Coordinate Time (TCG).
 *
 * Geocentric Coordinate Time is a continuous time scale defined by the IAU. It is related to Terrestrial Time (TT) by a
 * linear transformation that accounts for the relativistic effects of Earth's gravitational potential. TCG is commonly
 * used in astrodynamics for high-precision timekeeping in the vicinity of Earth.
 */
struct GeocentricCoordinateTimeClock {
    using rep      = double;        //!< The representation type, a double for sub-second precision.
    using period   = std::ratio<1>; //!< The period type, seconds.
    using duration = std::chrono::duration<rep, period>; //!< The duration type, representing time in seconds.
    using time_point = std::chrono::time_point<GeocentricCoordinateTimeClock>; //!< The time point type for TCG, using GeocentricCoordinateTimeClock.

    static constexpr bool is_steady = false; //!< TCG is not a steady clock; it is anchored to TAI.
    static constexpr rep Lg{ 6.969290134e-10 }; //!< The dimensionless constant Lg, representing the rate difference between TCG and TT
    static constexpr JulianDateClock::duration jdRef{ 2443144.5 };

    /**
     * @brief Converts a system time point to a Geocentric Coordinate Time time point.
     *
     * The conversion route is: UTC → TT → TCG
     *
     * @tparam Duration The duration type of the system time point.
     * @param timePoint The system time point to convert.
     * @return GeocentricCoordinateDateTime The converted TCG time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tt = TerrestrialTimeClock::from_sys(timePoint).time_since_epoch();
        const auto jd = JulianDateClock::from_sys(timePoint).time_since_epoch();
        return GeocentricCoordinateDateTime<duration>{ tt + Lg / (1.0 - Lg) * (jd - jdRef) };
    }

    /**
     * @brief Converts a Geocentric Coordinate Time time point to a system time point.
     *
     * The conversion route is: TCG → TAI (- 32.184 s) → UTC (via clock_cast, handling leap seconds).
     *
     * @tparam Duration The duration type of the TCG time point.
     * @param timePoint The TCG time point to convert.
     * @return std::chrono::sys_time<std::chrono::tai_clock::duration> The converted system time point.
     *
     * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
     */
    template <class Duration>
    static auto to_sys(GeocentricCoordinateDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tgcRef = GeocentricCoordinateTimeClock::from_sys(sysRef);
        const auto tt = timePoint.time_since_epoch() - Lg / (1.0 - Lg) * duration_cast<days>(timePoint - tgcRef);
        return TerrestrialTimeClock::to_sys(TerrestrialTimeClock::time_point{ TerrestrialTimeClock::duration{ tt } });
    }

    /**
     * @brief Gets the current time point in Geocentric Coordinate Time format.
     *
     * @return GeocentricCoordinateTimeClock::time_point The current time point in TCG format.
     */
    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

/**
 * @brief A type alias for Geocentric Coordinate Time time points.
 *
 * This is a convenience type alias for TCG time points using the GeocentricCoordinateTimeClock.
 */
using GeocentricCoordinateTime = GeocentricCoordinateTimeClock::time_point;

} // namespace astro
} // namespace astrea
