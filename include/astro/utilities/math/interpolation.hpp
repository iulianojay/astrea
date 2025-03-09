#pragma once

#ifndef SWIG
    #include <vector>
#endif

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include "Time.hpp"

template<typename X_Type, typename Y_Type>
Y_Type interpolate(const std::vector<X_Type>& x, const std::vector<Y_Type>& y, const X_Type& sx) {

    const X_Type& xi = x[0];
    const X_Type& xf = x[x.size()-1];
    if (sx < xi || sx > xf) {
        throw std::runtime_error("Asked for interpolation outside of dataset bounds.");
    }
    if (sx == xi) { return y[0]; }
    if (sx == xf) { return y[x.size()-1]; }

    // Find indexes
    const size_t idx = std::distance(x.begin(), std::lower_bound(x.begin(), x.end(), sx));

    const X_Type& x0 = x[idx];
    const X_Type& x1 = x[idx+1];
    const Y_Type& y0 = y[idx];
    const Y_Type& y1 = y[idx+1];

    if (sx == x0) { return y0; }

    return y0 + (sx - x0)*(y1 - y0)/(x1 - x0);
}

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);