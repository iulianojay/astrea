#include "SolarRadiationPressureForce.hpp"

basis_array SolarRadiationPressureForce::compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const {

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
    const double& equitorialR = system.get_center().eqR();

    // Find day nearest to current time
    const int index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

    // Radius from central body to sun
    for (int jj = 0; jj < 3; ++jj) {
        radiusCentralBodyToSun[jj] = -radiusSunToCentralBody[index][jj]; // flip vector direction
    }
    radialMagnitudeCentralBodyToSun = math_c::normalize(radiusCentralBodyToSun);

    radiusSpacecraftToSun[0] = radiusCentralBodyToSun[0] - x;
    radiusSpacecraftToSun[1] = radiusCentralBodyToSun[1] - y;
    radiusSpacecraftToSun[2] = radiusCentralBodyToSun[2] - z;
    radialMagnitudeSpacecraftToSun = math_c::normalize(radiusSpacecraftToSun);

    // Solar radiation pressure
    solarRadiationPressure = solarRadiationPressureAt1AU*AU*AU/(radialMagnitudeSpacecraftToSun*radialMagnitudeSpacecraftToSun); // Scale by(1AU/R)^2 for other bodies
    fractionOfRecievedSunlight = 1.0;

    if (system.get_center().planetId() != 0) {
        //
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        //

        referenceAngle = acos((radiusCentralBodyToSun[0]*x + radiusCentralBodyToSun[1]*y + radiusCentralBodyToSun[2]*z)/(radialMagnitudeCentralBodyToSun*R));
        referenceAngle1 = acos(equitorialR/R);
        referenceAngle2 = acos(equitorialR/radialMagnitudeCentralBodyToSun);

        if (referenceAngle1 + referenceAngle2 <= referenceAngle) { // In shadow
            Xu = equitorialR*radialMagnitudeCentralBodyToSun/(696000.0 - equitorialR); // that constant has something to do with the diameter of the sun

            rP[0] = -Xu*radiusCentralBodyToSun[0]/radialMagnitudeCentralBodyToSun;
            rP[1] = -Xu*radiusCentralBodyToSun[1]/radialMagnitudeCentralBodyToSun;
            rP[2] = -Xu*radiusCentralBodyToSun[2]/radialMagnitudeCentralBodyToSun;

            rPs[0] = x - rP[0];
            rPs[1] = y - rP[1];
            rPs[2] = z - rP[2];

            normRP = math_c::normalize(rP);
            normRPs = math_c::normalize(rPs);

            alphaps = abs(asin((-rPs[0]*rP[0] - rPs[1]*rP[1] - rPs[2]*rP[2])/(normRP*normRPs)));

            if (alphaps < asin(equitorialR/Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0;
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5;
            }
        }
    }

    // accel due to srp
    const double coefficientOfReflectivity = spacecraft->get_coefficient_of_reflectivity();
    const double *areaSun = spacecraft->get_sun_area();
    const double mass = spacecraft->get_mass();
    const double tempA = -solarRadiationPressure*coefficientOfReflectivity*(areaSun[0] + areaSun[1] + areaSun[2])/mass/radialMagnitudeSpacecraftToSun*fractionOfRecievedSunlight;

    accelSRP[0] = tempA*radiusSpacecraftToSun[0];
    accelSRP[1] = tempA*radiusSpacecraftToSun[1];
    accelSRP[2] = tempA*radiusSpacecraftToSun[2];

    */
    const basis_array accelSRP{
        0.0,
        0.0,
        0.0
    };

    return accelSRP;
}