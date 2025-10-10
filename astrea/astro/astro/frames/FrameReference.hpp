/**
 * @file FrameReference.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the FrameReference class in the astro namespace
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all frame references.
 *
 * This class provides a common interface for all frame references used in the
 * astrodynamics library. It allows for easy conversion between different
 * coordinate state/frames.
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
    virtual std::string get_name() const = 0; //!< Get the name of the frame reference.

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, frames::earth::icrf>
     */
    virtual CartesianVector<Distance, frames::earth::icrf> get_inertial_position(const Date& date) const = 0;

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return CartesianVector<Velocity, frames::earth::icrf>
     */
    virtual CartesianVector<Velocity, frames::earth::icrf> get_inertial_velocity(const Date& date) const = 0;

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return CartesianVector<Acceleration, frames::earth::icrf>
     */
    virtual CartesianVector<Acceleration, frames::earth::icrf> get_inertial_acceleration(const Date& date) const;
};

} // namespace astro
} // namespace astrea