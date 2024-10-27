#pragma once

#include <vector>

#include "Time.hpp"


std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx);