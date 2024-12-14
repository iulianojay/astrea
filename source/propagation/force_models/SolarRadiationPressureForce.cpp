#include "SolarRadiationPressureForce.hpp"

#include "math_c.hpp"

basis_array SolarRadiationPressureForce::compute_force(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const {

    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double R = std::sqrt(x*x + y*y + z*z);

    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Central body properties
    static const double& equitorialR = center->get_equitorial_radius();
    static const bool isSun = (center->get_name() != "Sun");

    // Find day nearest to current time
    const State stateSunToCentralBody = center->get_state_at(julianDate);
    const basis_array radiusSunToCentralBody{};// = center->get_state_at(julianDate);

    // Radius from central body to sun
    const basis_array radiusCentralBodyToSun{};// = -radiusSunToCentralBody; // flip vector direction
    const double radialMagnitudeCentralBodyToSun = math_c::normalize(radiusCentralBodyToSun, 2);

    const basis_array radiusVehicleToSun{
        radiusCentralBodyToSun[0] - x,
        radiusCentralBodyToSun[1] - y,
        radiusCentralBodyToSun[2] - z
    };
    const double radialMagnitudeVehicleToSun = math_c::normalize(radiusVehicleToSun, 2);

    // Solar radiation pressure
    const double solarRadiationPressure = SRP_1AU*(AU*AU)/(radialMagnitudeVehicleToSun*radialMagnitudeVehicleToSun); // Scale by(1AU/R)^2 for other bodies
    double fractionOfRecievedSunlight = 1.0;
    if (isSun) {
        //
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        //

        const double referenceAngle = acos((radiusCentralBodyToSun[0]*x + radiusCentralBodyToSun[1]*y + radiusCentralBodyToSun[2]*z)/(radialMagnitudeCentralBodyToSun*R));
        const double referenceAngle1 = acos(equitorialR/R);
        const double referenceAngle2 = acos(equitorialR/radialMagnitudeCentralBodyToSun);

        if (referenceAngle1 + referenceAngle2 <= referenceAngle) { // In shadow
            const double Xu = equitorialR*radialMagnitudeCentralBodyToSun/(696000.0 - equitorialR); // that constant has something to do with the diameter of the sun

            const basis_array rP{
                -Xu*radiusCentralBodyToSun[0]/radialMagnitudeCentralBodyToSun,
                -Xu*radiusCentralBodyToSun[1]/radialMagnitudeCentralBodyToSun,
                -Xu*radiusCentralBodyToSun[2]/radialMagnitudeCentralBodyToSun
            };
            const double normRP = math_c::normalize(rP, 2);

            const basis_array rPs{
                x - rP[0],
                y - rP[1],
                z - rP[2]
            };
            const double normRPs = math_c::normalize(rPs, 2);

            const double alphaps = abs(asin((-rPs[0]*rP[0] - rPs[1]*rP[1] - rPs[2]*rP[2])/(normRP*normRPs)));

            if (alphaps < asin(equitorialR/Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0;
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5;
            }
        }
    }

    // accel due to srp
    const double coefficientOfReflectivity = vehicle.get_coefficient_of_reflectivity();
    const double areaSun = vehicle.get_solar_area();
    const double mass = vehicle.get_mass();
    const double tempA = -solarRadiationPressure*coefficientOfReflectivity*(areaSun)/mass/radialMagnitudeVehicleToSun*fractionOfRecievedSunlight;

    const basis_array accelSRP{
        tempA*radiusVehicleToSun[0],
        tempA*radiusVehicleToSun[1],
        tempA*radiusVehicleToSun[2]
    };

    return accelSRP;
}