#pragma once

#include <stdexcept>
#include <vector>

namespace waveguide {
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

    if (idx >= x.size() - 1 || idx >= y.size() - 1) {
        throw std::runtime_error("Internal Error: Interpolation index outside of input vector sizes.");
    }

    const X& x0 = x[idx];
    const X& x1 = x[idx + 1];
    const Y& y0 = y[idx];
    const Y& y1 = y[idx + 1];

    if (sx == x0) { return y0; }
    else if (sx == x1) {
        return y1;
    }

    return y0 + (sx - x0) * (y1 - y0) / (x1 - x0);
}

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);

} // namespace math
} // namespace waveguide