#pragma once

#include <array>
#include <stdint.h>

#include <astro/units/units.hpp>

namespace astro {

using ElementArray = std::array<double, 6>;
using BasisArray   = std::array<double, 3>;
using Basis        = std::array<BasisArray, 3>;

using EnumType = uint32_t;

using RadiusVector       = std::array<Distance, 3>;
using VelocityVector     = std::array<Velocity, 3>;
using AccelerationVector = std::array<Acceleration, 3>;

} // namespace astro