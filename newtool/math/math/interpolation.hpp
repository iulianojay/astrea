#pragma once

#ifndef SWIG
#include <stdexcept>
#include <vector>

#endif

namespace math {

template <typename X, typename Y>
Y interpolate(const std::vector<X>& x, const std::vector<Y>& y, const X& sx)
{

    const X& xi = x[0];
    const X& xf = x[x.size() - 1];
    if (sx < xi || sx > xf) { throw std::runtime_error("Asked for interpolation outside of dataset bounds."); }
    if (sx == xi) { return y[0]; }
    if (sx == xf) { return y[x.size() - 1]; }

    // Find indexes
    const size_t idx = std::distance(x.begin(), std::lower_bound(x.begin(), x.end(), sx));

    const X& x0 = x[idx];
    const X& x1 = x[idx + 1];
    const Y& y0 = y[idx];
    const Y& y1 = y[idx + 1];

    if (sx == x0) { return y0; }

    return y0 + (sx - x0) * (y1 - y0) / (x1 - x0);
}

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);

} // namespace math