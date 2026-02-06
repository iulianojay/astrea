/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the SolarRadiationPressure class, which computes the solar radiation pressure force on a spacecraft.
 * @date 2025-08-02
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the solar radiation pressure force on a spacecraft.
 *
 */
class SolarRadiationPressure : public Force {
  public:
    /**
     * @brief Default constructor for SolarRadiationPressure.
     */
    SolarRadiationPressure() = default;

    /**
     * @brief Default destructor for SolarRadiationPressure.
     */
    ~SolarRadiationPressure() = default;

    /**
     * @brief Computes the solar radiation pressure force on a spacecraft.
     *
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return AccelerationVector<frames::earth::icrf> The computed acceleration vector due to solar radiation pressure.
     */
    CartesianVector<Acceleration, frames::earth::icrf> compute_force(const State& state, const Vehicle& vehicle) const override;

  private:
};

} // namespace astro
} // namespace astrea