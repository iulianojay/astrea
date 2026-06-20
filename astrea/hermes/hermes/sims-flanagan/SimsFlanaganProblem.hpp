/**
 * @file SimsFlanaganProblem.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Sims-Flanagan problem module
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

#include <pagmo/problem.hpp>
#include <pagmo/types.hpp>

#include <hermes/sims-flanagan/model/DeltaV.hpp>
#include <hermes/sims-flanagan/model/Segment.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

class SimsFlanaganProblem {
  public:
    SimsFlanaganProblem()  = default;
    ~SimsFlanaganProblem() = default;

    pamgo::vector_double::size_type get_nic() const;

    pamgo::vector_double::size_type get_nobj() const;

    std::pair<pamgo::vector_double, pamgo::vector_double> get_bounds() const;

    pamgo::vector_double fitness(const pamgo::vector_double&) const;

    std::string get_name() const;
};

} // namespace hermes
} // namespace astrea