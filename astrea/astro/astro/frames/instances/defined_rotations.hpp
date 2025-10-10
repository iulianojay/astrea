/**
 * @file defined_rotations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for defined rotations between common frames.
 * @version 0.1
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

#include <astro/frames/frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<Frame_T, Frame_U> The DCM from Frame_U to Frame_T.
 */
template <typename Frame_T, typename Frame_U>
    requires(Frame_T::get_axis() == FrameAxis::J2000 && Frame_U::get_axis() == FrameAxis::ICRF && HasSameOrigin<Frame_T, Frame_U>)
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::deg;
    static const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    return DCM<Frame_T, Frame_U>::X(obliquity);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed> The DCM from ECI to ECEF.
 */
template <>
inline DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>
    get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>::Z(gst);
}

} // namespace astro
} // namespace astrea