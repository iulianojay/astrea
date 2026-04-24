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

#include <hermes/sims-flanagan/model/Node.hpp>

namespace astrea {
namespace hermes {

Node::Node(const State& state) :
    _stateIn(state),
    _stateOut(state)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

Node::Node(const State& stateIn, const State& stateOut) :
    _stateIn(stateIn),
    _stateOut(stateOut)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

std::size_t Node::get_id() const { return _id; }

const State& Node::get_state_in() const { return _stateIn; }

const State& Node::get_state_out() const { return _stateOut; }

OptionalRef<const State> Node::get_state(std::size_t id) const
{
    if (_stateIn.get_id() == id) { return _stateIn; }
    else if (_stateOut.get_id() == id) {
        return _stateOut;
    }
    return std::nullopt;
}

OptionalRef<State> Node::get_state(std::size_t id)
{
    if (_stateIn.get_id() == id) { return _stateIn; }
    else if (_stateOut.get_id() == id) {
        return _stateOut;
    }
    return std::nullopt;
}

} // namespace hermes
} // namespace astrea
