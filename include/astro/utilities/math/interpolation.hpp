#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include "Time.hpp"


double interpolate(const std::vector<Time>& x, const std::vector<double>& y, const Time& sx);

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);