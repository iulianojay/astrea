/**
 * @file RadialInTrackCrossTrack.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the RadialInTrackCrossTrack class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Class representing the Radial, In-Track, Cross-Track (RIC) frame.
 */
class RadialInTrackCrossTrack : public DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC> {

    friend DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>;

  public:
    RadialInTrackCrossTrack() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for RadialInTrackCrossTrack.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    RadialInTrackCrossTrack(const FrameReference* parent) :
        DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>(parent)
    {
    }

    /**
     * @brief Default destructor for RadialInTrackCrossTrack.
     */
    ~RadialInTrackCrossTrack() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<frames::earth::icrf, frames::dynamic::ric> The DCM from ECI to RIC.
     */
    DirectionCosineMatrix<frames::earth::icrf, RadialInTrackCrossTrack> get_dcm(const Date& date) const
    {
        const auto r = get_inertial_position(date).unit();
        const auto v = get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<frames::earth::icrf, RadialInTrackCrossTrack>::from_vectors(r, -r.cross(h), h);
    }

  private:
    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    RadialInTrackCrossTrack(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>(position, velocity)
    {
    }
};

namespace dynamic {
using ric = RadialInTrackCrossTrack;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea