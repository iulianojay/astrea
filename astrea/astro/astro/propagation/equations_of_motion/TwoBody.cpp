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

#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::si;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

TwoBody::TwoBody(const AstrodynamicsSystem& system) :
    EquationsOfMotion(system),
    mu(system.get_mu())
{
}

OrbitalElementPartials TwoBody::operator()(const Date& date, const OrbitalElements& state, const Vehicle& vehicle) const
{
    // Extract
    const Cartesian cartesian = state.in_element_set<Cartesian>(mu);

    const RadiusVector<frames::earth::icrf> r   = cartesian.get_position();
    const VelocityVector<frames::earth::icrf> v = cartesian.get_velocity();

    // mu/R^3
    const Distance R                 = r.norm();
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    return CartesianPartial(v, -muOverRadiusCubed * r);
}

} // namespace astro
} // namespace astrea