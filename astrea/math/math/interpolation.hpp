/**
 * @file interpolation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Interpolation functions for numerical data.
 * @date 2025-10-09
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <array>
#include <stdexcept>
#include <vector>

namespace astrea {
namespace math {

/**
 * @brief Linear interpolation for a single point, with bounds checking.
 *
 * @tparam X Type of the x values (e.g. time).
 * @tparam Y Type of the y values (e.g. distance, angle). Must support arithmetic operations.
 * @param x Vector of x values corresponding to the y values. Must be in ascending order.
 * @param y Vector of y values corresponding to the x values.
 * @param sx The x value to interpolate at. Must be between x[0] and x.back().
 * @return Y The interpolated y value at sx.
 * @throws std::runtime_error if sx is outside the bounds of x.
 */
template <typename X, typename Y>
inline Y interpolate(const std::vector<X>& x, const std::vector<Y>& y, const X& sx)
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

    return y0 + (sx - x0) * (y1 - y0) / (x1 - x0);
}

/**
 * @brief Fast linear interpolation for two points, with bounds checking.
 *
 * @tparam X Type of the x values (e.g. time).
 * @tparam Y Type of the y values (e.g. distance, angle). Must support arithmetic operations.
 * @param x Two x values corresponding to the y values. Must be in ascending order.
 * @param y Two y values corresponding to the x values.
 * @param sx The x value to interpolate at. Must be between x[0] and x[1].
 * @return Y The interpolated y value at sx.
 * @throws std::runtime_error if sx is outside the bounds of x.
 */
template <typename X, typename Y>
inline Y fast_interpolate(const std::array<X, 2>& x, const std::array<Y, 2>& y, const X& sx)
{
    const X& x0 = x[0];
    const X& x1 = x[1];
    const Y& y0 = y[0];
    const Y& y1 = y[1];

    if (sx < x0 || sx > x1) { throw std::runtime_error("Asked for interpolation outside of dataset bounds."); }
    if (sx == x0) { return y0; }
    if (sx == x1) { return y1; }

    return y0 + (sx - x0) * (y1 - y0) / (x1 - x0);
}

// TDOD: Fix UB somewhere in spline or just get rid of spline.
// std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);

} // namespace math
} // namespace astrea