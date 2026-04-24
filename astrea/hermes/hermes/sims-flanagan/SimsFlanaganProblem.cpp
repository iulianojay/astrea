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

#include <hermes/sims-flanagan/SimsFlanaganProblem.hpp>

namespace astrea {
namespace hermes {

using pamgo::vector_double;


std::string SimsFlanaganProblem::get_name() const { return "Sims-Flanagan Problem"; }

vector_double::size_type SimsFlanaganProblem::get_nic() const { return 0; }

vector_double::size_type SimsFlanaganProblem::get_nobj() const { return 1; }

std::pair<vector_double, vector_double> SimsFlanaganProblem::get_bounds() const
{
    const vector_double lb{ 0.0 };
    const vector_double ub{ 1e6 };
    return { lb, ub };
}

vector_double SimsFlanaganProblem::fitness(const vector_double&) const {}

} // namespace hermes
} // namespace astrea