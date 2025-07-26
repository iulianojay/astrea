#pragma once

#include <array>
#include <stdint.h>

#include <astro/astro.fwd.hpp>

namespace waveguide {
namespace astro {

using ElementArray = std::array<double, 6>;
using BasisArray   = std::array<double, 3>;
using Basis        = std::array<BasisArray, 3>;

using EnumType = uint32_t;

} // namespace astro
} // namespace waveguide
