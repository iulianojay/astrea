#include <astro/propagation/force_models/NBodyForce.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;
using namespace mp_units::iau::unit_symbols;

namespace astrea {
namespace astro {

AccelerationVector<ECI>
    NBodyForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();

    // Center body properties
    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Find day nearest to current time
    const Date epoch                          = vehicle.get_state().get_epoch();
    const State& stateSunToCenter             = center->get_state_at(date);
    const RadiusVector<ECI> radiusSunToCenter = stateSunToCenter.get_elements().in<Cartesian>(sys).get_position();

    // Radius from central body to sun
    const RadiusVector<ECI> radiusCenterToSun{ // flip vector direction
                                               -radiusSunToCenter[0],
                                               -radiusSunToCenter[1],
                                               -radiusSunToCenter[2]
    };

    // Reset perturbation
    AccelerationVector<ECI> accelNBody{ 0.0 * km / (s * s) };
    for (const auto& [name, body] : sys.get_all_bodies()) {

        if (body == center) { continue; }

        // Find day nearest to current time
        const State stateCenterToNBody = center->get_state_at(date);
        const RadiusVector<ECI> radiusCenterToNbody = stateCenterToNBody.get_elements().in<Cartesian>(sys).get_position();
        // TODO: This won't work for bodies in other planetary systems. Need a function like sys.get_radius_to_sun("name");

        // Find radius from central body and spacecraft to nth body
        const RadiusVector<ECI> radiusVehicleToNbody{ radiusCenterToNbody[0] - x,
                                                      radiusCenterToNbody[1] - y,
                                                      radiusCenterToNbody[2] - z };

        // Normalize
        const quantity radiusVehicleToNbodyMagnitude = sqrt(
            radiusVehicleToNbody[0] * radiusVehicleToNbody[0] + radiusVehicleToNbody[1] * radiusVehicleToNbody[1] +
            radiusVehicleToNbody[2] * radiusVehicleToNbody[2]
        );
        const quantity radiusCenterToNbodyMagnitude = sqrt(
            radiusCenterToNbody[0] * radiusCenterToNbody[0] + radiusCenterToNbody[1] * radiusCenterToNbody[1] +
            radiusCenterToNbody[2] * radiusCenterToNbody[2]
        );

        // Perturbational force from nth body
        const quantity directCoefficient =
            body->get_mu() / (radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude);
        const quantity indirectCoefficient =
            body->get_mu() / (radiusCenterToNbodyMagnitude * radiusCenterToNbodyMagnitude * radiusCenterToNbodyMagnitude);

        accelNBody[0] += directCoefficient * radiusVehicleToNbody[0] - indirectCoefficient * radiusCenterToNbody[0];
        accelNBody[1] += directCoefficient * radiusVehicleToNbody[1] - indirectCoefficient * radiusCenterToNbody[1];
        accelNBody[2] += directCoefficient * radiusVehicleToNbody[2] - indirectCoefficient * radiusCenterToNbody[2];
    }

    return accelNBody;
}

} // namespace astro
} // namespace astrea