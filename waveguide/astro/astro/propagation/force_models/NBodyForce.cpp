#include <astro/propagation/force_models/NBodyForce.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;
using namespace mp_units::iau::unit_symbols;

namespace waveguide {
namespace astro {

AccelerationVector
    NBodyForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();

    // Center body properties
    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Find day nearest to current time
    const Date epoch                     = vehicle.get_state().get_epoch();
    const State& stateSunToCenter        = center->get_state_at(date);
    const RadiusVector radiusSunToCenter = stateSunToCenter.get_elements().in<Cartesian>(sys).get_radius();

    // Radius from central body to sun
    const RadiusVector radiusCenterToSun{ // flip vector direction
                                          -radiusSunToCenter[0],
                                          -radiusSunToCenter[1],
                                          -radiusSunToCenter[2]
    };

    // Reset perturbation
    AccelerationVector accelNBody{ 0.0 * km / (s * s) };
    for (const auto& [name, body] : sys.get_all_bodies()) {

        if (body == center) { continue; }

        // Find day nearest to current time
        const State& stateSunToNBody        = center->get_state_at(date);
        const RadiusVector radiusSunToNbody = stateSunToNBody.get_elements().in<Cartesian>(sys).get_radius();

        // Find radius from central body and spacecraft to nth body
        const RadiusVector radiusCenterToNbody{ radiusSunToNbody[0] + radiusCenterToSun[0],
                                                radiusSunToNbody[1] + radiusCenterToSun[1],
                                                radiusSunToNbody[2] + radiusCenterToSun[2] };

        const RadiusVector radiusVehicleToNbody{ radiusCenterToNbody[0] - x, radiusCenterToNbody[1] - y, radiusCenterToNbody[2] - z };

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
        const quantity tempA =
            body->get_mu() / (radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude);
        const quantity tempB =
            body->get_mu() / (radiusCenterToNbodyMagnitude * radiusCenterToNbodyMagnitude * radiusCenterToNbodyMagnitude);

        accelNBody[0] += tempA * radiusVehicleToNbody[0] - tempB * radiusCenterToNbody[0];
        accelNBody[1] += tempA * radiusVehicleToNbody[1] - tempB * radiusCenterToNbody[1];
        accelNBody[2] += tempA * radiusVehicleToNbody[2] - tempB * radiusCenterToNbody[2];
    }

    return accelNBody;
}

} // namespace astro
} // namespace waveguide