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

#include <hermes/sims-flanagan/model/Segment.hpp>

namespace astrea {
namespace hermes {

Segment::Segment(const std::vector<Subsegment>& subsegments, const std::vector<DeltaV>& burns, const Time& duration, bool isForward) :
    _subsegments(subsegments),
    _burns(burns),
    _isForward(isForward),
    _duration(duration)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();
}

Segment::Segment(const SegmentSettings& settings)
{
    _id = utilities::IdProvider::get_next_id<"SimsFlanagan">();

    _isForward = settings.isForward;
    _burns     = settings.subsegBurns;
    _duration  = settings.duration;

    const Node startingNode = Node(settings.initialState);
    _subsegments.resize(settings.nSubsegments, Node());
    if (_isForward) { _subsegments.front().set_initial_node(startingNode); }
    else {
        _subsegments.back().set_final_node(startingNode);
    }
    for (auto& subsegment : _subsegments) {
        subsegment.set_direction(_isForward);
    }
}

Segment Segment::ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& segmentTime, std::size_t nSubsegments)
{
    const Time timeOfFlight = segmentTime / nSubsegments;

    std::vector<Subsegment> subsegments;
    subsegments.reserve(nSubsegments);

    State subsegmentState = initialState;
    for (std::size_t ii = 0; ii < nSubsegments; ++ii) {
        const Subsegment subsegment = Subsegment::ballistic(integrator, vehicle, subsegmentState, timeOfFlight);
        subsegmentState             = subsegment.get_final_state();
        subsegments.emplace_back(subsegment);
    }

    const Segment segment(subsegments);
    return Segment(subsegments, {}, segmentTime, true);
}

astro::StateHistory
    Segment::propagate(astro::Integrator& integrator, astro::Vehicle& vehicle, const DeltaV& initialBurn, const DeltaV& finalBurn, bool store)
{
    if (_subsegments.empty()) { throw std::runtime_error("Segment has no subsegments to propagate."); }
    else if (mp_units::abs(_duration) <= 1.0 * mp_units::si::unit_symbols::ms) {
        throw std::runtime_error("Segment has zero duration.");
    }

    static const DeltaV zeroBurn{};
    astro::StateHistory history;
    const Time timeOfFlight = _duration / _subsegments.size();
    const std::size_t N     = _subsegments.size();

    // Seed from the optimizer-controlled entry node (forward) or exit node (backward).
    State currentState = _isForward ? _subsegments.front().get_initial_node().get_state_in() :
                                      _subsegments.back().get_final_node().get_state_out();

    for (std::size_t step = 0; step < N; ++step) {
        // Iterate forward 0..N-1 or backward N-1..0
        const std::size_t ii = _isForward ? step : (N - 1 - step);
        auto& subsegment     = _subsegments[ii];

        const DeltaV& iBurn = (ii == 0) ? initialBurn : (ii - 1 < _burns.size() ? _burns[ii - 1] : zeroBurn);
        const DeltaV& fBurn = (ii + 1 == N) ? finalBurn : (ii < _burns.size() ? _burns[ii] : zeroBurn);

        const auto subsegmentHistory = subsegment.propagate(integrator, vehicle, currentState, timeOfFlight, iBurn, fBurn, store);
        if (store) { history.insert(subsegmentHistory); }

        // Chain: next subsegment inherits from the physical propagation result (pre-burn)
        currentState = _isForward ? subsegment.get_final_node().get_state_out() : subsegment.get_initial_node().get_state_in();
    }
    return history;
}

std::size_t Segment::get_id() const { return _id; }

const std::vector<Subsegment>& Segment::get_subsegments() const { return _subsegments; }

const Time& Segment::get_duration() const { return _duration; }

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

const std::vector<DeltaV>& Segment::get_burns() const { return _burns; }

bool Segment::is_forward() const { return _isForward; }

} // namespace hermes
} // namespace astrea