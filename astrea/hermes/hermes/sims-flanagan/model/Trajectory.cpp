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

#include <hermes/sims-flanagan/model/Trajectory.hpp>

namespace astrea {
namespace hermes {

Trajectory::Trajectory(const std::vector<Segment>& segments) :
    _segments(segments)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

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

    State segmentState     = initialState;
    const Time segmentTime = propTime / nSegments;
    for (std::size_t ii = 0; ii < nSegments; ++ii) {
        const Segment segment = Segment::ballistic(integrator, vehicle, segmentState, segmentTime, nSubsegmentsPerSegment);
        segmentState = segment.get_final_state();
        segments.emplace_back(segment);
    }
    return Trajectory(segments);
}

static Trajectory from_vector(std::size_t nSubsegments, const std::vector<double>& vec)
{
    /*
    Trajectory has n segments, each segment has m subsegments, each subsegment has 2 nodes and a time of flight,
    each node has 6 state variables. Each trajectory also has n-1 delta-vs, each segment has m-1 delta-vs, each with
    3 components. So the total number of parameters is :
    s = n * m * (2 * 6 + 1) + (n - 1) * 3 + n * (m - 1) * 3 = n * (13 * m + 3 + m - 1) - 3 = n * (14 * m + 2) - 3

    Solving for n gives : n = (s + 3) / (14 * m + 2)

    Each Node has 12 variables
    Each Subsegment has 25 variables (2 nodes + time of flight)
    Each Segment has m subsegments and m-1 delta-vs, so it has m * 25 + (m - 1) * 3 = 26 * m - 3 variables

    Now we slice the vector in a hard-coded way:
    x[0 : 14 * m + 2] -> segment 1
    x[14 * m + 3 : 2 * (14 * m + 2)] -> segment 2
    ...
    x[(n - 1) * (14 * m + 2) : n * (14 * m + 2)] -> segment n
    x[n * (14 * m + 2) : n * (14 * m + 2) + 3] -> delta-vs between segments

    For each segment:
    x[]

    */
    const std::size_t nSegments = (vec.size() + 3) / (14 * nSubsegments + 2);
    std::vector<Segment> segments;
    segments.reserve(nSegments);
}

std::vector<double> to_vector() const {}

std::size_t Trajectory::get_id() const { return _id; }

const std::vector<Segment>& Trajectory::get_segments() const { return _segments; }

const State& Trajectory::get_initial_state() const { return _segments.front().get_initial_state(); }

const State& Trajectory::get_final_state() const { return _segments.back().get_final_state(); }

OptionalRef<const Segment> Trajectory::get_segment(std::size_t id) const
{
    for (const auto& segment : _segments) {
        if (segment.get_id() == id) { return segment; }
    }
    return std::nullopt;
}

OptionalRef<Segment> Trajectory::get_segment(std::size_t id)
{
    for (auto& segment : _segments) {
        if (segment.get_id() == id) { return segment; }
    }
    return std::nullopt;
}

OptionalRef<const Subsegment> Trajectory::get_subsegment(std::size_t id) const
{
    for (const auto& segment : _segments) {
        auto subsegment = segment.get_subsegment(id);
        if (subsegment) { return subsegment; }
    }
    return std::nullopt;
}

OptionalRef<Subsegment> Trajectory::get_subsegment(std::size_t id)
{
    for (auto& segment : _segments) {
        auto subsegment = segment.get_subsegment(id);
        if (subsegment) { return subsegment; }
    }
    return std::nullopt;
}

OptionalRef<const Node> Trajectory::get_node(std::size_t id) const
{
    for (const auto& segment : _segments) {
        const auto node = segment.get_node(id);
        if (node) { return node; }
    }
    return std::nullopt;
}

OptionalRef<Node> Trajectory::get_node(std::size_t id)
{
    for (auto& segment : _segments) {
        auto node = segment.get_node(id);
        if (node) { return node; }
    }
    return std::nullopt;
}

OptionalRef<const State> Trajectory::get_state(std::size_t id) const
{
    for (const auto& segment : _segments) {
        const auto state = segment.get_state(id);
        if (state) { return state; }
    }
    return std::nullopt;
}

OptionalRef<State> Trajectory::get_state(std::size_t id)
{
    for (auto& segment : _segments) {
        auto state = segment.get_state(id);
        if (state) { return state; }
    }
    return std::nullopt;
}

} // namespace hermes
} // namespace astrea