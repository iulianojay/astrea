/**
 * @file VelocityNormalBinormal.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the VelocityNormalBinormal class in the astro namespace
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
 * @brief Class representing the Velocity, Normal, Binormal (VNB) frame.
 */
template <IsFrame auto _parent_>
struct VelocityNormalBinormal : public DynamicFrame<VelocityNormalBinormal<_parent_>, _parent_> {

    struct SelfTag : Frame<"vnb", DynamicOrigin{}, DynamicAxis{}, _parent_> {}; //!< Empty frame tag satisfying IsFrame.

    static constexpr auto parent = _parent_; //!< The reference frame of the VNB frame.

    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    VelocityNormalBinormal(const RadiusVector<parent>& position, const VelocityVector<parent>& velocity) :
        DynamicFrame<VelocityNormalBinormal<_parent_>, parent>(position, velocity)
    {
    }

    VelocityNormalBinormal() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<parent, VelocityNormalBinormal> The DCM from ECI to VNB.
     */
    DirectionCosineMatrix<parent, SelfTag{}> get_dcm(const Date& date) const
    {
        const auto r        = this->get_position(date).unit();
        const auto v        = this->get_velocity(date).unit();
        const auto h        = r.cross(v).unit();
        const auto binormal = (v.cross(h)).unit();
        return DirectionCosineMatrix<parent, SelfTag{}>::from_vectors(v, h, binormal);
    }
};

} // namespace frames
} // namespace astro
} // namespace astrea