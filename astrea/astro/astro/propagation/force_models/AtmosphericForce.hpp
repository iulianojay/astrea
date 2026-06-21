/**
 * @file AtmosphericForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle.
 * @date 2025-08-02
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

#include <map>
#include <tuple>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the atmospheric force on a vehicle.
 *
 * This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere.
 */
class AtmosphericForce : public PerturbingForce {

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
     * @return Perturbation The computed force and torque due to atmospheric force.
     */
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override;

    /**
     * @brief Creates a deep copy of this AtmosphericForce object.
     *
     * @return std::unique_ptr<PerturbingForce> A unique pointer to the cloned AtmosphericForce object.
     */
    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<AtmosphericForce>(*this); }
};

} // namespace astro
} // namespace astrea