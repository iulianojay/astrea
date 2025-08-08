/**
 * @file VelocityNormalBinormal.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the VelocityNormalBinormal class in the astro namespace
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
 * @brief Class representing the Velocity, Normal, Binormal (VNB) frame.
 */
class VelocityNormalBinormal : public DynamicFrame {

  public:
    /**
     * @brief Default constructor for VelocityNormalBinormal.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    VelocityNormalBinormal(const FrameReference* parent) :
        DynamicFrame("Velocity, Normal, Binormal", parent){};

    /**
     * @brief Default destructor for VelocityNormalBinormal.
     */
    ~VelocityNormalBinormal() = default;

    /**
     * @brief Converts a CartesianVector from VNB coordinates to VNB coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vnbVec The CartesianVector in VNB coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, VelocityNormalBinormal> The converted CartesianVector in VNB coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, VelocityNormalBinormal>
        convert_to_this_frame(const CartesianVector<Value_T, VelocityNormalBinormal>& vnbVec, const Date& date) const
    {
        return vnbVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, VelocityNormalBinormal>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * eciVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, VelocityNormalBinormal>& vnbVec, const Date& date) const
    {
        return get_dcm(date).transpose() * vnbVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to VNB coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<VelocityNormalBinormal> The converted CartesianVector in VNB coordinates.
     */
    RadiusVector<VelocityNormalBinormal> convert_to_this_frame(const RadiusVector<EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * (eciVec - _parent->get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from VNB coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param vnbVec The CartesianVector in VNB coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<EarthCenteredInertial>
        convert_from_this_frame(const RadiusVector<VelocityNormalBinormal>& vnbVec, const Date& date) const
    {
        return get_dcm(date).transpose() * vnbVec + _parent->get_inertial_position(date);
    }

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal> The DCM from ECI to VNB.
     */
    DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal> get_dcm(const Date& date) const
    {
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal>::from_vectors(v, h, v.cross(h));
    }
};

/**
 * @brief Alias for VelocityNormalBinormal.
 */
using VNB = VelocityNormalBinormal; // Alias for convenience

} // namespace astro
} // namespace waveguide