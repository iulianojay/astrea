/**
 * @file RadialTangentialNormal.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the RadialTangentialNormal class in the astro namespace
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
 * @brief Class representing the Radial, Tagential, Normal (RTN) frame.
 */
class RadialTangentialNormal : public DynamicFrame {

  public:
    RadialTangentialNormal() = delete; //<! Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for RadialTangentialNormal.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    RadialTangentialNormal(const FrameReference* parent) :
        DynamicFrame("Radial, Tagential, Normal", parent){};

    /**
     * @brief Default destructor for RadialTangentialNormal.
     */
    ~RadialTangentialNormal() = default;

    /**
     * @brief Converts a CartesianVector from RTN coordinates to RTN coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param rtnVec The CartesianVector in RTN coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, RadialTangentialNormal> The converted CartesianVector in RTN coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, RadialTangentialNormal>
        convert_to_this_frame(const CartesianVector<Value_T, RadialTangentialNormal>& rtnVec, const Date& date) const
    {
        return rtnVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, RadialTangentialNormal>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * eciVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, RadialTangentialNormal>& rtnVec, const Date& date) const
    {
        return get_dcm(date).transpose() * rtnVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to RTN coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<RadialTangentialNormal> The converted CartesianVector in RTN coordinates.
     */
    RadiusVector<RadialTangentialNormal> convert_to_this_frame(const RadiusVector<EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * (eciVec - _parent->get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from RTN coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param rtnVec The CartesianVector in RTN coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<EarthCenteredInertial>
        convert_from_this_frame(const RadiusVector<RadialTangentialNormal>& rtnVec, const Date& date) const
    {
        return get_dcm(date).transpose() * rtnVec + _parent->get_inertial_position(date);
    }

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RTN frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal> The DCM from ECI to RTN.
     */
    DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal> get_dcm(const Date& date) const
    {
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal>::from_vectors(r, -r.cross(h), h);
    }
};

/**
 * @brief Alias for RadialTangentialNormal.
 */
using RTN = RadialTangentialNormal; // Alias for convenience

} // namespace astro
} // namespace waveguide