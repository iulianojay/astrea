/**
 * @file Node.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Node module
 * @date 2026-04-24
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <astro/astro.hpp>
#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing a node in the Sims-Flanagan trajectory
 */
class Node {
  public:
    /**
     * @brief Construct a new Node object
     *
     * @param state The state of the node
     */
    Node(const State& state = {});

    /**
     * @brief Construct a new Node object
     *
     * @param stateIn The state of the trajectory entering the node
     * @param stateOut The state of the trajectory exiting the node
     */
    Node(const State& stateIn, const State& stateOut);

    /**
     * @brief Default destructor for the Node class
     */
    ~Node() = default;

    /**
     * @brief Get the unique identifier for this Node instance
     *
     * @return std::size_t The unique identifier for this Node instance
     */
    std::size_t get_id() const;

    /**
     * @brief Get the state of the trajectory entering the node
     *
     * @return const State& The state of the trajectory entering the node
     */
    const State& get_state_in() const;

    /**
     * @brief Get the state of the trajectory exiting the node
     *
     * @return const State& The state of the trajectory exiting the node
     */
    const State& get_state_out() const;

    /**
     * @brief Get the state of the node with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<const State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<const State> get_state(std::size_t id) const;

    /**
     * @brief Get the state of the node with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<State> get_state(std::size_t id);

  private:
    std::size_t _id; //!< Unique identifier for this Node instance
    State _stateIn;  //!< The state of the trajectory entering the node
    State _stateOut; //!< The state of the trajectory exiting the node
};

} // namespace hermes
} // namespace astrea