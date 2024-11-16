#include "NBodyForce.hpp"

basis_array NBodyForce::compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const {

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Central body properties
    const double& mu = system.get_center().mu();
    const double& equitorialR = system.get_center().eqR();
    const double& bodyRotationRate = system.get_center().rotRate();

    // Find day nearest to current time
    const int index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

    // Radius from central body to sun
    for (int jj = 0; jj < 3; ++jj) {
        radiusCentralBodyToSun[jj] = -radiusSunToCentralBody[index][jj]; // flip vector direction
    }

    // Reset perturbation
    accelNBody[0] = 0.0;
    accelNBody[1] = 0.0;
    accelNBody[2] = 0.0;
    for (int ii = 0; ii < nBodies; ++ii) {
        // Find radius from central body and spacecraft to nth body
        radiusCentralBodyToNbody[0] = radiusSunToNbody[index][ii*3]   + radiusCentralBodyToSun[0];
        radiusCentralBodyToNbody[1] = radiusSunToNbody[index][ii*3+1] + radiusCentralBodyToSun[1];
        radiusCentralBodyToNbody[2] = radiusSunToNbody[index][ii*3+2] + radiusCentralBodyToSun[2];

        radiusSpacecraftToNbody[0] = radiusCentralBodyToNbody[0] - x;
        radiusSpacecraftToNbody[1] = radiusCentralBodyToNbody[1] - y;
        radiusSpacecraftToNbody[2] = radiusCentralBodyToNbody[2] - z;

        // Normalize
        radiusSpacecraftToNbodyMagnitude = math_c::normalize(radiusSpacecraftToNbody);
        radiusCentralToNbodyMagnitude = math_c::normalize(radiusCentralBodyToNbody);

        // Perturbational force from nth body
        const double tempA = nBodyGravitationalParameter[ii]/(radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude);
        const double tempB = nBodyGravitationalParameter[ii]/(radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude);

        accelNBody[0] += tempA*radiusSpacecraftToNbody[0] - tempB*radiusCentralBodyToNbody[0];
        accelNBody[1] += tempA*radiusSpacecraftToNbody[1] - tempB*radiusCentralBodyToNbody[1];
        accelNBody[2] += tempA*radiusSpacecraftToNbody[2] - tempB*radiusCentralBodyToNbody[2];
    }
    */
    const basis_array accelNBody{
        0.0,
        0.0,
        0.0
    };

    return accelNBody;
}


std::unique_ptr<Force> build_nbody() { return std::make_unique<NBodyForce>(); }