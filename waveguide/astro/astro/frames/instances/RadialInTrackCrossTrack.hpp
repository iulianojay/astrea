/**
 * @file RadialInTrackCrossTrack.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the RadialInTrackCrossTrack class in the astro namespace
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
 * @brief Class representing the Radial, In-Track, Cross-Track (RIC) frame.
 */
class RadialInTrackCrossTrack : public DynamicFrame {

  public:
    RadialInTrackCrossTrack() = delete; //<! Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for RadialInTrackCrossTrack.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    RadialInTrackCrossTrack(const FrameReference* parent) :
        DynamicFrame("Radial, In-Track, Cross-Track", parent){};

    /**
     * @brief Default destructor for RadialInTrackCrossTrack.
     */
    ~RadialInTrackCrossTrack() = default;

    /**
     * @brief Converts a CartesianVector from RIC coordinates to RIC coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param ricVec The CartesianVector in RIC coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, RadialInTrackCrossTrack> The converted CartesianVector in RIC coordinates.
     */
    template <typename Value_T>
    CartesianVector<Value_T, RadialInTrackCrossTrack>
        convert_to_this_frame(const CartesianVector<Value_T, RadialInTrackCrossTrack>& ricVec, const Date& date) const
    {
        return ricVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, RadialInTrackCrossTrack>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * eciVec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, RadialInTrackCrossTrack>& ricVec, const Date& date) const
    {
        return get_dcm(date).transpose() * ricVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to RIC coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<RadialInTrackCrossTrack> The converted CartesianVector in RIC coordinates.
     */
    RadiusVector<RadialInTrackCrossTrack> convert_to_this_frame(const RadiusVector<EarthCenteredInertial>& eciVec, const Date& date) const
    {
        return get_dcm(date) * (eciVec - _parent->get_inertial_position(date));
    }

    /**
     * @brief Converts a CartesianVector from RIC coordinates to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param ricVec The CartesianVector in RIC coordinates.
     * @param date The date for which the conversion is performed.
     * @return RadiusVector<EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    RadiusVector<EarthCenteredInertial>
        convert_from_this_frame(const RadiusVector<RadialInTrackCrossTrack>& ricVec, const Date& date) const
    {
        return get_dcm(date).transpose() * ricVec + _parent->get_inertial_position(date);
    }

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack> The DCM from ECI to RIC.
     */
    DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack> get_dcm(const Date& date) const
    {
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack>::from_vectors(r, v, h);
    }
};

/**
 * @brief Alias for RadialInTrackCrossTrack.
 */
using RIC = RadialInTrackCrossTrack; // Alias for convenience

} // namespace astro
} // namespace waveguide