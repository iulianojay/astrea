/**
 * @file Subsegment.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Subsegment module
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

#include <astro/astro.hpp>
#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/model/Node.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

class Subsegment {
  public:
    Subsegment() = default;

    Subsegment(const Node& initialNode, const Node& finalNode = {});

    ~Subsegment() = default;

    static Subsegment ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& timeOfFlight);

    std::size_t get_id() const;

    void set_initial_node(const Node& node);

    void set_final_node(const Node& node);

    const Node& get_initial_node() const;

    const Node& get_final_node() const;

    const Time& get_time_of_flight() const;

    const State& get_initial_state() const;

    const State& get_final_state() const;

    OptionalRef<const Node> get_node(std::size_t id) const;

    OptionalRef<Node> get_node(std::size_t id);

    OptionalRef<const State> get_state(std::size_t id) const;

    OptionalRef<State> get_state(std::size_t id);

  private:
    std::size_t _id;
    Node _initialNode;
    Node _finalNode;
};

} // namespace hermes
} // namespace astrea