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
 * @return DirectionCosineMatrix<Frame_T, Frame_U> The DCM from Frame_U to Frame_T.
 *
 * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
 */
template <typename Frame_T, typename Frame_U>
    requires(Frame_T::axis == FrameAxis::ICRF && Frame_U::axis == FrameAxis::J2000 && HasSameOrigin<Frame_T, Frame_U>)
inline constexpr DirectionCosineMatrix<Frame_T, Frame_U> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::rad;
    static const Angle zeta0   = -8.0561e-8 * rad;
    static const Angle eta0    = -3.3060e-8 * rad;
    static const Angle dalpha0 = 7.0783e-8 * rad;
    return DirectionCosineMatrix<Frame_T, Frame_U>::XYZ(-eta0, zeta0, dalpha0);
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
 * @tparam In_Frame_T The input frame type, must be ICRF and share the same origin as Out_Frame_T.
 * @tparam Out_Frame_T The output frame type, must be FIXED_ROTATING and share the same origin as In_Frame_T.
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The DCM from In_Frame_T to Out_Frame_T.
 */
template <typename In_Frame_T, typename Out_Frame_T>
    requires(
        HasSameOrigin<In_Frame_T, Out_Frame_T> && In_Frame_T::axis == FrameAxis::ICRF && Out_Frame_T::axis == FrameAxis::FIXED_ROTATING &&
        In_Frame_T::origin != CelestialBodyId::SUN && Out_Frame_T::origin != CelestialBodyId::EARTH
    )
inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> get_dcm(const Date& date)
{
    static const AstrodynamicsSystem system(Out_Frame_T::origin);
    static const auto& body = system.get_body(Out_Frame_T::origin);
    const Angle gst         = date.body_sidereal_time(*body.get());
    return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::Z(-gst);
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