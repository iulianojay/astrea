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
 * @brief Class representing the Radial, Tangential, Normal (RTN) frame.
 */
class RadialTangentialNormal : public DynamicFrame<RadialTangentialNormal> {

  public:
    RadialTangentialNormal() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for RadialTangentialNormal.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    RadialTangentialNormal(const FrameReference* parent) :
        DynamicFrame("Radial, Tagential, Normal", parent)
    {
    }

    static RadialTangentialNormal
        instantaneous(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity)
    {
        return RadialTangentialNormal(position, velocity);
    }

  private:
    RadialTangentialNormal(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Radial, Tangential, Normal", position, velocity)
    {
    }

  public:
    /**
     * @brief Default destructor for RadialTangentialNormal.
     */
    ~RadialTangentialNormal() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the RTN frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal> The DCM from ECI to RTN.
     */
    DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal> get_dcm(const Date& date) const
    {
        if (!_parent) { // Assume instantaneous instance
            const auto r = _position.unit();
            const auto v = _velocity.unit();
            const auto h = r.cross(v).unit();
            return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal>::from_vectors(r, -r.cross(h), h);
        }
        const auto r = _parent->get_inertial_position(date).unit();
        const auto v = _parent->get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal>::from_vectors(r, -r.cross(h), h);
    }

  private:
    RadiusVector<EarthCenteredInertial> _position;
    VelocityVector<EarthCenteredInertial> _velocity;
};

/**
 * @brief Alias for RadialTangentialNormal.
 */
using RTN = RadialTangentialNormal; // Alias for convenience

} // namespace astro
} // namespace waveguide