/**
 * @file defined_rotations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for defined rotations between common frames.
 * @date 2025-10-09
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

#include <units/units.hpp>

#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/frames.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<_frame_, _frame_u_> The DCM from _frame_u_ to _frame_.
 *
 * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
 */
template <IsFrame auto _frame_, IsFrame auto _frame_u_>
    requires(_frame_::axis == axes::icrf && _frame_u_::axis == axes::j200 && has_same_origin(_frame_, _frame_u_))
inline constexpr DirectionCosineMatrix<_frame_, _frame_u_> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::rad;
    static const Angle zeta0   = -8.0561e-8 * rad;
    static const Angle eta0    = -3.3060e-8 * rad;
    static const Angle dalpha0 = 7.0783e-8 * rad;
    return DirectionCosineMatrix<_frame_, _frame_u_>::XYZ(-eta0, zeta0, dalpha0);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed> The DCM from ECI to ECEF.
 */
template <>
inline constexpr DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>
    get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>::Z(-gst);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the body-fixed frame at a given date.
 *
 * @tparam _in_frame_ The input frame type, must be ICRF and share the same origin as _out_frame_.
 * @tparam _out_frame_ The output frame type, must be FIXED_ROTATING and share the same origin as _in_frame_.
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<_in_frame_, _out_frame_> The DCM from _in_frame_ to _out_frame_.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
    requires(
        has_same_origin(_in_frame_, _out_frame_) && _in_frame_::axis == axes::icrf && _out_frame_::axis == FrameAxis::FIXED_ROTATING &&
        _in_frame_::origin != CelestialBodyId::SUN && _out_frame_::origin != CelestialBodyId::EARTH
    )
inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> get_dcm(const Date& date)
{
    static const AstrodynamicsSystem system(_out_frame_::origin);
    static const auto& body = system.get_body(_out_frame_::origin);
    const Angle gst         = date.body_sidereal_time(*body.get());
    return DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(-gst);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the Earth-Moon Synodic frame at a given date.
 *
 * The Earth-Moon Synodic frame is a fixed-rotating frame centered at the Earth-Moon barycenter, with the x-axis pointing towards the Moon.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems> The DCM from Earth ICRF to Earth-Moon Synodic frame.
 */
template <>
inline constexpr DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems> get_dcm(const Date& date)
{
    static const AstrodynamicsSystem system(CelestialBodyId::EARTH_BARYCENTER, { CelestialBodyId::EARTH, CelestialBodyId::MOON });
    const auto rEarth2Moon = system.get_relative_position(date, CelestialBodyId::EARTH, CelestialBodyId::MOON);
    const Angle lambda     = atan2(rEarth2Moon[1], rEarth2Moon[0]);
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::ems>::Z(-lambda);
}

} // namespace astro
} // namespace astrea