#pragma once

#include <array>
#include <stdint.h>

using ElementArray = std::array<double, 6>;
using BasisArray   = std::array<double, 3>;
using Basis        = std::array<BasisArray, 3>;

using EnumType = uint32_t;
