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

    DynamicFrame(const std::string& name, const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        Frame(name, "Instantaneous Dynamic Frame Instance"),
        _position(position),
        _velocity(velocity),
        _isInstantaneous(true)
    {
    }

  public:
    template <typename Value_T>
    CartesianVector<Value_T, Frame_T> convert_to_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date) const
    {
        return vec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, Frame_T>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to LVLH coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<Frame_T> The converted CartesianVector in LVLH coordinates.
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
    DCM<EarthCenteredInertial, Frame_T> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Frame_T*>(this)->get_dcm(date);
    }

  protected:
    const FrameReference* _parent;                   //!< The parent object this frame is attached to.
    bool _isInstantaneous;                           //!< Flag indicating if the frame is instantaneous.
    RadiusVector<EarthCenteredInertial> _position;   //!< The position vector in the ECI frame.
    VelocityVector<EarthCenteredInertial> _velocity; //!< The velocity vector in the ECI frame.
};

} // namespace astro
} // namespace waveguide