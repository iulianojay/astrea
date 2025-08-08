/**
 * @file FrameReference.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the FrameReference class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all frame references.
 *
 * This class provides a common interface for all frame references used in the
 * astrodynamics library. It allows for easy conversion between different
 * coordinate frames.
 */
class FrameReference {
  public:
    /**
     * @brief Default constructor for FrameReference.
     *
     * Initializes the frame reference with default values.
     */
    FrameReference() = default;

    /**
     * @brief Default destructor for FrameReference.
     */
    virtual ~FrameReference() = default;

    /**
     * @brief Get the name of the frame reference.
     *
     * @return std::string The name of the frame reference.
     */
    virtual std::string get_name() const = 0; //<! Get the name of the frame reference.

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, EarthCenteredInertial>
     */
    virtual CartesianVector<Distance, EarthCenteredInertial> get_inertial_position(const Date& date) const = 0;

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return CartesianVector<Velocity, EarthCenteredInertial>
     */
    virtual CartesianVector<Velocity, EarthCenteredInertial> get_inertial_velocity(const Date& date) const = 0;

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return CartesianVector<Acceleration, EarthCenteredInertial>
     */
    virtual CartesianVector<Acceleration, EarthCenteredInertial> get_inertial_acceleration(const Date& date) const;
};

} // namespace astro
} // namespace waveguide