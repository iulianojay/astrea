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
#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Frame tag type for VelocityNormalBinormal, defined outside the class to allow use as a DynamicFrame NTTP.
 */
template <IsFrame auto _parent_>
struct VnbTag : Frame<"vnb", DynamicOrigin{}, DynamicAxis{}, _parent_> {
    VelocityNormalBinormal<_parent_> instantaneous(const RadiusVector<_parent_>& r, const VelocityVector<_parent_>& v) const
    {
        return VelocityNormalBinormal<_parent_>(r, v);
    }
};

template <IsFrame auto _parent_>
inline constexpr VnbTag<_parent_> vnb_tag{};

/**
 * @brief Class representing the Velocity, Normal, Binormal (VNB) frame.
 */
template <IsFrame auto _parent_>
struct VelocityNormalBinormal : public DynamicFrame<VelocityNormalBinormal<_parent_>, _parent_, vnb_tag<_parent_>> {

    using tag_type = VnbTag<_parent_>;       //!< Tag type for this frame.
    static inline constexpr tag_type tag{};  //!< Empty frame tag satisfying IsFrame.
    static constexpr auto parent = _parent_; //!< The reference frame of the VNB frame.

    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the parent frame.
     * @param velocity The velocity vector in the parent frame.
     */
    VelocityNormalBinormal(const RadiusVector<parent>& position, const VelocityVector<parent>& velocity) :
        DynamicFrame<VelocityNormalBinormal<_parent_>, parent, vnb_tag<_parent_>>(position, velocity)
    {
    }

    VelocityNormalBinormal() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<parent, VelocityNormalBinormal> The DCM from parent to VNB.
     */
    DirectionCosineMatrix<parent, tag> get_dcm(const Date& date) const
    {
        const auto r        = this->get_position(date).direction();
        const auto v        = this->get_velocity(date).direction();
        const auto h        = r.cross(v).direction();
        const auto binormal = (v.cross(h)).direction();
        return DirectionCosineMatrix<parent, tag>::from_vectors(v, h, binormal);
    }
};


} // namespace frames
} // namespace astro
} // namespace astrea