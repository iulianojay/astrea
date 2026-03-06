

# File interpolation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**math**](dir_450de47f4bf9646ba641743528a4ea64.md) **>** [**math**](dir_b2ecf34ed687fe8e79818a2ecae6cd69.md) **>** [**interpolation.hpp**](interpolation_8hpp.md)

[Go to the documentation of this file](interpolation_8hpp.md)


```C++

#pragma once

#include <array>
#include <stdexcept>
#include <vector>

namespace astrea {
namespace math {

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
```


