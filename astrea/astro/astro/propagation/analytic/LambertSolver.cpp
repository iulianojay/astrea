/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/analytic/LambertSolver.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <numbers>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::si;
using mp_units::si::unit_symbols::rad;

std::pair<Unitless, Unitless> LambertSolver::evaluate_stumpff(const Unitless& z)
{
    using namespace math;
    if (z > 0.0 * one) {
        const Unitless sqz = sqrt(z);
        const Unitless Cz  = (1.0 - cos(sqz * rad)) / z;
        const Unitless Sz  = (sqz - sin(sqz * rad)) / (sqz * sqz * sqz);
        return { Cz, Sz };
    }
    else if (z < 0.0 * one) {
        const Unitless sqnz = sqrt(-z);
        const Unitless Cz   = (1.0 - cosh(sqnz * rad)) / z;
        const Unitless Sz   = (sinh(sqnz * rad) - sqnz) / (sqnz * sqnz * sqnz);
        return { Cz, Sz };
    }

    const Unitless Cz = 0.5 * one;
    const Unitless Sz = 1.0 / 6.0 * one;
    return { Cz, Sz };
}

} // namespace astro
} // namespace astrea