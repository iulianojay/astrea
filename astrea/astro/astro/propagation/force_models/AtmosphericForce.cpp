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

#include <astro/propagation/force_models/AtmosphericForce.hpp>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


AccelerationVector<frames::earth::icrf>
    AtmosphericForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_central_body();

    // Extract
    const RadiusVector<frames::earth::icrf>& r   = state.get_position();
    const VelocityVector<frames::earth::icrf>& v = state.get_velocity();

    const Distance& x = r.get_x();
    const Distance& y = r.get_y();
    const Distance& R = r.norm();

    const Velocity& vx = v.get_x();
    const Velocity& vy = v.get_y();
    const Velocity& vz = v.get_z();

    // Central body properties
    static const AngularRate& bodyRotationRate = center->get_rotation_rate();

    // Find velocity relative to atmosphere
    const VelocityVector<frames::earth::icrf> relVelocity = { vx + y * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle),
                                                              vy - x * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle),
                                                              vz };

    // Exponential Drag Model
    const Density atmosphericDensity = find_atmospheric_density(date, state, center);

    // Accel due to drag
    const Velocity relativeVelocityMagnitude = relVelocity.norm();
    const Unitless coefficientOfDrag         = vehicle.get_coefficient_of_drag();
    const SurfaceArea areaRam                = vehicle.get_ram_area();
    const Mass mass                          = vehicle.get_mass();
    const UnitlessPerTime dragTerm = -0.5 * coefficientOfDrag * (areaRam) / mass * atmosphericDensity * relativeVelocityMagnitude;

    const AccelerationVector<frames::earth::icrf> accelDrag = dragTerm * relVelocity;

    // Velocity in the radial direction
    const quantity radialVelocityMagnitude = r.dot(v) / R;

    // accel due to lift
    const Unitless coefficientOfLift         = vehicle.get_coefficient_of_lift();
    const SurfaceArea areaLift               = vehicle.get_lift_area();
    const quantity<one / pow<2>(s)> liftTerm = 0.5 * coefficientOfLift * areaLift / mass * atmosphericDensity *
                                               radialVelocityMagnitude * radialVelocityMagnitude / R;

    const AccelerationVector<frames::earth::icrf> accelLift = liftTerm * r;

    return { accelDrag[0] + accelLift[0], accelDrag[1] + accelLift[1], accelDrag[2] + accelLift[2] };
}


const Density AtmosphericForce::find_atmospheric_density(const Date& date, const Cartesian& state, const CelestialBodyUniquePtr& center) const
{
    // Central body properties
    static const Distance equitorialR = center->get_equitorial_radius();
    static const Distance polarR      = center->get_polar_radius();

    // Find altitude
    const RadiusVector<frames::earth::earth_fixed> rEcef = state.get_position().in_frame<frames::earth::earth_fixed>(date);
    const auto [latitude, longitude, altitude] =
        convert_earth_fixed_to_geodetic(rEcef, center->get_equitorial_radius(), center->get_polar_radius());

    return center->find_atmospheric_density(date, altitude);
}


} // namespace astro
} // namespace astrea