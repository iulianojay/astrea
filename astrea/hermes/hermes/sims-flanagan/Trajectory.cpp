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

#include <hermes/sims-flanagan/Trajectory.hpp>

namespace astrea {
namespace hermes {

using astro::State;

Trajectory Trajectory::ballistic(
    astro::Integrator& integrator,
    astro::Vehicle& vehicle,
    const State& initialState,
    const Time& propTime,
    std::size_t nSegments,
    std::size_t nSubsegmentsPerSegment
)
{
    std::vector<Segment> segments;
    segments.reserve(nSegments);

    State segmentState        = initialState;
    const Time segmentTime    = propTime / nSegments;
    const Time subsegmentTime = segmentTime / nSubsegmentsPerSegment;
    for (std::size_t ii = 0; ii < nSegments; ++ii) {
        const Segment segment = Segment::ballistic(integrator, vehicle, segmentState, segmentTime, nSubsegmentsPerSegment);
        segments.emplace_back(segment);
        segmentState = segment.get_final_state();
    }
    return Trajectory(segments);
}

} // namespace hermes
} // namespace astrea