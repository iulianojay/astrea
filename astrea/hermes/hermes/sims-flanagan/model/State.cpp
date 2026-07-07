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

#include <hermes/sims-flanagan/model/State.hpp>

#include <utilities/IdProvider.hpp>

namespace astrea {
namespace hermes {

State::State(const astro::State& state) :
    _state(state)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

std::size_t State::get_id() const { return _id; }

const astro::State& State::get_state() const { return _state; }

astro::Cartesian<astro::frames::primary> State::get_cartesian() const
{
    return _state.in_element_set<astro::Cartesian<astro::frames::primary>>();
}

} // namespace hermes
} // namespace astrea
