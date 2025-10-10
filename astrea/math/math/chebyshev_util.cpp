/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <math/chebyshev_util.hpp>

namespace astrea {
namespace math {

double transform_from_chebyshev_range(const double& x, const double& lb, const double& ub)
{
    return x * 0.5 * (ub - lb) + 0.5 * (ub + lb);
}

double transform_to_chebyshev_range(const double& x, const double& lb, const double& ub)
{
    return (x - 0.5 * (ub + lb)) / (0.5 * (ub - lb));
}

} // namespace math
} // namespace astrea
