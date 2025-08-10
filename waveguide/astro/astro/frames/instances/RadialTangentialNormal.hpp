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

    friend DynamicFrame<RadialTangentialNormal>;

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
        const auto r = get_inertial_position(date).unit();
        const auto v = get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, RadialTangentialNormal>::from_vectors(r, -r.cross(h), h);
    }

  private:
    /**
     * @brief Constructor for instantaneous dynamic frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    RadialTangentialNormal(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Radial, Tangential, Normal", position, velocity)
    {
    }
};

/**
 * @brief Alias for RadialTangentialNormal.
 */
using RTN = RadialTangentialNormal; // Alias for convenience

} // namespace astro
} // namespace waveguide