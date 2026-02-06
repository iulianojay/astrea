/**
 * @file AtmosphericForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle.
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

#include <map>
#include <tuple>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the atmospheric force on a vehicle.
 *
 * This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere.
 */
class AtmosphericForce : public Force {

  public:
    /**
     * @brief Default constructor for AtmosphericForce.
     */
    AtmosphericForce() = default;

    /**
     * @brief Default destructor for AtmosphericForce.
     */
    ~AtmosphericForce() = default;

    /**
     * @brief Computes the atmospheric force on a vehicle.
     *
     * @param state State of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return AccelerationVector<frames::earth::icrf> The computed acceleration vector due to atmospheric force.
     */
    CartesianVector<Acceleration, frames::earth::icrf> compute_force(const State& state, const Vehicle& vehicle) const override;

  private:
    /**
     * @brief Finds the atmospheric density at a given altitude.
     *
     * @param state Cartesian state vector of the vehicle
     * @param center Celestial body around which the vehicle is orbiting
     * @return Density The atmospheric density at the given altitude.
     */
    const Density find_atmospheric_density(const State& state, const std::unique_ptr<CelestialBody>& center) const;
};

} // namespace astro
} // namespace astrea