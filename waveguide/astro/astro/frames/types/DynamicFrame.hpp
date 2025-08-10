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

#include <memory>

#include <astro/frames/Frame.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/time/Date.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all dynamic frames.
 */
template <class Frame_T>
class DynamicFrame : public Frame {
  protected:
    /**
     * @brief Constructor for DynamicFrame.
     *
     * @param name The name of the dynamic frame.
     * @param origin The origin of the dynamic frame.
     * @param parent The parent inertial frame that this dynamic frame is based on.
     */
    DynamicFrame(const std::string& name, const FrameReference* parent) :
        Frame(name, parent->get_name()),
        _parent(parent),
        _isInstantaneous(false)
    {
        if (parent == nullptr) {
            throw std::invalid_argument("Parent of a dynamic frame cannot be null. Use Frame_T::instantaneous(r, v) "
                                        "for instantaneous frames.");
        }
    }

    /**
     * @brief Constructor for instantaneous dynamic frames.
     *
     * @param name The name of the dynamic frame.
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    DynamicFrame(const std::string& name, const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        Frame(name, "Instantaneous Dynamic Frame Instance"),
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
    static Frame_T instantaneous(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity)
    {
        return Frame_T(position, velocity);
    }

    /**
     * @brief Converts a CartesianVector from Frame_T coordinates to itself - null conversion.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The converted CartesianVector in Frame_T coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, Frame_T> convert_to_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date) const
    {
        return vec;
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
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    /**
     * @brief Rotates a CartesianVector from Frame_T coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredInertial> The rotated CartesianVector in ECI coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
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
    RadiusVector<Frame_T> convert_to_this_frame(const RadiusVector<EarthCenteredInertial>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * (vec - _parent->get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from Frame_T coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<EarthCenteredInertial> convert_from_this_frame(const RadiusVector<Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec + _parent->get_inertial_position(date);
    }

  private:
    /**
     * @brief Get the direction cosine matrix (DCM) from Earth-Centered Inertial (ECI) to Frame_T coordinates.
     *
     * @param date The date for which the DCM is requested.
     * @return DCM<EarthCenteredInertial, Frame_T> The DCM from ECI to Frame_T coordinates.
     */
    DCM<EarthCenteredInertial, Frame_T> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Frame_T*>(this)->get_dcm(date);
    }

  protected:
    const FrameReference* _parent;                   //!< The parent object this frame is attached to.
    bool _isInstantaneous;                           //!< Flag indicating if the frame is instantaneous.
    RadiusVector<EarthCenteredInertial> _position;   //!< The position vector in the ECI frame.
    VelocityVector<EarthCenteredInertial> _velocity; //!< The velocity vector in the ECI frame.

    /**
     * @brief Gets the inertial position vector at a given date.
     *
     * @param date The date for which the position is requested.
     * @return RadiusVector<EarthCenteredInertial> The inertial position vector.
     */
    RadiusVector<EarthCenteredInertial> get_inertial_position(const Date& date) const
    {
        return _isInstantaneous ? _position : _parent->get_inertial_position(date); // TODO: maybe store date for instantaneous and throw here if it doesn't match
    }

    /**
     * @brief Gets the inertial velocity vector at a given date.
     *
     * @param date The date for which the velocity is requested.
     * @return VelocityVector<EarthCenteredInertial> The inertial velocity vector.
     */
    VelocityVector<EarthCenteredInertial> get_inertial_velocity(const Date& date) const
    {
        return _isInstantaneous ? _velocity : _parent->get_inertial_velocity(date);
    }
};

} // namespace astro
} // namespace waveguide