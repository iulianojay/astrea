/**
 * @file LocalHorizontalLocalVertical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the LocalHorizontalLocalVertical class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/instances/EarthCenteredInertial.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class representing the Local Horizontal, Local Vertical (LVLH) frame.
 */
class LocalHorizontalLocalVertical : public DynamicFrame {

  public:
    /**
     * @brief Default constructor for LocalHorizontalLocalVertical.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    LocalHorizontalLocalVertical(const FrameReference* parent) :
        DynamicFrame("Local Horizontal, Local Vertical", parent)
    {
    }

  private:
    LocalHorizontalLocalVertical(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Local Horizontal, Local Vertical", nullptr),
        _position(position),
        _velocity(velocity)
    {
    }

  public:
    static LocalHorizontalLocalVertical
        instantaneous(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity)
    {
        return LocalHorizontalLocalVertical(position, velocity);
    }

    /**
     * @brief Default destructor for LocalHorizontalLocalVertical.
     */
    ~LocalHorizontalLocalVertical() = default;

    /**
     * @brief Converts a CartesianVector from LVLH coordinates to LVLH coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param lvlhVec The CartesianVector in LVLH coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Distance, LocalHorizontalLocalVertical> The converted CartesianVector in LVLH coordinates.
     */
    RadiusVector<LocalHorizontalLocalVertical>
        convert_to_this_frame(const RadiusVector<LocalHorizontalLocalVertical>& lvlhVec, const Date& date) const
    {
        return lvlhVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, LocalHorizontalLocalVertical>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * eciVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, LocalHorizontalLocalVertical>& lvlhVec, const Date& date) const
    {
        return get_dcm(date).transpose() * lvlhVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to LVLH coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<LocalHorizontalLocalVertical> The converted CartesianVector in LVLH coordinates.
     */
    RadiusVector<LocalHorizontalLocalVertical>
        convert_to_this_frame(const RadiusVector<EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * (eciVec - _parent->get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from LVLH coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param lvlhVec The CartesianVector in LVLH coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<EarthCenteredInertial>
        convert_from_this_frame(const RadiusVector<LocalHorizontalLocalVertical>& lvlhVec, const Date& date) const
    {
        return get_dcm(date).transpose() * lvlhVec + _parent->get_inertial_position(date);
    }

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date.
     *
     * @param date The date for which the DCM is computed.
     * @return DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical> The DCM from ECI to LVLH.
     */
    DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical> get_dcm(const Date& date) const
    {
        if (!_parent) { // Assume instantaneous instance
            const auto r = _position.unit();
            const auto v = _velocity.unit();
            const auto h = r.cross(v).unit();
            return DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical>::from_vectors((-h).cross(-r), -h, -r);
        }
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical>::from_vectors((-h).cross(-r), -h, -r);
    }

  private:
    RadiusVector<EarthCenteredInertial> _position;
    VelocityVector<EarthCenteredInertial> _velocity;
};

/**
 * @brief Alias for LocalHorizontalLocalVertical.
 */
using LVLH = LocalHorizontalLocalVertical; // Alias for convenience

} // namespace astro
} // namespace waveguide