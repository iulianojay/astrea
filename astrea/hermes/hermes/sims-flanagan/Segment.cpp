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

#include <hermes/sims-flanagan/Segment.hpp>

namespace astrea {
namespace hermes {

using astro::State;

Segment Segment::ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& segmentTime, std::size_t nSubsegments)
{
    const Time subsegmentTime = segmentTime / nSubsegments;

    std::vector<Subsegment> subsegments;
    subsegments.reserve(nSubsegments);

    State subsegmentState = initialState;
    for (std::size_t ii = 0; ii < nSubsegments; ++ii) {
        const Subsegment subsegment = Subsegment::ballistic(integrator, vehicle, subsegmentState, subsegmentTime);
        subsegments.emplace_back(subsegment);
        subsegmentState = subsegment.get_final_state();
    }
    const Segment segment(subsegments);
    return Segment(subsegments);
}

} // namespace hermes
} // namespace astrea