/**
 * @file defined_rotations_earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Earth-specific DCM explicit specialisations.
 *
 * This file is intentionally separate from defined_rotations.hpp so that the
 * generic templates in defined_rotations.hpp can be included mid-way through
 * the include graph (e.g. via dynamic_frames.hpp) without pulling in
 * frames::earth::*, which are only complete once body_centered_inertial_frames.hpp
 * and body_fixed_frames.hpp have both finished.
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

#include <mp-units/systems/angular/math.h>

#include <astro/frames/frames.hpp>
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

// frames::earth::* must already be in scope when this header is parsed.
// This is guaranteed because frames.hpp includes the body-centred-inertial and
// fixed-rotating frame headers before it includes us.

namespace astrea {
namespace astro {

/**
 * @brief DCM from any Earth-centred ICRF frame (including the canonical frames::earth::icrf)
 * to any Earth-centred body-fixed frame.
 *
 * The explicit template<> specialisation was replaced with this constrained template so that
 * HasDcm<earth::icrf, earth::earth_fixed> (and similar requires-expressions) can find this
 * overload.  GCC 15 does not locate explicit template<> specialisations when checking
 * concept requires-expressions with constrained-auto NTTP arguments.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(in_frame.origin == out_frame.origin && in_frame.origin == planets::Earth && in_frame.axis == axes::icrf && IsBodyFixedFrame<decltype(out_frame)>)
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
    using mp_units::angular::atan2;

    const auto rEarth2Moon = get_relative_position<planets::Earth, moons::Moon>(date);
    const Angle lambda     = atan2(rEarth2Moon[1], rEarth2Moon[0]);
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems_fixed>::Z(-lambda);
}

} // namespace astro
} // namespace astrea
