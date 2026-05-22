/**
 * @file DynamicFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DynamicFrame class in the astro namespace
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

#include <string>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all dynamic state/frames.
 */
template <typename Self, IsFrame auto _parent_, IsFrame auto _self_>
struct DynamicFrame {
  protected:
    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param name The name of the dynamic frame.
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    DynamicFrame(const RadiusVector<_parent_>& position, const VelocityVector<_parent_>& velocity) :
        _position(position),
        _velocity(velocity)
    {
    }

  public:
    static constexpr auto parent = _parent_; //!< The reference frame of the dynamic frame.

    /**
     * @brief Rotates a CartesianVector from Earth-Centered Inertial (ECI) to _parent_ coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, _parent_> The rotated CartesianVector in _parent_ coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, _self_> rotate_into_this_frame(const CartesianVector<Value_T, parent>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    /**
     * @brief Rotates a CartesianVector from _parent_ coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in _parent_ coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, self> The rotated CartesianVector in ECI coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, parent> rotate_out_of_this_frame(const CartesianVector<Value_T, _self_>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to _parent_ coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<self> The converted CartesianVector in _parent_ coordinates.
     */
    RadiusVector<_self_> transform_to_this_frame(const RadiusVector<parent>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * (vec - get_position(date));
    }

    /**
     * @brief Converts a CartesianVector from _parent_ coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in _parent_ coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<parent> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<parent> transform_from_this_frame(const RadiusVector<_self_>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec + get_position(date);
    }

  private:
    /**
     * @brief Get the direction cosine matrix (DCM) from Earth-Centered Inertial (ECI) to _parent_ coordinates.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<parent, Self> The DCM from ECI to _parent_ coordinates.
     */
    DirectionCosineMatrix<parent, _self_> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Self*>(this)->get_dcm(date);
    }

    RadiusVector<parent> get_center_offset(const Date& date) const { return get_position(date); }

  protected:
    RadiusVector<parent> _position;   //!< The position vector
    VelocityVector<parent> _velocity; //!< The velocity vector

    /**
     * @brief Gets the inertial position vector at a given date.
     *
     * @param date The date for which the position is requested.
     * @return RadiusVector<parent> The inertial position vector.
     */
    RadiusVector<parent> get_position(const Date& date) const { return _position; }

    /**
     * @brief Gets the inertial velocity vector at a given date.
     *
     * @param date The date for which the velocity is requested.
     * @return VelocityVector<parent> The inertial velocity vector.
     */
    VelocityVector<parent> get_velocity(const Date& date) const { return _velocity; }
};

} // namespace astro
} // namespace astrea