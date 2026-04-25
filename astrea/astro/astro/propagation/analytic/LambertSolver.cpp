/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
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
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::rad;

std::pair<Unitless, Unitless> LambertSolver::evaluate_stumpff(const Unitless& z)
{
    using namespace math;
    if (z > 0.0 * one) {
        const Unitless sqz = sqrt(z);
        const Unitless Cz  = (1.0 - cos(sqz * isq_angle::cotes_angle)) / z;
        const Unitless Sz  = (sqz - sin(sqz * isq_angle::cotes_angle)) / (sqz * sqz * sqz);
        return { Cz, Sz };
    }
    else if (z < 0.0 * one) {
        const Unitless sqnz = sqrt(-z);
        const Unitless Cz   = (1.0 - cosh(sqnz * isq_angle::cotes_angle)) / z;
        const Unitless Sz   = (sinh(sqnz * isq_angle::cotes_angle) - sqnz) / (sqnz * sqnz * sqnz);
        return { Cz, Sz };
    }

    const Unitless Cz = 0.5 * one;
    const Unitless Sz = 1.0 / 6.0 * one;
    return { Cz, Sz };
}

} // namespace astro
} // namespace astrea