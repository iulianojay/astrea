/**
 * @file LocalHorizontalLocalVertical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the LocalHorizontalLocalVertical class in the astro namespace
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
 * @brief Class representing the Local Horizontal, Local Vertical (LVLH) frame.
 */
class LocalHorizontalLocalVertical : public DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH> {

    friend DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>;

  public:
    LocalHorizontalLocalVertical() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for LocalHorizontalLocalVertical.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    LocalHorizontalLocalVertical(const FrameReference* parent) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(parent)
    {
    }

    /**
     * @brief Default destructor for LocalHorizontalLocalVertical.
     */
    ~LocalHorizontalLocalVertical() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date.
     *
     * @param date The date for which the DCM is computed.
     * @return DirectionCosineMatrix<frames::primary, LocalHorizontalLocalVertical> The DCM from ECI to LVLH.
     */
    DirectionCosineMatrix<frames::primary, LocalHorizontalLocalVertical> get_dcm(const Date& date) const
    {
        const auto r               = get_inertial_position(date).unit();
        const auto v               = get_inertial_velocity(date).unit();
        const auto h               = r.cross(v).unit();
        const auto localHorizontal = ((-h).cross(-r)).unit();
        return DirectionCosineMatrix<frames::primary, LocalHorizontalLocalVertical>::from_vectors(localHorizontal, -h, -r);
    }

  private:
    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    LocalHorizontalLocalVertical(const RadiusVector<frames::primary>& position, const VelocityVector<frames::primary>& velocity) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(position, velocity)
    {
    }
};

namespace dynamic {
using lvlh = LocalHorizontalLocalVertical;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea