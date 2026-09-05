/**
 * @file PerturbingForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the PerturbingForce class, which defines the interface for force models in astrodynamics.
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

#include <memory>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Abstract base class for force models in astrodynamics.
 *
 * This class defines the interface for computing forces acting on a vehicle in space.
 */
class PerturbingForce {
  public:
    /**
     * @brief Default constructor for PerturbingForce.
     */
    PerturbingForce() = default;

    /**
     * @brief Default destructor for PerturbingForce.
     */
    virtual ~PerturbingForce() = default;

    /**
     * @brief Computes the force acting on a vehicle at a given date and state.
     *
     * @param state State of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The computed acceleration and torque vectors due to the force.
     */
    virtual Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const = 0;

    /**
     * @brief Creates a clone of the current PerturbingForce object.
     *
     * @return std::unique_ptr<PerturbingForce> A unique pointer to the cloned PerturbingForce object.
     */
    virtual std::unique_ptr<PerturbingForce> clone() const = 0;

    /**
     * @brief Binds a shared space weather provider to this force.
     *
     * Default implementation is a no-op for forces that do not use space weather.
     */
    virtual void bind_space_weather_provider(std::shared_ptr<const SpaceWeatherProvider> provider) { (void)provider; }
};

} // namespace astro
} // namespace astrea