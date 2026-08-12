/**
 * @file FieldOfView.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Field of View (FoV) classes for representing different types of sensor fields of view.
 * @date 2025-08-03
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

#include <numbers>
#include <unordered_map>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/fov/FieldOfView.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Circular field of view implementation.
 *
 * This class represents a circular field of view defined by a half-cone angle.
 */
class CircularFieldOfView : public FieldOfView {
  public:
    /**
     * @brief Constructor for CircularFieldOfView.
     *
     * @param halfConeAngle The half-cone angle defining the field of view.
     */
    CircularFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::si::unit_symbols::rad);

    /**
     * @brief Default destructor for CircularFieldOfView.
     */
    ~CircularFieldOfView() = default;

    /**
     * @brief Checks if a target is within the circular field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the circular field of view.
     * @return false If the target is outside the circular field of view.
     */
    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const;

    Angle max_half_angle() const override { return _halfConeAngle; }

  private:
    Angle _halfConeAngle;       // Half-cone angle defining the circular field of view
    Unitless _cosHalfConeAngle; // cos(_halfConeAngle), pre-computed for fast containment checks
};

} // namespace trace
} // namespace astrea