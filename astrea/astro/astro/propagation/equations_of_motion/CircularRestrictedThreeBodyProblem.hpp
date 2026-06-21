/**
 * @file CircularRestrictedThreeBodyProblem.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Circular Restricted Three-Body Problem equations of motion class.
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class implementing the Circular Restricted Three-Body Problem equations of motion.
 */
class CircularRestrictedThreeBodyProblem : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for the Circular Restricted Three-Body Problem.
     *
     * @param forces The force model to be used in the equations of motion.
     */
    CircularRestrictedThreeBodyProblem(const ForceModel& forces);

    /**
     * @brief Destructor for the Circular Restricted Three-Body Problem.
     */
    ~CircularRestrictedThreeBodyProblem() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using the Circular Restricted Three-Body Problem.
     *
     * @param state The current state of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    OrbitalElementPartials compute_dynamics(
        const State& state,
        const Vehicle& vehicle,
        const ForceVector<frames::primary>& perts,
        const ForceVector<frames::primary>& control
    ) const override;

    /**
     * @brief Returns the expected set of orbital elements for this method.
     *
     * @return std::size_t The expected set id of orbital elements.
     */
    constexpr std::size_t get_expected_set_id() const override
    {
        return OrbitalElements::get_set_id<Cartesian<frames::primary>>();
    };

    /**
     * @brief Creates a deep copy of this CircularRestrictedThreeBodyProblem object.
     *
     * @return std::unique_ptr<EquationsOfMotion> A unique pointer to the cloned CircularRestrictedThreeBodyProblem object.
     */
    std::unique_ptr<EquationsOfMotion> clone() const override
    {
        return std::make_unique<CircularRestrictedThreeBodyProblem>(*this);
    }
};

using CR3BP = CircularRestrictedThreeBodyProblem;

} // namespace astro
} // namespace astrea