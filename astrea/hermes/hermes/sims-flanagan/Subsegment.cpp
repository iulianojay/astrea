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

#include <hermes/sims-flanagan/Subsegment.hpp>

namespace astrea {
namespace hermes {

using astro::State;

Subsegment Subsegment::ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& timOfFlight)
{
    const State state = integrator.propagate(initialState, timOfFlight, vehicle).last();
    const Subsegment subsegment({ Node(initialState), Node(state), timOfFlight });
    return subsegment;
}

} // namespace hermes
} // namespace astrea