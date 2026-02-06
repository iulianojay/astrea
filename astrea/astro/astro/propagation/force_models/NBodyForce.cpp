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

#include <astro/propagation/force_models/NBodyForce.hpp>

#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;

using mp_units::pow;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

AccelerationVector<frames::earth::icrf> NBodyForce::compute_force(const State& state, const Vehicle& vehicle) const
{
    // Extract
    const AstrodynamicsSystem& sys                            = state.get_system();
    const Date date                                           = state.get_epoch();
    const RadiusVector<frames::earth::icrf>& rCenterToVehicle = state.get_position();

    // Center body properties
    static const CelestialBodyUniquePtr& center = sys.get_central_body();

    // Find day nearest to current time
    const RadiusVector<frames::solar_system_barycenter::icrf> rCenterToSsb = -center->get_position_at(date);

    // Reset perturbation
    AccelerationVector<frames::earth::icrf> accelNBody{ 0.0 * astrea::detail::distance_unit / pow<2>(astrea::detail::time_unit) };
    for (const auto& [id, body] : sys) {

        if (body->get_name() == center->get_name()) { continue; }

        // Find center to nth body and spacecraft to nth body
        RadiusVector<frames::earth::icrf> rCenterToNbody;
        if (body->get_type() == CelestialBodyType::MOON) {
            // TODO: Moons return position w.r.t their planet. Fix this. This will only work for the Earth-Moon system right now
            rCenterToNbody = body->get_position_at(date).force_frame_conversion<frames::earth::icrf>();
        }
        else {
            rCenterToNbody = (body->get_position_at(date) - rCenterToSsb).force_frame_conversion<frames::earth::icrf>(); // Gross
        }
        const RadiusVector<frames::earth::icrf> rVehicleToNbody = rCenterToNbody - rCenterToVehicle;

        // Normalize
        const Distance rMagVehicleToNbody = rVehicleToNbody.norm();
        const Distance rMagCenterToNbody  = rCenterToNbody.norm();

        // Perturbational force from nth body
        const GravParam mu                 = body->get_mu();
        const quantity directCoefficient   = mu / pow<3>(rMagVehicleToNbody);
        const quantity indirectCoefficient = mu / pow<3>(rMagCenterToNbody);

        accelNBody += directCoefficient * rVehicleToNbody - indirectCoefficient * rCenterToNbody;
    }

    return accelNBody;
}

} // namespace astro
} // namespace astrea