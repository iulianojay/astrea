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
class RadialInTrackCrossTrack : public DynamicFrame<RadialInTrackCrossTrack> {

  public:
    RadialInTrackCrossTrack() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for RadialInTrackCrossTrack.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    RadialInTrackCrossTrack(const FrameReference* parent) :
        DynamicFrame("Radial, In-Track, Cross-Track", parent)
    {
    }

    static RadialInTrackCrossTrack
        instantaneous(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity)
    {
        return RadialInTrackCrossTrack(position, velocity);
    }

  private:
    RadialInTrackCrossTrack(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Radial, In-Track, Cross-Track", position, velocity)
    {
    }

  public:
    /**
     * @brief Default destructor for RadialInTrackCrossTrack.
     */
    ~RadialInTrackCrossTrack() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RIC frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack> The DCM from ECI to RIC.
     */
    DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack> get_dcm(const Date& date) const
    {
        if (!_parent) { // Assume instantaneous instance
            const auto r = _position.unit();
            const auto v = _velocity.unit();
            const auto h = r.cross(v).unit();
            return DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack>::from_vectors(r, v, h);
        }
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, RadialInTrackCrossTrack>::from_vectors(r, v, h);
    }

  private:
    RadiusVector<EarthCenteredInertial> _position;
    VelocityVector<EarthCenteredInertial> _velocity;
};

/**
 * @brief Alias for RadialInTrackCrossTrack.
 */
using RIC = RadialInTrackCrossTrack; // Alias for convenience

} // namespace astro
} // namespace waveguide