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

Segment::Segment(const std::vector<Subsegment>& subsegments) :
    _subsegments(subsegments)
{
    _id = utilities::IdProvider::get_next_id<"Segment">();
}

Segment Segment::ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& segmentTime, std::size_t nSubsegments)
{
    const Time subsegmentTime = segmentTime / nSubsegments;

    std::vector<Subsegment> subsegments;
    subsegments.reserve(nSubsegments);

    State subsegmentState = initialState;
    for (std::size_t ii = 0; ii < nSubsegments; ++ii) {
        const Subsegment subsegment = Subsegment::ballistic(integrator, vehicle, subsegmentState, subsegmentTime);
        subsegmentState             = subsegment.get_final_state();
        subsegments.emplace_back(subsegment);
    }

    const Segment segment(subsegments);
    return Segment(subsegments);
}

std::size_t Segment::get_id() const { return _id; }

const std::vector<Subsegment>& Segment::get_subsegments() const { return _subsegments; }

const State& Segment::get_initial_state() const { return _subsegments.front().get_initial_state(); }

const State& Segment::get_final_state() const { return _subsegments.back().get_final_state(); }

OptionalRef<const Subsegment> Segment::get_subsegment(std::size_t id) const
{
    for (const auto& subsegment : _subsegments) {
        if (subsegment.get_id() == id) { return subsegment; }
    }
    return std::nullopt;
}

OptionalRef<Subsegment> Segment::get_subsegment(std::size_t id)
{
    for (auto& subsegment : _subsegments) {
        if (subsegment.get_id() == id) { return subsegment; }
    }
    return std::nullopt;
}

OptionalRef<const Node> Segment::get_node(std::size_t id) const
{
    for (const auto& subsegment : _subsegments) {
        const auto node = subsegment.get_node(id);
        if (node) { return node; }
    }
    return std::nullopt;
}

OptionalRef<Node> Segment::get_node(std::size_t id)
{
    for (auto& subsegment : _subsegments) {
        auto node = subsegment.get_node(id);
        if (node) { return node; }
    }
    return std::nullopt;
}

OptionalRef<const State> Segment::get_state(std::size_t id) const
{
    for (const auto& subsegment : _subsegments) {
        const auto state = subsegment.get_state(id);
        if (state) { return state; }
    }
    return std::nullopt;
}

OptionalRef<State> Segment::get_state(std::size_t id)
{
    for (auto& subsegment : _subsegments) {
        auto state = subsegment.get_state(id);
        if (state) { return state; }
    }
    return std::nullopt;
}

} // namespace hermes
} // namespace astrea