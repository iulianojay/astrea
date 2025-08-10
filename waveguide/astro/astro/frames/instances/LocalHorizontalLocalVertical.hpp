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
class LocalHorizontalLocalVertical : public DynamicFrame<LocalHorizontalLocalVertical> {

  public:
    LocalHorizontalLocalVertical() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for LocalHorizontalLocalVertical.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    LocalHorizontalLocalVertical(const FrameReference* parent) :
        DynamicFrame("Local Horizontal, Local Vertical", parent)
    {
    }

    /**
     * @brief Default destructor for LocalHorizontalLocalVertical.
     */
    ~LocalHorizontalLocalVertical() = default;

    /**
     * @brief Creates an instantaneous LocalHorizontalLocalVertical frame.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     * @return LocalHorizontalLocalVertical The instantaneous frame.
     */
    static LocalHorizontalLocalVertical
        instantaneous(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity)
    {
        return LocalHorizontalLocalVertical(position, velocity);
    }

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date.
     *
     * @param date The date for which the DCM is computed.
     * @return DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical> The DCM from ECI to LVLH.
     */
    DirectionCosineMatrix<EarthCenteredInertial, LocalHorizontalLocalVertical> get_dcm(const Date& date) const
    {
        if (_isInstantaneous) { // Assume instantaneous instance
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
    /**
     * @brief Constructor for instantaneous dynamic frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    LocalHorizontalLocalVertical(const RadiusVector<EarthCenteredInertial>& position, const VelocityVector<EarthCenteredInertial>& velocity) :
        DynamicFrame("Local Horizontal, Local Vertical", position, velocity)
    {
    }
};

/**
 * @brief Alias for LocalHorizontalLocalVertical.
 */
using LVLH = LocalHorizontalLocalVertical; // Alias for convenience

} // namespace astro
} // namespace waveguide