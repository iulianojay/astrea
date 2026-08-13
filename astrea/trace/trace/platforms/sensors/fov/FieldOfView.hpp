/**
 * @file FieldOfView.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Field of View (FoV) classes for representing different types of sensor fields of view.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <numbers>
#include <unordered_map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Computes the angle between two radius vectors.
 *
 * @param vector1 The first radius vector.
 * @param vector2 The second radius vector.
 * @return Angle The angle between the two vectors.
 */
Angle calculate_angle_between_vectors(
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector1,
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector2
);

/**
 * @brief Base class for Field of View (FoV) representations.
 *
 * This class defines the interface for different types of fields of view.
 */
class FieldOfView {
  public:
    /**
     * @brief Default constructor for FieldOfView.
     */
    FieldOfView() = default;

    /**
     * @brief Virtual destructor for FieldOfView.
     *
     * Ensures proper cleanup of derived classes.
     */
    ~FieldOfView() = default;

    /**
     * @brief Checks if a target is within the field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the field of view.
     * @return false If the target is outside the field of view.
     */
    virtual bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const = 0;

    /**
     * @brief Returns the maximum off-boresight half-angle for this field of view.
     *
     * Used for spatial index culling to determine the maximum sensor footprint radius.
     * The default returns π/2 rad, a conservative bound covering the full hemisphere.
     *
     * @return Angle Maximum off-boresight half-angle.
     */
    virtual Angle max_half_angle() const { return std::numbers::pi / 2.0 * mp_units::si::unit_symbols::rad; }
};

} // namespace trace
} // namespace astrea