#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include "Time.hpp"


double interpolate(const std::vector<double>& x, const std::vector<double>& y, const double& sx);

std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);