/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>

#include <optional>

#include <mp-units/systems/angular.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/attitude/Attitude.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

using namespace mp_units;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

EquationsOfMotion::EquationsOfMotion(const ForceModel& forces) :
    forces(&forces)
{
}

StatePartial EquationsOfMotion::operator()(const State& state, const Vehicle& vehicle) const
{
    // Find forces and torques caused by perturbations
    const Perturbation perts = forces ? forces->compute_perturbations(state, vehicle) : Perturbation();

    // Get vehicle-produced forces and torques
    const Perturbation control = vehicle.get_control_authority(state);

    // Get dynamics
    const OrbitalElementPartials dynamics = compute_dynamics(state, vehicle, perts.force, control.force);

    // Get kinematics
    const std::optional<AttitudePartials> kinematics =
        state.get_attitude().has_value() ?
            std::optional<AttitudePartials>(compute_kinematics(state, vehicle, perts.torque, control.torque)) :
            std::nullopt;

    return StatePartial(state.get_epoch(), dynamics, kinematics);
}

AttitudePartials EquationsOfMotion::compute_kinematics(
    const State& state,
    const Vehicle& vehicle,
    const TorqueVector<frames::primary>& perts,
    const TorqueVector<frames::primary>& control
) const
{
    // Has value is guaranteed by caller before calling compute_kinematics
    const Attitude& attitude                                  = state.get_attitude().value();
    const BodyQuaternion& q                                   = attitude.get_orientation();
    const BodyAngleVelocities& w                              = attitude.get_angular_velocity();
    const InertiaTensor<frames::dynamic::body>& inertiaTensor = vehicle.get_inertia_tensor();

    // Compute angular acceleration
    const DCM<frames::primary, frames::dynamic::body> dcm    = q.to_dcm().transpose();
    const TorqueVector<frames::dynamic::body> externalTorque = dcm * (perts + control);
    const BodyAngularAcceleration angularAcceleration =
        inertiaTensor.inverse_multiply(externalTorque - w.cross(inertiaTensor * w) / pow<2>(rad)) * rad;

    // Compute quaternion rate
    const Unitless& s                         = q.get_scalar_part();
    const Direction<frames::dynamic::body>& u = q.get_vector_part();
    const BodyQuaternionRate quaternionRate{ 0.5 * w.dot(u) / rad, 0.5 * (w * s - w.cross(u)) / rad };

    return AttitudePartials(quaternionRate, angularAcceleration);
}

StateTransitionMatrix EquationsOfMotion::compute_stm(const State& state, const Vehicle& vehicle) const
{
    // Default to numerical STM using finite differences if not overridden by the specific equations of motion implementation
    return StateTransitionMatrix(*this, state, vehicle);
}

} // namespace astro
} // namespace astrea
