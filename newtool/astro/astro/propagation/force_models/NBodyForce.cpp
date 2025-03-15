#include <astro/propagation/force_models/NBodyForce.hpp>

#include <math/utils.hpp>

basis_array NBodyForce::compute_force(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];

    // Central body properties
    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Find day nearest to current time
    const State& stateSunToCentralBody = (center->get_closest_state(julianDate)).convert(ElementSet::CARTESIAN, sys);

    // Radius from central body to sun
    const basis_array radiusCentralBodyToSun{ // flip vector direction
                                              -stateSunToCentralBody.elements[0],
                                              -stateSunToCentralBody.elements[1],
                                              -stateSunToCentralBody.elements[2]
    };

    // Reset perturbation
    basis_array accelNBody{ 0.0 };
    for (auto&& [name, body] : sys) {

        if (body == center) { continue; }

        // Find day nearest to current time
        const State& stateSunToNBody = (center->get_closest_state(julianDate)).convert(ElementSet::CARTESIAN, sys);

        // Radius from central body to sun
        const basis_array radiusSunToNbody{ // flip vector direction
                                            -stateSunToNBody.elements[0],
                                            -stateSunToNBody.elements[1],
                                            -stateSunToNBody.elements[2]
        };

        // Find radius from central body and spacecraft to nth body
        const basis_array radiusCentralBodyToNbody{ radiusSunToNbody[0] + radiusCentralBodyToSun[0],
                                                    radiusSunToNbody[1] + radiusCentralBodyToSun[1],
                                                    radiusSunToNbody[2] + radiusCentralBodyToSun[2] };

        const basis_array radiusVehicleToNbody{ radiusCentralBodyToNbody[0] - x,
                                                radiusCentralBodyToNbody[1] - y,
                                                radiusCentralBodyToNbody[2] - z };

        // Normalize
        const double radiusVehicleToNbodyMagnitude = math::normalize(radiusVehicleToNbody, 2);
        const double radiusCentralToNbodyMagnitude = math::normalize(radiusCentralBodyToNbody, 2);

        // Perturbational force from nth body
        const double tempA =
            body->get_mu() / (radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude * radiusVehicleToNbodyMagnitude);
        const double tempB =
            body->get_mu() / (radiusCentralToNbodyMagnitude * radiusCentralToNbodyMagnitude * radiusCentralToNbodyMagnitude);

        accelNBody[0] += tempA * radiusVehicleToNbody[0] - tempB * radiusCentralBodyToNbody[0];
        accelNBody[1] += tempA * radiusVehicleToNbody[1] - tempB * radiusCentralBodyToNbody[1];
        accelNBody[2] += tempA * radiusVehicleToNbody[2] - tempB * radiusCentralBodyToNbody[2];
    }

    return accelNBody;
}
