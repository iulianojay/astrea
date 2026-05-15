/**
 * @file RadialInTrackCrossTrack.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the RadialInTrackCrossTrack class in the astro namespace
 * @date 2025-08-05
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

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/DynamicFrame.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Class representing the Radial, In-Track, Cross-Track (RIC) frame.
 */
template <IsFrame auto _parent_>
struct RadialInTrackCrossTrack : public DynamicFrame<RadialInTrackCrossTrack, _parent_> {

    static constexpr auto parent = _parent_; //!< The reference frame of the RIC frame.

    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    RadialInTrackCrossTrack(const RadiusVector<parent>& position, const VelocityVector<parent>& velocity) :
        DynamicFrame<RadialInTrackCrossTrack, parent>(position, velocity)
    {
    }

    RadialInTrackCrossTrack() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<parent, RadialInTrackCrossTrack> The DCM from ECI to RIC.
     */
    DirectionCosineMatrix<parent, RadialInTrackCrossTrack> get_dcm(const Date& date) const
    {
        const auto r       = get_inertial_position(date).unit();
        const auto v       = get_inertial_velocity(date).unit();
        const auto h       = r.cross(v).unit();
        const auto inTrack = (-r.cross(h)).unit();
        return DirectionCosineMatrix<parent, RadialInTrackCrossTrack>::from_vectors(r, inTrack, h);
    }
};

namespace dynamic {
template <IsFrame auto parent>
using ric = RadialInTrackCrossTrack<parent>;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea