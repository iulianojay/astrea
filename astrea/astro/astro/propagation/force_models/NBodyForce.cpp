#include <astro/propagation/force_models/NBodyForce.hpp>

#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

AccelerationVector<frames::earth::icrf>
    NBodyForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    // Extract
    const RadiusVector<frames::earth::icrf>& rCenterToVehicle = state.get_position();

    // Center body properties
    static const CelestialBodyUniquePtr& center = sys.get_central_body();

    // Find day nearest to current time
    const RadiusVector<frames::solar_system_barycenter::icrf> rCenterToSsb = -center->get_position_at(date);

    // Reset perturbation
    AccelerationVector<frames::earth::icrf> accelNBody{ 0.0 * km / (s * s) };
    for (const auto& [id, body] : sys) {

        if (body->get_name() == center->get_name()) { continue; }

        // Find center to nth body and spacecraft to nth body
        RadiusVector<frames::earth::icrf> rCenterToNbody;
        if (body->get_type() == CelestialBodyType::MOON) {
            // Moons return position w.r.t their planet. TODO: Fix this. This will only work for the Earth-Moon system right now
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