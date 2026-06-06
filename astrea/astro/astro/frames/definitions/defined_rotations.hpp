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

#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<frame, frame_u> The DCM from frame_u to frame.
 *
 * @ref https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA%20TP%2020220014814%20final.pdf
 */
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(equivalent(frame.axis, axes::icrf) && equivalent(frame_u.axis, axes::j2000))
inline constexpr DirectionCosineMatrix<frame, frame_u> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::rad;
    static const Angle zeta0   = -8.0561e-8 * rad;
    static const Angle eta0    = -3.3060e-8 * rad;
    static const Angle dalpha0 = 7.0783e-8 * rad;
    return DirectionCosineMatrix<frame, frame_u>::XYZ(-eta0, zeta0, dalpha0);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the body-fixed frame at a given date.
 *
 * @tparam in_frame The input frame type, must be ICRF and share the same origin as out_frame.
 * @tparam out_frame The output frame type, must be FIXED_ROTATING and share the same origin as in_frame.
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<in_frame, out_frame> The DCM from in_frame to out_frame.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(IsBodyFixedFrame<decltype(out_frame)> && equivalent(in_frame.axis, axes::icrf) && in_frame.origin != planets::Earth)
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    const Angle gst = date.body_sidereal_time<decltype(out_frame)::origin>();
    return DirectionCosineMatrix<in_frame, out_frame>::Z(-gst);
}

template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(IsSynodicFrame<decltype(out_frame)> && equivalent(in_frame.axis, axes::icrf))
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    static constexpr auto primary   = out_frame.axis.primary;
    static constexpr auto secondary = out_frame.axis.secondary;

    const auto r = get_relative_position<secondary, primary>(date).direction(); // x-axis
    const auto v = get_relative_velocity<secondary, primary>(date).direction(); // nearly the y-axis but not quite
    const auto h = r.cross(v); // z-axis, normal to the plane of motion of the secondary around the primary
    const auto y = h.cross(r); // y-axis, normal to the plane of motion and the line connecting the primary and
                               // secondary, pointing in the direction of motion of the secondary around the primary

    return DirectionCosineMatrix<in_frame, out_frame>::from_vectors(r, y, h);
}

/**
 * @brief Retrieves the direction cosine matrix representing the fixed angular offset from the parent frame to the given FixedOffsetFrame.
 */
template <IsFrame auto frame, IsFrame auto parent>
    requires(IsFixedOffsetFrame<decltype(frame)> && equivalent(frame.parent.axis, parent.axis))
inline constexpr DirectionCosineMatrix<parent, frame> get_dcm()
{
    if constexpr (HasAngularOffset<decltype(frame)>) {
        return DirectionCosineMatrix<parent, frame>::template from_euler_angles<frame.axis.sequence>(
            frame.axis.misalignment.phi, frame.axis.misalignment.theta, frame.axis.misalignment.psi
        );
    }
    else {
        return DirectionCosineMatrix<parent, frame>::identity();
    }
}

} // namespace astro
} // namespace astrea