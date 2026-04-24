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

#include <hermes/sims-flanagan/Subsegment.hpp>

namespace astrea {
namespace hermes {

class Segment {
  public:
    Segment()  = default;
    ~Segment() = default;

    Segment(const std::vector<Subsegment>& subsegments) :
        _subsegments(subsegments)
    {
        _id = utilities::IdProvider::get_next_id<"Segment">();
    }

    static Segment
        ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const astro::State& initialState, const Time& segmentTime, std::size_t nSubsegments);

    std::size_t get_id() const { return _id; }

    const std::vector<Subsegment>& get_subsegments() const { return _subsegments; }

    const astro::State& get_initial_state() const { return _subsegments.front().get_initial_state(); }
    const astro::State& get_final_state() const { return _subsegments.back().get_final_state(); }

  private:
    std::size_t _id;
    std::vector<Subsegment> _subsegments;
};

} // namespace hermes
} // namespace astrea