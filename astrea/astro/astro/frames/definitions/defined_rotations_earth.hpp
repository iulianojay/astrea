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

#include <type_traits>

#include <mp-units/systems/angular/math.h>

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

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
 * @brief DCM from any Earth-centred ICRF frame to the Earth-Moon Synodic (EMS) frame.
 *
 * Identified by: in_frame centred on Earth with ICRF axes, out_frame with a
 * SynodicAxis<Earth,Moon> axis (i.e. the ems frame).  Using a constrained
 * template rather than an explicit specialisation avoids naming
 * frames::earth::icrf / frames::earth::ems at declaration time, which
 * would fail when this header is reached via a circular include chain before
 * body_centered_inertial_frames.hpp has finished.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(
        in_frame.origin == planets::Earth && in_frame.axis == axes::icrf &&
        std::is_same_v<std::decay_t<decltype(out_frame.axis)>, SynodicAxis<planets::Earth, moons::Moon>>
    )
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    using mp_units::angular::atan2;

    const auto rEarth2Moon = get_relative_position<planets::Earth, moons::Moon>(date);
    const Angle lambda     = atan2(rEarth2Moon[1], rEarth2Moon[0]);
    return DirectionCosineMatrix<in_frame, out_frame>::Z(-lambda);
}

} // namespace astro
} // namespace astrea
