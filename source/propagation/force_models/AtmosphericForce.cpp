#include "AtmosphericForce.hpp"

#include "astro/constants/math_constants.h"
#include "astro/utilities/math/math_c.hpp"

basis_array AtmosphericForce::compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const {

    const GravitationalBody& center = sys.get_center();

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double& R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Central body properties
    const double& bodyRotationRate = center.rotRate();

    // Find velocity relative to atmosphere
    const double relativeVelocity[3] = {
        vx - y*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD,
        vy + x*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD,
        vz
    };

    // Exponential Drag Model
    const double atmosphericDensity = find_atmospheric_density(julianDate, state, center);

    // accel due to drag
    const double relativeVelocityMagnitude = math_c::normalize(relativeVelocity);

    const double coefficientOfDrag = vehicle.get_coefficient_of_drag();
    const basis_array areaRam = vehicle.get_ram_area();
    const double mass = vehicle.get_mass();
    const double dragMagnitude = -0.5*coefficientOfDrag*(areaRam[0] + areaRam[1] + areaRam[2])/mass*atmosphericDensity*relativeVelocityMagnitude;

    const basis_array accelDrag{
        dragMagnitude*relativeVelocity[0],
        dragMagnitude*relativeVelocity[1],
        dragMagnitude*relativeVelocity[2]
    };

    // Velocity in the radial direction
    const double radialVelcityMagnitude = (vx*x + vy*y + vz*z)/R;

    // accel due to lift
    const double coefficientOfLift = vehicle.get_coefficient_of_lift();
    const basis_array areaLift = vehicle.get_lift_area();
    const double tempA = 0.5*coefficientOfLift*(areaLift[0] + areaLift[1] + areaLift[2])/mass*atmosphericDensity*radialVelcityMagnitude*radialVelcityMagnitude/R;

    const basis_array accelLift{
        tempA*x,
        tempA*y,
        tempA*z
    };

    return {accelDrag[0] + accelLift[0], accelDrag[1] + accelLift[1], accelDrag[2] + accelLift[2]};
}


const double AtmosphericForce::find_atmospheric_density(const double& julianDate, const OrbitalElements& state, const GravitationalBody& center) const {

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];

    // Central body properties
    const double& equitorialR = center.eqR();
    const double& polarR = center.polR();
    const double& bodyRotationRate = center.rotRate();

    // Find altitude
    basis_array radius = {x, y, z};
    basis_array rBCBF{};
    basis_array lla{};
    conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);
    conversions::bcbf_to_lla(rBCBF, equitorialR, polarR, lla);
    const double altitude = lla[2];

    // Assume that bodies not listed have no significant atmosphere.Assume that
    // the atmosphere of the gas giants is defined by their radii, e.g.
    // outside of their equitorial radius, they have no noticible atmosphere
    // and inside that radius, the object will crash.
    double atmosphericDensity = 0.0;
    double referenceAltitude{};
    double referenceDensity{};
    double scaleHeight{};
    switch (center.planetId()) {
    case 2: // Venus
        if      (altitude < 3.0)   { atmosphericDensity = 5.53e1; } // kg/m^3
        else if (altitude < 6.0)   { atmosphericDensity = 4.75e1; }
        else if (altitude < 9.0)   { atmosphericDensity = 4.02e1; }
        else if (altitude < 12.0)  { atmosphericDensity = 3.44e1; }
        else if (altitude < 15.0)  { atmosphericDensity = 2.91e1; }
        else if (altitude < 18.0)  { atmosphericDensity = 2.46e1; }
        else if (altitude < 21.0)  { atmosphericDensity = 2.06e1; }
        else if (altitude < 24.0)  { atmosphericDensity = 1.70e1; }
        else if (altitude < 27.0)  { atmosphericDensity = 1.405e1; }
        else if (altitude < 30.0)  { atmosphericDensity = 1.115e1; }
        else if (altitude < 33.0)  { atmosphericDensity = 9.0; }
        else if (altitude < 36.0)  { atmosphericDensity = 7.15; }
        else if (altitude < 39.0)  { atmosphericDensity = 5.15; }
        else if (altitude < 42.0)  { atmosphericDensity = 4.34; }
        else if (altitude < 45.0)  { atmosphericDensity = 3.30; }
        else if (altitude < 48.0)  { atmosphericDensity = 2.39; }
        else if (altitude < 51.0)  { atmosphericDensity = 1.88; }
        else if (altitude < 54.0)  { atmosphericDensity = 1.38; }
        else if (altitude < 57.0)  { atmosphericDensity = 9.6e-1; }
        else if (altitude < 60.0)  { atmosphericDensity = 6.2e-1; }
        else if (altitude < 70.0)  { atmosphericDensity = 1.2e-1; }
        else if (altitude < 80.0)  { atmosphericDensity = 1.8e-2; }
        else if (altitude < 90.0)  { atmosphericDensity = 2.3e-3; }
        else if (altitude < 100.0) { atmosphericDensity = 3.1e-4; }
        else if (altitude < 110.0) { atmosphericDensity = 4.4e-5; }
        else if (altitude < 120.0) { atmosphericDensity = 7.2e-6; }
        else if (altitude < 130.0) { atmosphericDensity = 1.4e-6; }
        else if (altitude < 140.0) { atmosphericDensity = 3.0e-7; }
        else if (altitude < 150.0) { atmosphericDensity = 8.0e-8; }
        else if (altitude < 160.0) { atmosphericDensity = 2.6e-8; }
        else if (altitude < 170.0) { atmosphericDensity = 9.5e-9; }
        else if (altitude < 180.0) { atmosphericDensity = 4.0e-9; }
        else if (altitude < 190.0) { atmosphericDensity = 1.9e-9; }
        else if (altitude < 200.0) { atmosphericDensity = 9.4e-10; }
        else if (altitude < 210.0) { atmosphericDensity = 4.9e-10; }
        else if (altitude < 220.0) { atmosphericDensity = 2.6e-10; }
        else if (altitude < 230.0) { atmosphericDensity = 1.4e-10; }
        else if (altitude < 240.0) { atmosphericDensity = 7.5e-11; }
        else if (altitude < 250.0) { atmosphericDensity = 5.5e-11; }
        else if (altitude < 260.0) { atmosphericDensity = 4.1e-11; }
        else if (altitude < 270.0) { atmosphericDensity = 2.2e-11; }
        else if (altitude < 280.0) { atmosphericDensity = 1.2e-11; }
        else if (altitude < 290.0) { atmosphericDensity = 6.5e-12; }
        else if (altitude < 300.0) { atmosphericDensity = 3.5e-12; }
        else                       { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e9; // kg/m^3->kg/km^3
        break;

    case 3: // Earth
        // Altitude Conditions(TABLE 7-4, Vallado)
        if      (altitude < 25.0)   { referenceAltitude = 0.0;    referenceDensity = 1.225;     scaleHeight = 7.249; } // km, kg/m^3, km
        else if (altitude < 30.0)   { referenceAltitude = 25.0;   referenceDensity = 3.899e-2;  scaleHeight = 6.349; }
        else if (altitude < 40.0)   { referenceAltitude = 30.0;   referenceDensity = 1.774e-2;  scaleHeight = 6.682; }
        else if (altitude < 50.0)   { referenceAltitude = 40.0;   referenceDensity = 3.972e-3;  scaleHeight = 7.554; }
        else if (altitude < 60.0)   { referenceAltitude = 50.0;   referenceDensity = 1.057e-3;  scaleHeight = 8.382; }
        else if (altitude < 70.0)   { referenceAltitude = 60.0;   referenceDensity = 3.206e-4;  scaleHeight = 7.714; }
        else if (altitude < 80.0)   { referenceAltitude = 70.0;   referenceDensity = 8.770e-5;  scaleHeight = 6.549; }
        else if (altitude < 90.0)   { referenceAltitude = 80.0;   referenceDensity = 1.905e-5;  scaleHeight = 5.799; }
        else if (altitude < 100.0)  { referenceAltitude = 90.0;   referenceDensity = 3.396e-6;  scaleHeight = 5.382; }
        else if (altitude < 110.0)  { referenceAltitude = 100.0;  referenceDensity = 5.297e-7;  scaleHeight = 5.877; }
        else if (altitude < 120.0)  { referenceAltitude = 110.0;  referenceDensity = 9.661e-8;  scaleHeight = 7.263; }
        else if (altitude < 130.0)  { referenceAltitude = 120.0;  referenceDensity = 2.438e-8;  scaleHeight = 9.473; }
        else if (altitude < 140.0)  { referenceAltitude = 130.0;  referenceDensity = 8.484e-9;  scaleHeight = 12.636; }
        else if (altitude < 150.0)  { referenceAltitude = 140.0;  referenceDensity = 3.845e-9;  scaleHeight = 16.149; }
        else if (altitude < 180.0)  { referenceAltitude = 150.0;  referenceDensity = 2.070e-9;  scaleHeight = 22.523; }
        else if (altitude < 200.0)  { referenceAltitude = 180.0;  referenceDensity = 5.464e-10; scaleHeight = 29.740; }
        else if (altitude < 250.0)  { referenceAltitude = 200.0;  referenceDensity = 2.789e-10; scaleHeight = 37.105; }
        else if (altitude < 300.0)  { referenceAltitude = 250.0;  referenceDensity = 7.248e-11; scaleHeight = 45.546; }
        else if (altitude < 350.0)  { referenceAltitude = 300.0;  referenceDensity = 2.418e-11; scaleHeight = 53.628; }
        else if (altitude < 400.0)  { referenceAltitude = 350.0;  referenceDensity = 9.158e-12; scaleHeight = 53.298; }
        else if (altitude < 450.0)  { referenceAltitude = 400.0;  referenceDensity = 3.725e-12; scaleHeight = 58.515; }
        else if (altitude < 500.0)  { referenceAltitude = 450.0;  referenceDensity = 1.585e-12; scaleHeight = 60.828; }
        else if (altitude < 600.0)  { referenceAltitude = 500.0;  referenceDensity = 6.967e-13; scaleHeight = 63.822; }
        else if (altitude < 700.0)  { referenceAltitude = 600.0;  referenceDensity = 1.454e-13; scaleHeight = 71.835; }
        else if (altitude < 800.0)  { referenceAltitude = 700.0;  referenceDensity = 3.614e-14; scaleHeight = 88.667; }
        else if (altitude < 900.0)  { referenceAltitude = 800.0;  referenceDensity = 1.170e-14; scaleHeight = 124.64; }
        else if (altitude < 1000.0) { referenceAltitude = 900.0;  referenceDensity = 5.245e-15; scaleHeight = 181.05; }
        else if (altitude < 1100.0) { referenceAltitude = 1000.0; referenceDensity = 2.019e-15; scaleHeight = 268.00; }
        else                        { referenceAltitude = 1100.0; referenceDensity = 0.0;       scaleHeight = 1.0; }

        atmosphericDensity = referenceDensity*exp((referenceAltitude - altitude)/scaleHeight)*1.0e9; // kg/m^3 -> kg/km^3

        break;

    case 4: // Mars
        // The values up to 80 km are almost definitely wrong.I can't find any
        // sources that contradict them though.Please fix them(and the
        // associated crash radius of Mars) if you can find better numbers.
        if      (altitude < 2.0)   { atmosphericDensity = 1.19e-1; } // kg/m^3
        else if (altitude < 4.0)   { atmosphericDensity = 1.10e-1; }
        else if (altitude < 6.0)   { atmosphericDensity = 1.02e-1; }
        else if (altitude < 8.0)   { atmosphericDensity = 9.39e-2; }
        else if (altitude < 10.0)  { atmosphericDensity = 8.64e-2; }
        else if (altitude < 12.0)  { atmosphericDensity = 7.93e-2; }
        else if (altitude < 14.0)  { atmosphericDensity = 7.25e-2; }
        else if (altitude < 16.0)  { atmosphericDensity = 6.61e-2; }
        else if (altitude < 18.0)  { atmosphericDensity = 6.00e-2; }
        else if (altitude < 20.0)  { atmosphericDensity = 5.43e-2; }
        else if (altitude < 22.0)  { atmosphericDensity = 4.89e-2; }
        else if (altitude < 24.0)  { atmosphericDensity = 3.91e-2; }
        else if (altitude < 26.0)  { atmosphericDensity = 3.32e-2; }
        else if (altitude < 28.0)  { atmosphericDensity = 2.82e-2; }
        else if (altitude < 30.0)  { atmosphericDensity = 2.40e-2; }
        else if (altitude < 32.0)  { atmosphericDensity = 2.04e-2; }
        else if (altitude < 34.0)  { atmosphericDensity = 1.73e-2; }
        else if (altitude < 36.0)  { atmosphericDensity = 1.47e-2; }
        else if (altitude < 38.0)  { atmosphericDensity = 1.25e-2; }
        else if (altitude < 40.0)  { atmosphericDensity = 1.06e-2; }
        else if (altitude < 45.0)  { atmosphericDensity = 7.03e-3; }
        else if (altitude < 50.0)  { atmosphericDensity = 4.67e-3; }
        else if (altitude < 55.0)  { atmosphericDensity = 3.10e-3; }
        else if (altitude < 60.0)  { atmosphericDensity = 2.06e-3; }
        else if (altitude < 65.0)  { atmosphericDensity = 1.36e-3; }
        else if (altitude < 70.0)  { atmosphericDensity = 9.11e-4; }
        else if (altitude < 75.0)  { atmosphericDensity = 6.05e-4; }
        else if (altitude < 80.0)  { atmosphericDensity = 4.02e-4; }
        else if (altitude < 200.0) { atmosphericDensity = exp(-2.55314e-10*pow(altitude, 5) + 2.31927e-7*pow(altitude, 4) - 8.33206e-5*pow(altitude, 3) + 0.0151947*pow(altitude, 2) - 1.52799*altitude + 48.69659); }
        else if (altitude < 300.0) { atmosphericDensity = exp(2.65472e-11*pow(altitude, 5) - 2.45558e-8*pow(altitude, 4) + 6.31410e-6*pow(altitude, 3) + 4.73359e-4*pow(altitude, 2) - 0.443712*altitude + 23.79408); }
        else { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e9;  // kg/m^3->kg/km^3
        break;

    case 5: // Titan
        if      (altitude < 780.0)  { atmosphericDensity = 1.00e-12; } // g/cm^3
        else if (altitude < 790.0)  { atmosphericDensity = 8.45e-12; }
        else if (altitude < 800.0)  { atmosphericDensity = 7.16e-12; }
        else if (altitude < 810.0)  { atmosphericDensity = 6.08e-12; }
        else if (altitude < 820.0)  { atmosphericDensity = 5.17e-12; }
        else if (altitude < 830.0)  { atmosphericDensity = 4.41e-12; }
        else if (altitude < 840.0)  { atmosphericDensity = 3.77e-12; }
        else if (altitude < 850.0)  { atmosphericDensity = 3.23e-12; }
        else if (altitude < 860.0)  { atmosphericDensity = 2.78e-12; }
        else if (altitude < 870.0)  { atmosphericDensity = 2.39e-12; }
        else if (altitude < 880.0)  { atmosphericDensity = 2.06e-12; }
        else if (altitude < 890.0)  { atmosphericDensity = 1.78e-12; }
        else if (altitude < 900.0)  { atmosphericDensity = 1.54e-12; }
        else if (altitude < 910.0)  { atmosphericDensity = 1.34e-12; }
        else if (altitude < 920.0)  { atmosphericDensity = 1.16e-12; }
        else if (altitude < 930.0)  { atmosphericDensity = 1.01e-12; }
        else if (altitude < 940.0)  { atmosphericDensity = 8.80e-13; }
        else if (altitude < 950.0)  { atmosphericDensity = 7.67e-13; }
        else if (altitude < 960.0)  { atmosphericDensity = 6.69e-13; }
        else if (altitude < 970.0)  { atmosphericDensity = 5.84e-13; }
        else if (altitude < 980.0)  { atmosphericDensity = 5.10e-13; }
        else if (altitude < 990.0)  { atmosphericDensity = 4.46e-13; }
        else if (altitude < 1000.0) { atmosphericDensity = 3.90e-13; }
        else if (altitude < 1010.0) { atmosphericDensity = 1.81e-13; }
        else if (altitude < 1020.0) { atmosphericDensity = 2.99e-13; }
        else if (altitude < 1030.0) { atmosphericDensity = 2.62e-13; }
        else if (altitude < 1040.0) { atmosphericDensity = 2.30e-13; }
        else if (altitude < 1050.0) { atmosphericDensity = 2.02e-13; }
        else if (altitude < 1060.0) { atmosphericDensity = 1.78e-13; }
        else if (altitude < 1070.0) { atmosphericDensity = 1.56e-13; }
        else if (altitude < 1080.0) { atmosphericDensity = 1.38e-13; }
        else if (altitude < 1090.0) { atmosphericDensity = 1.21e-13; }
        else if (altitude < 1100.0) { atmosphericDensity = 1.07e-13; }
        else if (altitude < 1110.0) { atmosphericDensity = 9.43e-14; }
        else if (altitude < 1120.0) { atmosphericDensity = 8.33e-14; }
        else if (altitude < 1130.0) { atmosphericDensity = 7.36e-14; }
        else if (altitude < 1140.0) { atmosphericDensity = 6.51e-14; }
        else if (altitude < 1150.0) { atmosphericDensity = 5.76e-14; }
        else if (altitude < 1160.0) { atmosphericDensity = 5.10e-14; }
        else if (altitude < 1170.0) { atmosphericDensity = 4.52e-14; }
        else if (altitude < 1180.0) { atmosphericDensity = 4.01e-14; }
        else if (altitude < 1190.0) { atmosphericDensity = 3.56e-14; }
        else if (altitude < 1200.0) { atmosphericDensity = 3.16e-14; }
        else if (altitude < 1210.0) { atmosphericDensity = 2.81e-14; }
        else if (altitude < 1220.0) { atmosphericDensity = 2.50e-14; }
        else if (altitude < 1230.0) { atmosphericDensity = 2.22e-14; }
        else if (altitude < 1240.0) { atmosphericDensity = 1.98e-14; }
        else if (altitude < 1250.0) { atmosphericDensity = 1.77e-14; }
        else if (altitude < 1260.0) { atmosphericDensity = 1.58e-14; }
        else if (altitude < 1270.0) { atmosphericDensity = 1.41e-14; }
        else if (altitude < 1280.0) { atmosphericDensity = 1.26e-14; }
        else if (altitude < 1290.0) { atmosphericDensity = 1.12e-14; }
        else if (altitude < 1300.0) { atmosphericDensity = 1.00e-14; }
        else                        { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e12;  // g/cm^3->kg/km^3
        break;
    }

    return atmosphericDensity;
}
