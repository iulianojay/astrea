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

#include <astro/propagation/force_models/instances/AtmosphericForce.hpp>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::pow;
using mp_units::angular::atan2;
using mp_units::angular::sin;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


Perturbation AtmosphericForce::compute_perturbation(const State& state, const Vehicle& vehicle) const
{
    // Extract
    static constexpr auto center            = frames::primary.origin;
    const AngularVelocity& bodyRotationRate = get_rotation_rate<center>();

    const RadiusVector<frames::primary>& r   = state.get_position();
    const VelocityVector<frames::primary>& v = state.get_velocity();

    const Distance& x = r.get_x();
    const Distance& y = r.get_y();
    const Distance R  = r.norm();

    const Velocity& vx = v.get_x();
    const Velocity& vy = v.get_y();
    const Velocity& vz = v.get_z();

    // Find velocity relative to atmosphere
    const VelocityVector<frames::primary> relVelocity = { vx + y * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle),
                                                          vy - x * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle),
                                                          vz };

    // Exponential Drag Model
    const Density atmosphericDensity = find_atmospheric_density<center>(state);

    // Accel due to drag
    const Velocity relVelMag         = relVelocity.norm();
    const Unitless coefficientOfDrag = vehicle.get_coefficient_of_drag();
    const SurfaceArea areaRam        = vehicle.get_ram_area();
    const Force dragForceMag         = -0.5 * coefficientOfDrag * areaRam * atmosphericDensity * pow<2>(relVelMag);

    const ForceVector<frames::primary> forceDrag = dragForceMag * (relVelocity / relVelMag);

    // accel due to lift
    const Angle angleOfAttack        = atan2(relVelocity.get_z(), relVelocity.get_x());
    const Unitless coefficientOfLift = vehicle.get_coefficient_of_lift();
    const SurfaceArea areaLift       = vehicle.get_lift_area();
    const Force liftForceMag = 0.5 * coefficientOfLift * areaLift * atmosphericDensity * pow<2>(relVelMag) * sin(angleOfAttack);
    const ForceVector<frames::primary> forceLift = liftForceMag * (r / R); // just assume radial lift for now

    return { .force = forceDrag + forceLift };
};


} // namespace astro
} // namespace astrea