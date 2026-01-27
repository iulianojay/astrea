/**
 * @file StateTransitionMatrix.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the StateTransitionMatrix class.
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

#include <variant>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/state_transition_matrix/instances/CartesianStm.hpp>

namespace astrea {
namespace astro {

class StateTransitionMatrix {
  public:
    /**
     * @brief Default constructor for StateTransitionMatrix.
     */
    StateTransitionMatrix() = default;

    /**
     * @brief Default destructor for StateTransitionMatrix.
     */
    ~StateTransitionMatrix() = default;

    /**
     * @brief Constructor for StateTransitionMatrix from a CartesianStm.
     *
     * @param stm The CartesianStm to initialize from.
     */
    StateTransitionMatrix(CartesianStm stm) :
        _stm(stm)
    {
    }

    /**
     * @brief Constructor for StateTransitionMatrix. Uses the provided equations of motion
     *  and state to initialize the STM numerically.
     *
     * @param eom Equations of motion object
     * @param state Current orbital elements state vector
     * @param vehicle Vehicle object
     */
    StateTransitionMatrix(const EquationsOfMotion& eom, const OrbitalElements& state, const Vehicle& vehicle);

    /**
     * @brief Set the STM element at (ii, jj) to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     *
     * @note The value's unit will be forced to a unitless representation inside the STM. It is on the user to ensure
     *  that the correct units are used for the STM elements. I'm sorry.
     */
    template <Quantity Value_T, std::size_t ii, std::size_t jj>
    void set(const Value_T& value)
    {
        _stm[ii][jj] = value.in(value.unit);
    }

    /**
     * @brief Convert the STM to a vector of unitless quantities.
     *
     * @return std::vector<Unitless> Vector representation of the STM.
     */
    std::vector<Unitless> force_to_vector() const;

  private:
    std::array<std::array<Unitless, 6>, 6> _stm; //, KeplerianStm, EquinoctialStm> _stm;
};

} // namespace astro
} // namespace astrea
