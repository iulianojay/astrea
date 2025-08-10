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
class VelocityNormalBinormal : public DynamicFrame<VelocityNormalBinormal> {

    friend DynamicFrame<VelocityNormalBinormal>;

  public:
    /**
     * @brief Default constructor for VelocityNormalBinormal.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    VelocityNormalBinormal(const FrameReference* parent) :
        DynamicFrame("Velocity, Normal, Binormal", parent)
    {
    }

    /**
     * @brief Default destructor for VelocityNormalBinormal.
     */
    ~VelocityNormalBinormal() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the VNB frame at a given date.
     *
     * @param date The date for which the DCM is requested.
     * @return DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal> The DCM from ECI to VNB.
     */
    DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal> get_dcm(const Date& date) const
    {
        const auto r = get_inertial_position(date).unit();
        const auto v = get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<EarthCenteredInertial, VelocityNormalBinormal>::from_vectors(v, h, v.cross(h));
    }

  private:
    /**
     * @brief Constructor for instantaneous dynamic frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    VelocityNormalBinormal(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Velocity, Normal, Binormal", position, velocity)
    {
    }
};

/**
 * @brief Alias for VelocityNormalBinormal.
 */
using VNB = VelocityNormalBinormal; // Alias for convenience

} // namespace astro
} // namespace waveguide