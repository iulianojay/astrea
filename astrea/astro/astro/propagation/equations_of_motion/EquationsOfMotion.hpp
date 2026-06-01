/**
 * @file EquationsOfMotion.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the base class of equations of motion.
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

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for equations of motion in astrodynamics.
 */
class EquationsOfMotion {
  public:
    /**
     * @brief Default constructor for the Equations of Motion class.
     */
    EquationsOfMotion() = default;

    /**
     * @brief Constructor for the Equations of Motion class that takes a ForceModel.
     *
     * @param forces The force model to be used in the equations of motion.
     */
    EquationsOfMotion(const ForceModel& forces);

    /**
     * @brief Destructor for the Equations of Motion class.
     */
    virtual ~EquationsOfMotion() = default;

    /**
     * @brief Computes the partial derivatives of the state.
     *
     * @param state The current state of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return StatePartial The computed partial derivatives of the state.
     */
    StatePartial operator()(const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Computes the partial derivatives of the orbital elements.
     *
     * @param date The current date for which the equations of motion are being computed.
     * @param state The current state of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @param perts The perturbations acting on the vehicle.
     * @param control The control forces produced by the vehicle.
     * @return StatePartial The computed partial derivatives of the orbital elements.
     */
    virtual OrbitalElementPartials compute_dynamics(
        const State& state,
        const Vehicle& vehicle,
        const ForceVector<frames::primary>& perts,
        const ForceVector<frames::primary>& control
    ) const = 0;

    /**
     * @brief Computes the kinematic partial derivatives of the attitude.
     *
     * @param state The current state of the vehicle.
     * @param vehicle The vehicle for which the kinematic partials are being computed.
     * @param perts The perturbations acting on the vehicle.
     * @param control The control torques produced by the vehicle.
     * @return AttitudePartials The computed kinematic partial derivatives of the attitude.
     */
    virtual AttitudePartials compute_kinematics(
        const State& state,
        const Vehicle& vehicle,
        const TorqueVector<frames::primary>& perts,
        const TorqueVector<frames::primary>& control
    ) const;

    /**
     * @brief Computes the state transition matrix (STM).
     *
     * @param date The current date for which the STM is being computed.
     * @param state The current state of the vehicle.
     * @param vehicle The vehicle for which the STM is being computed.
     * @return StateTransitionMatrix The computed state transition matrix.
     */
    virtual StateTransitionMatrix compute_stm(const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Returns the expected set of orbital elements for this method.
     *
     * @return std::size_t The expected set id of orbital elements.
     */
    virtual constexpr std::size_t get_expected_set_id() const = 0;

  protected:
    const ForceModel* forces = nullptr; //!< The force model used in the equations of motion.
};

} // namespace astro
} // namespace astrea
