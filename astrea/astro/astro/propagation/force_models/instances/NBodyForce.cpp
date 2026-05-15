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

#include <astro/propagation/force_models/instances/NBodyForce.hpp>

#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_utilities>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;

using mp_units::pow;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

Perturbation NBodyForce::compute_perturbation(const State& state, const Vehicle& vehicle) const
{
    if (frames::primary::axis != axes::icrf) {
        throw std::runtime_error("NBodyForce only works in ICRF frames right now.");
    }

    // Extract
    const Date date                                       = state.get_epoch();
    const RadiusVector<frames::primary>& rCenterToVehicle = state.get_position();

    // Center body properties
    const CelestialBodyId center = sys.get_central_body_id();

    // Reset perturbation
    AccelerationVector<frames::primary> accelNBody{ 0.0 * km / (s * s) };
    for (const auto& [id, body] : sys) {

        if (id == center) { continue; }

        // Find center to nth body and spacecraft to nth body
        // NOTE: The forced frame conversion here is fine since it's just a relative translation, no rotation or velocity
        const RadiusVector<frames::primary> rCenterToNbody =
            sys.get_relative_position<body, frames::primary::origin>(date).force_frame_conversion<frames::primary>();
        const RadiusVector<frames::primary> rVehicleToNbody = rCenterToNbody - rCenterToVehicle;

        // Normalize
        const Distance rMagVehicleToNbody = rVehicleToNbody.norm();
        const Distance rMagCenterToNbody  = rCenterToNbody.norm();

        // Perturbational force from nth body
        const GravParam mu                 = body->get_mu();
        const quantity directCoefficient   = mu / pow<3>(rMagVehicleToNbody);
        const quantity indirectCoefficient = mu / pow<3>(rMagCenterToNbody);

        accelNBody += directCoefficient * rVehicleToNbody - indirectCoefficient * rCenterToNbody;
    }

    return { .force = accelNBody * vehicle.get_mass() };
}

} // namespace astro
} // namespace astrea