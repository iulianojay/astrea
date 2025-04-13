#pragma once

#include <array>

#include <mp-units/systems/si.h>

using ElementArray = std::array<double, 6>;
using BasisArray   = std::array<double, 3>;
using Basis        = std::array<BasisArray, 3>;

using EnumType = uint32_t;


using RadiusVector   = std::array<mp_units::quantity<mp_units::si::unit_symbols::km>, 3>;
using VelocityVector = std::array<mp_units::quantity<mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s>, 3>;
using AccelerationVector =
    std::array<mp_units::quantity<mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s)>, 3>;