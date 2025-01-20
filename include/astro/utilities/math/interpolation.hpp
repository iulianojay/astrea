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

template<auto R, typename Rep>
mp_units::quantity<R, Rep> interpolate(const std::vector<Time>& x, const std::vector<mp_units::quantity<R, Rep>>& y, const Time& sx);

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);