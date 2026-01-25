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
     * @brief Constructor for StateTransitionMatrix from a KeplerianStm.
     *
     * @param stm The KeplerianStm to initialize from.
     */
    // StateTransitionMatrix(KeplerianStm stm) :
    //     _stm(stm)
    // {
    // }

    // /**
    //  * @brief Constructor for StateTransitionMatrix from an EquinoctialStm.
    //  *
    //  * @param stm The EquinoctialStm to initialize from.
    //  */
    // StateTransitionMatrix(EquinoctialStm stm) :
    //     _stm(stm)
    // {
    // }

    /**
     * @brief Set the STM element at (ii, jj) to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     */
    template <std::size_t ii, std::size_t jj>
    void set(const auto& value)
    {
        std::visit([&](auto&& stm) { stm.template set<ii, jj>(value); }, _stm);
    }

    /**
     * @brief Get the STM element at (ii, jj).
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return auto& STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
    const auto& get() const
    {
        return std::visit([&](auto&& stm) -> const auto& { return stm.template get<ii, jj>(); }, _stm);
    }

    /**
     * @brief Get the STM element at (ii, jj).
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return auto& STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
    auto& get()
    {
        return std::visit([&](auto&& stm) -> auto& { return stm.template get<ii, jj>(); }, _stm);
    }

    /**
     * @brief Convert the STM to a vector of unitless quantities.
     *
     * @return std::vector<Unitless> Vector representation of the STM.
     */
    std::vector<Unitless> force_to_vector() const
    {
        return std::visit([&](auto&& stm) -> std::vector<Unitless> { return stm.force_to_vector(); }, _stm);
    }

  private:
    std::variant<CartesianStm> _stm; //, KeplerianStm, EquinoctialStm> _stm;
};

} // namespace astro
} // namespace astrea
