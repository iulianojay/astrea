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
#include <astro/propagation/equations_of_motion/state_transition_matrix/StateTransitionMatrix.hpp>
#include <astro/propagation/equations_of_motion/state_transition_matrix/instances/CartesianStm.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;

using mp_units::pow;

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
    const Distance R        = r.norm();
    const quantity muOverR3 = mu / pow<3>(R);

    // Derivative
    return CartesianPartial(v, -muOverR3 * r);
}


StateTransitionMatrix TwoBody::compute_stm(const OrbitalElements& state, const Vehicle& vehicle) const
{
    /*
        |   0       0       0        1        0        0    |
        |   0       0       0        0        1        0    |
        |   0       0       0        0        0        1    |
        | dax/dx  dax/dy  dax/dz     0        0        0    |
        | day/dx  day/dy  day/dz     0        0        0    |
        | daz/dx  daz/dy  daz/dz     0        0        0    |

        a = -mu/r^3 * r

        ax = -mu*x/r^3
        ay = -mu*y/r^3
        az = -mu*z/r^3

        dax/dx = -mu/r^3 + 3*mu*x^2/r^5
        dax/dy = 3*mu*x*y/r^5
        dax/dz = 3*mu*x*z/r^5
    */
    const Cartesian cartesian = state.in_element_set<Cartesian>(mu);

    const auto r = cartesian.get_position();
    const auto x = r[0];
    const auto y = r[1];
    const auto z = r[2];
    const auto R = r.norm();

    quantity muOverR3      = mu / pow<3>(R);
    quantity threeMuOverR5 = 3 * mu / pow<5>(R);

    StateTransitionMatrix stm;

    stm.set<0, 3>(1.0 * one);
    stm.set<1, 4>(1.0 * one);
    stm.set<2, 5>(1.0 * one);

    stm.set<3, 0>(-muOverR3 + threeMuOverR5 * x * x);
    stm.set<3, 1>(threeMuOverR5 * x * y);
    stm.set<3, 2>(threeMuOverR5 * x * z);

    stm.set<4, 0>(threeMuOverR5 * y * x);
    stm.set<4, 1>(-muOverR3 + threeMuOverR5 * y * y);
    stm.set<4, 2>(threeMuOverR5 * y * z);

    stm.set<5, 0>(threeMuOverR5 * z * x);
    stm.set<5, 1>(threeMuOverR5 * z * y);
    stm.set<5, 2>(-muOverR3 + threeMuOverR5 * z * z);

    return stm;
}

} // namespace astro
} // namespace astrea