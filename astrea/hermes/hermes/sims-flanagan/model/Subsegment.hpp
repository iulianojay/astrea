/**
 * @file Subsegment.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Subsegment module
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

#include <vector>

#include <astro/astro.hpp>
#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/model/DeltaV.hpp>
#include <hermes/sims-flanagan/model/Node.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing a subsegment of a Sims-Flanagan trajectory, consisting of an initial node and a final node
 */
class Subsegment {
  public:
    /**
     * @brief Construct a new Subsegment object
     *
     * @param initialNode The initial node of the subsegment
     * @param finalNode The final node of the subsegment
     */
    Subsegment() = default;

    /**
     * @brief Construct a new Subsegment object
     *
     * @param initialNode The initial node of the subsegment
     * @param finalNode The final node of the subsegment
     */
    Subsegment(const Node& initialNode, const Node& finalNode = {});

    /**
     * @brief Default destructor for the Subsegment class
     */
    ~Subsegment() = default;

    /**
     * @brief Create a new Subsegment object representing a ballistic trajectory
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @param initialState The initial state of the subsegment
     * @param timeOfFlight The time of flight for the subsegment
     * @return Subsegment A new Subsegment object representing a ballistic trajectory
     */
    static Subsegment ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& timeOfFlight);

    /**
     * @brief Propagate the subsegment, optionally storing the full state history.
     *
     * Burns are applied at the nodes in forward time: the initial node stores
     * (state_in = initialState, state_out = initialState + initialBurn) and the
     * final node stores (state_in = propagated_result, state_out = propagated_result + finalBurn).
     * The ballistic arc runs between initial_node.state_out and final_node.state_in.
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @param initialState The state arriving at the initial node (pre-burn)
     * @param timeOfFlight The time of flight for the subsegment arc
     * @param initialBurn Burn applied at the initial node (default zero)
     * @param finalBurn Burn applied at the final node (default zero)
     * @param store When false (default) skips intermediate state storage; when true returns the full history
     * @return astro::StateHistory The state history (empty when store is false)
     */
    astro::StateHistory propagate(
        astro::Integrator& integrator,
        astro::Vehicle& vehicle,
        const State& initialState,
        const Time& timeOfFlight,
        const DeltaV& initialBurn = {},
        const DeltaV& finalBurn   = {},
        bool store                = false
    );

    /**
     * @brief Get the unique identifier for this Subsegment instance
     *
     * @return std::size_t The unique identifier for this Subsegment instance
     */
    std::size_t get_id() const;

    /**
     * @brief Set the initial node of the subsegment
     *
     * @param node The initial node to set for the subsegment
     */
    void set_initial_node(const Node& node);

    /**
     * @brief Set the final node of the subsegment
     *
     * @param node The final node to set for the subsegment
     */
    void set_final_node(const Node& node);

    /**
     * @brief Set the direction of the subsegment
     *
     * @param isForward Whether the subsegment is forward-propagating (true) or backward-propagating (false)
     */
    void set_direction(bool isForward);

    /**
     * @brief Get the initial node of the subsegment
     *
     * @return const Node& The initial node of the subsegment
     */
    const Node& get_initial_node() const;

    /**
     * @brief Get the final node of the subsegment
     *
     * @return const Node& The final node of the subsegment
     */
    const Node& get_final_node() const;

    /**
     * @brief Get the subsegment time of flight
     *
     * @return const Time& The time of flight for the subsegment
     */
    const Time& get_time_of_flight() const;

    /**
     * @brief Get the initial state of the subsegment
     *
     * @return const State& The initial state of the subsegment
     */
    const State& get_initial_state() const;

    /**
     * @brief Get the final state of the subsegment
     *
     * @return const State& The final state of the subsegment
     */
    const State& get_final_state() const;

    /**
     * @brief Get the node with the given ID
     *
     * @param id The unique identifier of the node to retrieve
     * @return OptionalRef<const Node> An optional reference to the node with the given ID, or std::nullopt if no such node exists
     */
    OptionalRef<const Node> get_node(std::size_t id) const;

    /**
     * @brief Get the node with the given ID
     *
     * @param id The unique identifier of the node to retrieve
     * @return OptionalRef<Node> An optional reference to the node with the given ID, or std::nullopt if no such node exists
     */
    OptionalRef<Node> get_node(std::size_t id);

    /**
     * @brief Get the state with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<const State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<const State> get_state(std::size_t id) const;

    /**
     * @brief Get the state with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<State> get_state(std::size_t id);

  private:
    std::size_t _id;   //!< Unique identifier for this Subsegment instance
    Node _initialNode; //!< The initial node of the subsegment
    Node _finalNode;   //!< The final node of the subsegment
    bool _isForward;   //!< Whether the subsegment is forward-propagating (true) or backward-propagating (false)
};

} // namespace hermes
} // namespace astrea