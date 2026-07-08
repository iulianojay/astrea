/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <hermes/sims-flanagan/model/Subsegment.hpp>

namespace astrea {
namespace hermes {

Subsegment::Subsegment(const Node& initialNode, const Node& finalNode) :
    _initialNode(initialNode),
    _finalNode(finalNode)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

Subsegment Subsegment::ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& timeOfFlight)
{
    const State state = integrator.propagate_no_storage(initialState.get_state(), timeOfFlight, vehicle);
    Subsegment subsegment({ Node(initialState), Node(state) });
    subsegment.set_direction(true);
    return subsegment;
}

astro::StateHistory Subsegment::propagate(
    astro::Integrator& integrator,
    astro::Vehicle& vehicle,
    const State& initialState,
    const Time& timeOfFlight,
    const DeltaV& initialBurn,
    const DeltaV& finalBurn,
    bool store
)
{
    const State startingState(_isForward ? initialState + initialBurn : initialState - finalBurn);
    const Time propTime = _isForward ? timeOfFlight : -timeOfFlight;

    astro::StateHistory history;
    State endState;
    if (store) {
        history  = integrator.propagate(startingState.get_state(), propTime, vehicle);
        endState = history.last();
    }
    else {
        endState = integrator.propagate_no_storage(startingState.get_state(), propTime, vehicle);
    }

    const Node initialNode = _isForward ? Node(initialState, startingState) : Node(endState - initialBurn, endState);
    const Node finalNode   = _isForward ? Node(endState, endState + finalBurn) : Node(initialState, startingState);

    set_initial_node(initialNode);
    set_final_node(finalNode);

    return history;
}

std::size_t Subsegment::get_id() const { return _id; }

void Subsegment::set_initial_node(const Node& node) { _initialNode = node; }

void Subsegment::set_final_node(const Node& node) { _finalNode = node; }

void Subsegment::set_direction(bool isForward) { _isForward = isForward; }

const Node& Subsegment::get_initial_node() const { return _initialNode; }

const Node& Subsegment::get_final_node() const { return _finalNode; }

const State& Subsegment::get_initial_state() const { return _initialNode.get_state_in(); }

const State& Subsegment::get_final_state() const { return _finalNode.get_state_out(); }

OptionalRef<const Node> Subsegment::get_node(std::size_t id) const
{
    if (_initialNode.get_id() == id) { return _initialNode; }
    else if (_finalNode.get_id() == id) {
        return _finalNode;
    }
    return std::nullopt;
}

OptionalRef<Node> Subsegment::get_node(std::size_t id)
{
    if (_initialNode.get_id() == id) { return _initialNode; }
    else if (_finalNode.get_id() == id) {
        return _finalNode;
    }
    return std::nullopt;
}

OptionalRef<const State> Subsegment::get_state(std::size_t id) const
{
    const auto state0 = _initialNode.get_state(id);
    if (state0) { return state0; }

    const auto statef = _finalNode.get_state(id);
    if (statef) { return statef; }

    return std::nullopt;
}

OptionalRef<State> Subsegment::get_state(std::size_t id)
{
    auto state0 = _initialNode.get_state(id);
    if (state0) { return state0; }

    auto statef = _finalNode.get_state(id);
    if (statef) { return statef; }

    return std::nullopt;
}

} // namespace hermes
} // namespace astrea