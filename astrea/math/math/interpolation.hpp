/**
 * @file interpolation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Interpolation functions for numerical data.
 * @date 2025-10-09
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

#include <stdexcept>
#include <vector>

namespace astrea {
namespace math {

template <typename X, typename Y>
Y interpolate(const std::vector<X>& x, const std::vector<Y>& y, const X& sx)
{
    if (x.size() != y.size()) { throw std::runtime_error("Input vectors must have the same size for interpolation."); }

    const X& xi = x[0];
    const X& xf = x[x.size() - 1];
    if (sx < xi || sx > xf) { throw std::runtime_error("Asked for interpolation outside of dataset bounds."); }
    if (sx == xi) { return y[0]; }
    if (sx == xf) { return y[x.size() - 1]; }

    // Find indexes
    const size_t idx = std::distance(x.begin(), std::lower_bound(x.begin(), x.end(), sx)) - 1;

    // Get nearest points
    const X& x0 = x[idx];
    const X& x1 = x[idx + 1];
    const Y& y0 = y[idx];
    const Y& y1 = y[idx + 1];

    if (sx == x0) { return y0; }
    // else if (sx == x1) { // This can't happen due to the way idx is found
    //     return y1;
    // }

    return y0 + (sx - x0) * (y1 - y0) / (x1 - x0);
}

// TDOD: Fix UB somewhere in spline or just get rid of spline.
// std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);

} // namespace math
} // namespace astrea