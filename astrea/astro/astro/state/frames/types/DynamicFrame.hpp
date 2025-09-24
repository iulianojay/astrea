/**
 * @file DynamicFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DynamicFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

#include <astro/state/frames/Frame.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all dynamic state/frames.
 */
template <class Frame_T, FrameAxis axis>
    requires(axis != FrameAxis::ICRF && axis != FrameAxis::J2000 && axis != FrameAxis::BODY_FIXED)
struct DynamicFrame : public Frame<Frame_T, CelestialBodyId::CUSTOM, axis> {
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
                "Parent of a dynamic frame cannot be null. Use Frame_T::instantaneous(r, v) "
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
    DynamicFrame(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        _position(position),
        _velocity(velocity),
        _isInstantaneous(true)
    {
    }

  public:
    /**
     * @brief Creates an instantaneous Frame_T frame.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     * @return Frame_T The instantaneous frame.
     */
    static Frame_T instantaneous(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity)
    {
        return Frame_T(position, velocity);
    }

    /**
     * @brief Rotates a CartesianVector from Earth-Centered Inertial (ECI) to Frame_T coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The rotated CartesianVector in Frame_T coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, Frame_T>
        rotate_into_this_frame(const CartesianVector<Value_T, frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    /**
     * @brief Rotates a CartesianVector from Frame_T coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, frames::earth::icrf> The rotated CartesianVector in ECI coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, frames::earth::icrf>
        rotate_out_of_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to Frame_T coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<Frame_T> The converted CartesianVector in Frame_T coordinates.
     */
    RadiusVector<Frame_T> convert_to_this_frame(const RadiusVector<frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * (vec - get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from Frame_T coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<frames::earth::icrf> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<frames::earth::icrf> convert_from_this_frame(const RadiusVector<Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec + get_inertial_position(date);
    }

  private:
    /**
     * @brief Get the direction cosine matrix (DCM) from Earth-Centered Inertial (ECI) to Frame_T coordinates.
     *
     * @param date The date for which the DCM is requested.
     * @return DCM<frames::earth::icrf, Frame_T> The DCM from ECI to Frame_T coordinates.
     */
    DCM<frames::earth::icrf, Frame_T> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Frame_T*>(this)->get_dcm(date);
    }

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