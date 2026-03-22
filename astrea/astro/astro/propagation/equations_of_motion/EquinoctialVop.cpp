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

#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

EquinoctialVop::EquinoctialVop(const ForceModel& forces) :
    forces(&forces)
{
}

OrbitalElementPartials EquinoctialVop::operator()(const State& state, const Vehicle& vehicle) const
{
    // Get need representations
    const auto mu                 = state.get_system().get_mu();
    const Date& date              = state.get_epoch();
    const Equinoctial equinoctial = state.in_element_set<Equinoctial>();

    // Extract
    const Distance& p = equinoctial.get_semilatus();
    const Unitless& f = equinoctial.get_f();
    const Unitless& g = equinoctial.get_g();
    const Unitless& h = equinoctial.get_h();
    const Unitless& k = equinoctial.get_k();
    const Angle& L    = equinoctial.get_true_longitude();

    // R and V
    const RadiusVector<frames::earth::icrf> r   = state.get_position();
    const VelocityVector<frames::earth::icrf> v = state.get_velocity();

    // Function for finding accel caused by perturbations
    const auto [forcePerts, torquePerts] = forces->compute_perturbations(state, vehicle);

    // Get vehicle-produced forces and torques
    const auto [forceVehicle, torqueVehicle] = vehicle.get_control_authority(state);

    // Calculate R, N, and T
    const frames::dynamic::ric ricFrame = frames::dynamic::ric::instantaneous(r, v);
    const AccelerationVector<frames::dynamic::ric> accelRic =
        ricFrame.rotate_into_this_frame((forcePerts + forceVehicle) / vehicle.get_mass(), date);

    const Acceleration& radialPert     = accelRic.get_x();
    const Acceleration& tangentialPert = accelRic.get_y();
    const Acceleration& normalPert     = accelRic.get_z();

    // Variables precalculated for speed
    const Unitless cosL = cos(L);
    const Unitless sinL = sin(L);

    const quantity sqPOverMu = sqrt(p / mu);
    const quantity w         = 1.0 + f * cosL + g * sinL;
    const quantity sSq       = 1.0 + h * h + k * k;

    // Common terms
    const quantity termA = (h * sinL - k * cosL) / w * normalPert;
    const quantity termB = sqPOverMu * sSq / (2.0 * w);

    // Derivative functions
    const Velocity dpdt = 2.0 * p / w * sqPOverMu * tangentialPert;
    const UnitlessPerTime dfdt = sqPOverMu * (radialPert * sinL + ((w + 1) * cosL + f) / w * tangentialPert - g * termA);
    const UnitlessPerTime dgdt = sqPOverMu * (-radialPert * cosL + ((w + 1) * sinL + g) / w * tangentialPert + g * termA); // TODO: My notes say: 'f * termA'. Find a second source
    const UnitlessPerTime dhdt = termB * cosL * normalPert;
    const UnitlessPerTime dkdt = termB * sinL * normalPert;
    const AngularRate dLdt     = (sqrt(mu * p) * w * w / (p * p) + sqPOverMu * termA) * (isq_angle::cotes_angle);

    return EquinoctialPartial(dpdt, dfdt, dgdt, dhdt, dkdt, dLdt);
}


StateTransitionMatrix EquinoctialVop::compute_stm(const State& state, const Vehicle& vehicle) const
{
    return StateTransitionMatrix(*this, state, vehicle);
}

} // namespace astro
} // namespace astrea