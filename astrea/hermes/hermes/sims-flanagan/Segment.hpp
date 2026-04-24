/**
 * @file Segment.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Segment module
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

#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/DeltaV.hpp>
#include <hermes/sims-flanagan/State.hpp>
#include <hermes/sims-flanagan/Subsegment.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

class Segment {
  public:
    Segment(const std::vector<Subsegment>& subsegments = {});
    ~Segment() = default;

    static Segment
        ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& segmentTime, std::size_t nSubsegments);

    std::size_t get_id() const;

    const std::vector<Subsegment>& get_subsegments() const;

    const State& get_initial_state() const;

    const State& get_final_state() const;

    OptionalRef<const Subsegment> get_subsegment(std::size_t id) const;

    OptionalRef<Subsegment> get_subsegment(std::size_t id);

    OptionalRef<const Node> get_node(std::size_t id) const;

    OptionalRef<Node> get_node(std::size_t id);

    OptionalRef<const State> get_state(std::size_t id) const;

    OptionalRef<State> get_state(std::size_t id);

  private:
    std::size_t _id;
    std::vector<Subsegment> _subsegments;
    std::vector<DeltaV> _burns;
};

} // namespace hermes
} // namespace astrea