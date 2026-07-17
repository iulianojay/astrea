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

#include <astro/propagation/equations_of_motion/CircularRestrictedThreeBodyProblem.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using si::unit_symbols::Hz;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

using frames::earth::icrf;
using frames::earth_moon_barycenter::ems;

CircularRestrictedThreeBodyProblem::CircularRestrictedThreeBodyProblem(const ForceModel& forces) :
    EquationsOfMotion(forces)
{
}

OrbitalElementPartials CircularRestrictedThreeBodyProblem::compute_dynamics(
    const State& state,
    const Vehicle& vehicle,
    const ForceVector<primary>& perts,
    const ForceVector<primary>& control
) const
{
    // Extract
    const GravParam mu1 = get_mu<planets::Earth>();
    const GravParam mu2 = get_mu<moons::Moon>();
    const GravParam mu  = mu1 + mu2;

    const Unitless mRatio1 = mu1 / mu;
    const Unitless mRatio2 = mu2 / mu;

    const Date date = state.get_epoch();

    const RadiusVector<primary> r   = state.get_position();
    const VelocityVector<primary> v = state.get_velocity();

    const Distance x = r[0];
    const Distance y = r[1];
    const Distance z = r[2];

    const Velocity vx = v[0];
    const Velocity vy = v[1];
    const Velocity vz = v[2];

    // Compute positions
    const RadiusVector<ems> r1 = get_relative_position<planets::Earth, barycenters::EarthMoonBarycenter>(date);
    const RadiusVector<ems> r2 = get_relative_position<moons::Moon, barycenters::EarthMoonBarycenter>(date);
    const auto r12             = r2 - r1;
    const Distance R12         = r12.norm();

    const auto r1s = r - r1;
    const auto R1s = r1s.norm();
    const auto r2s = r - r2;
    const auto R2s = r2s.norm();

    // Common terms
    const quantity<pow<2>(Hz)> omegaSq = mu / pow<3>(R12);
    const quantity<Hz> omega           = sqrt(omegaSq);
    const quantity<pow<2>(Hz)> coef    = -mu1 / pow<3>(R1s) * r1s - mu2 / pow<3>(R2s) * r2s;

    // Accel
    const AccelerationVector<ems> a = { 2 * omega * vy + (omegaSq + coef) * x - mu1 * mRatio2 * R12 / pow<3>(R1s) +
                                            mu2 * mRatio1 * R12 / pow<3>(R2s),
                                        -2 * omega * vx + (omegaSq + coef) * y,
                                        coef * z };

    // Derivative
    return { CartesianPartial<primary>{ v, a.in_frame<primary>(date) } };
}

} // namespace astro
} // namespace astrea