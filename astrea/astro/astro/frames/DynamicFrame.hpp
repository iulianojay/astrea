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
#include <astro/frames/Frame.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frame_registry.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all dynamic state/frames.
 */
template <IsFrame auto _frame_, FrameAxis _axis>
    requires(_axis != FrameAxis::ICRF && _axis != FrameAxis::J2000 && _axis != FrameAxis::FIXED_ROTATING)
struct DynamicFrame : public Frame<"", CelestialBodyId::CUSTOM, _axis> {

    static constexpr CelestialBodyId origin =
        Frame<"", CelestialBodyId::CUSTOM, _axis>::origin; //!< The central body associated with the inertial frame.
    static constexpr FrameAxis axis = Frame<"", CelestialBodyId::CUSTOM, _axis>::axis; //!< The axis type of the inertial frame.

  protected:
    /**
     * @brief Constructor for DynamicFrame.
     *
     * @param name The name of the dynamic frame.
     * @param origin The origin of the dynamic frame.
     * @param parent The parent inertial frame that this dynamic frame is based on.
     */
    DynamicFrame(const FrameReference* parent) :
        _parent(parent),
        _isInstantaneous(false)
    {
        if (parent == nullptr) {
            throw std::invalid_argument(
                "Parent of a dynamic frame cannot be null. Use frame::instantaneous(r, v) "
                "for instantaneous dynamic state/frames."
            );
        }
    }

    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param name The name of the dynamic frame.
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    DynamicFrame(const RadiusVector<frames::primary>& position, const VelocityVector<frames::primary>& velocity) :
        _position(position),
        _velocity(velocity),
        _isInstantaneous(true)
    {
    }

  public:
    /**
     * @brief Creates an instantaneous _frame_ frame.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     * @return _frame_ The instantaneous frame.
     */
    static _frame_ instantaneous(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity)
    {
        return _frame_(position, velocity);
    }

    /**
     * @brief Rotates a CartesianVector from Earth-Centered Inertial (ECI) to _frame_ coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, _frame_> The rotated CartesianVector in _frame_ coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, _frame_>
        rotate_into_this_frame(const CartesianVector<Value_T, frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    /**
     * @brief Rotates a CartesianVector from _frame_ coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in _frame_ coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, frames::earth::icrf> The rotated CartesianVector in ECI coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, frames::earth::icrf>
        rotate_out_of_this_frame(const CartesianVector<Value_T, _frame_>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to _frame_ coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<_frame_> The converted CartesianVector in _frame_ coordinates.
     */
    RadiusVector<_frame_> convert_to_this_frame(const RadiusVector<frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * (vec - get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from _frame_ coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in _frame_ coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<frames::earth::icrf> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<frames::earth::icrf> convert_from_this_frame(const RadiusVector<_frame_>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec + get_inertial_position(date);
    }

  private:
    /**
     * @brief Get the direction cosine matrix (DCM) from Earth-Centered Inertial (ECI) to _frame_ coordinates.
     *
     * @param date The date for which the DCM is requested.
     * @return DCM<frames::earth::icrf, _frame_> The DCM from ECI to _frame_ coordinates.
     */
    DCM<frames::earth::icrf, _frame_> get_dcm_impl(const Date& date) const
    {
        return static_cast<const _frame_*>(this)->get_dcm(date);
    }

    RadiusVector<frames::earth::icrf> get_center_offset(const Date& date) const { return get_inertial_position(date); }

  protected:
    const FrameReference* _parent;                 //!< The parent object this frame is attached to.
    RadiusVector<frames::earth::icrf> _position;   //!< The position vector in the ECI frame.
    VelocityVector<frames::earth::icrf> _velocity; //!< The velocity vector in the ECI frame.
    bool _isInstantaneous;                         //!< Flag indicating if the frame is instantaneous.

    /**
     * @brief Gets the inertial position vector at a given date.
     *
     * @param date The date for which the position is requested.
     * @return RadiusVector<frames::earth::icrf> The inertial position vector.
     */
    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const
    {
        return _isInstantaneous ? _position : _parent->get_inertial_position(date); // TODO: maybe store date for instantaneous and throw here if it doesn't match
    }

    /**
     * @brief Gets the inertial velocity vector at a given date.
     *
     * @param date The date for which the velocity is requested.
     * @return VelocityVector<frames::earth::icrf> The inertial velocity vector.
     */
    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const
    {
        return _isInstantaneous ? _velocity : _parent->get_inertial_velocity(date);
    }
};

} // namespace astro
} // namespace astrea