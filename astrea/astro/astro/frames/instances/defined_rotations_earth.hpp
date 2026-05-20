/**
 * @file defined_rotations_earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Earth-specific DCM explicit specialisations.
 *
 * This file is intentionally separate from defined_rotations.hpp so that the
 * generic templates in defined_rotations.hpp can be included mid-way through
 * the include graph (e.g. via dynamic_frames.hpp) without pulling in
 * frames::earth::*, which are only complete once body_centered_inertial_frames.hpp
 * and fixed_rotating_frames.hpp have both finished.
 *
 * frames.hpp includes this file AFTER its two frame-instance headers, so by
 * the time these specialisations are compiled all earth frame types are complete.
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 */
#pragma once

#include <astro/frames/frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

// frames::earth::* must already be in scope when this header is parsed.
// This is guaranteed because frames.hpp includes the body-centred-inertial and
// fixed-rotating frame headers before it includes us.

namespace astrea {
namespace astro {

/**
 * @brief DCM from Earth ICRF (GCRF) to Earth-fixed (ECEF) frame.
 */
template <>
inline constexpr DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>
    get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>::Z(-gst);
}

/**
 * @brief Generic DCM from any Earth-centred ICRF frame to any Earth-centred body-fixed frame.
 *
 * This covers synthetic frame types produced by get_body_icrf_frame<planets::Earth>() and
 * get_body_fixed_frame<planets::Earth>() so that Geodetic<planets::Earth> works correctly
 * without requiring the exact frames::earth::icrf / frames::earth::earth_fixed types.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(
        has_same_origin(in_frame, out_frame) && has_axis(in_frame, axes::icrf) && IsFixedRotatingFrame<decltype(out_frame)> &&
        has_origin(in_frame, planets::Earth) && !is_same_frame(in_frame, frames::earth::icrf)
    )
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<in_frame, out_frame>::Z(-gst);
}

/**
 * @brief DCM from Earth ICRF to Earth-Moon Synodic (EMS) frame.
 *
 * The EMS frame is centred at the Earth–Moon barycentre with the x-axis
 * pointing towards the Moon.
 */
template <>
inline constexpr DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems_fixed>
    get_dcm<frames::earth::icrf, frames::earth::ems_fixed>(const Date& date)
{
    const auto rEarth2Moon = get_relative_position<planets::Earth, planets::Moon>(date);
    const Angle lambda     = atan2(rEarth2Moon[1], rEarth2Moon[0]);
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems_fixed>::Z(-lambda);
}

/**
 * @brief Earth-specific specialisation of get_body_icrf_frame returning the canonical Earth ICRF frame.
 *
 * Using the named frame ensures the existing get_dcm specialisations are matched
 * during frame-conversion look-ups.
 */
template <>
inline consteval auto get_body_icrf_frame<planets::Earth>()
{
    return frames::earth::icrf;
}

/**
 * @brief Earth-specific specialisation of get_body_fixed_frame returning the canonical ECEF frame.
 */
template <>
inline consteval auto get_body_fixed_frame<planets::Earth>()
{
    return frames::earth::earth_fixed;
}

} // namespace astro
} // namespace astrea
