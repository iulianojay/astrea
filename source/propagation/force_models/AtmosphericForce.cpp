#include "AtmosphericForce.hpp"

#include "astro/constants/math_constants.h"
#include "astro/utilities/math/math_c.hpp"

basis_array AtmosphericForce::compute_force(const double& julianDate, const OrbitalElements& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const {

    const GravitationalBody& center = sys.get_center();

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double& R = std::sqrt(x*x + y*y + z*z);

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
    const double areaRam = vehicle.get_ram_area();
    const double mass = vehicle.get_mass();
    const double dragMagnitude = -0.5*coefficientOfDrag*(areaRam)/mass*atmosphericDensity*relativeVelocityMagnitude;

    const basis_array accelDrag{
        dragMagnitude*relativeVelocity[0],
        dragMagnitude*relativeVelocity[1],
        dragMagnitude*relativeVelocity[2]
    };

    // Velocity in the radial direction
    const double radialVelcityMagnitude = (vx*x + vy*y + vz*z)/R;

    // accel due to lift
    const double coefficientOfLift = vehicle.get_coefficient_of_lift();
    const double areaLift = vehicle.get_lift_area();
    const double tempA = 0.5*coefficientOfLift*areaLift/mass*atmosphericDensity*radialVelcityMagnitude*radialVelcityMagnitude/R;

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
    switch (center.planetId()) {
        case 2: { // Venus

            const auto iter = venutianAtmosphere.upper_bound(altitude);
            atmosphericDensity = (iter != venutianAtmosphere.end()) ? iter->second : 0.0;
            atmosphericDensity *= 1.0e9; // kg/m^3 -> kg/km^3
            break;
        }
        case 3: {// Earth

            double referenceAltitude{};
            double referenceDensity{};
            double scaleHeight{};

            const auto iter = earthAtmosphere.upper_bound(altitude);
            if (iter != earthAtmosphere.end()) {
                const auto atmo = iter->second;
                referenceAltitude = std::get<0>(atmo);
                referenceDensity = std::get<1>(atmo);
                scaleHeight = std::get<2>(atmo);
            }
            else {
                referenceAltitude = 1100.0;
                referenceDensity = 0.0;
                scaleHeight = 1.0;
            }

            atmosphericDensity = referenceDensity*std::exp((referenceAltitude - altitude)/scaleHeight)*1.0e9; // kg/m^3 -> kg/km^3
            break;
        }
        case 4: {// Mars
            // The values up to 80 km are almost definitely wrong.I can't find any
            // sources that contradict them though.Please fix them(and the
            // associated crash radius of Mars) if you can find better numbers.
            if (altitude <= 80.0)  {
                const auto iter = martianAtmosphere.upper_bound(altitude);
                atmosphericDensity = (iter != martianAtmosphere.end()) ? iter->second : 0.0;
            }
            else if (altitude < 200.0) {
                atmosphericDensity = std::exp(-2.55314e-10*std::pow(altitude, 5) + 2.31927e-7*std::pow(altitude, 4) - 8.33206e-5*std::pow(altitude, 3) +
                                         0.0151947*std::pow(altitude, 2) - 1.52799*altitude + 48.69659);
            }
            else if (altitude < 300.0) {
                atmosphericDensity = std::exp(2.65472e-11*std::pow(altitude, 5) - 2.45558e-8*std::pow(altitude, 4) + 6.31410e-6*std::pow(altitude, 3) +
                                         4.73359e-4*std::pow(altitude, 2) - 0.443712*altitude + 23.79408);
            }
            else {
                atmosphericDensity = 0.0;
            }

            atmosphericDensity *= 1.0e9;  // kg/m^3->kg/km^3
            break;
        }
        case 5: {// Titan

            const auto iter = titanicAtmosphere.upper_bound(altitude);
            atmosphericDensity = (iter != titanicAtmosphere.end()) ? iter->second : 0.0;

            atmosphericDensity *= 1.0e12;  // g/cm^3->kg/km^3
            break;
        }
    }
    return atmosphericDensity;
}

//------------------------------------------------------------------------//
//---------------------- ATMOSPHERIC DENSITY TABLES ----------------------//
//------------------------------------------------------------------------//

const std::map<double, double> AtmosphericForce::venutianAtmosphere = { // km, kg/m^3
    {3.0, 5.53e1},
    {6.0, 4.75e1},
    {9.0, 4.02e1},
    {12.0, 3.44e1},
    {15.0, 2.91e1},
    {18.0, 2.46e1},
    {21.0, 2.06e1},
    {24.0, 1.70e1},
    {27.0, 1.405e1},
    {30.0, 1.115e1},
    {33.0, 9.0},
    {36.0, 7.15},
    {39.0, 5.15},
    {42.0, 4.34},
    {45.0, 3.30},
    {48.0, 2.39},
    {51.0, 1.88},
    {54.0, 1.38},
    {57.0, 9.6e-1},
    {60.0, 6.2e-1},
    {70.0, 1.2e-1},
    {80.0, 1.8e-2},
    {90.0, 2.3e-3},
    {100.0, 3.1e-4},
    {110.0, 4.4e-5},
    {120.0, 7.2e-6},
    {130.0, 1.4e-6},
    {140.0, 3.0e-7},
    {150.0, 8.0e-8},
    {160.0, 2.6e-8},
    {170.0, 9.5e-9},
    {180.0, 4.0e-9},
    {190.0, 1.9e-9},
    {200.0, 9.4e-10},
    {210.0, 4.9e-10},
    {220.0, 2.6e-10},
    {230.0, 1.4e-10},
    {240.0, 7.5e-11},
    {250.0, 5.5e-11},
    {260.0, 4.1e-11},
    {270.0, 2.2e-11},
    {280.0, 1.2e-11},
    {290.0, 6.5e-12},
    {300.0, 3.5e-12}
};

const std::map<double, double> AtmosphericForce::martianAtmosphere = { // km, kg/m^3
    {2.0, 1.19e-1,},
    {4.0, 1.10e-1,},
    {6.0, 1.02e-1,},
    {8.0, 9.39e-2,},
    {10.0, 8.64e-2,},
    {12.0, 7.93e-2,},
    {14.0, 7.25e-2,},
    {16.0, 6.61e-2,},
    {18.0, 6.00e-2,},
    {20.0, 5.43e-2,},
    {22.0, 4.89e-2,},
    {24.0, 3.91e-2,},
    {26.0, 3.32e-2,},
    {28.0, 2.82e-2,},
    {30.0, 2.40e-2,},
    {32.0, 2.04e-2,},
    {34.0, 1.73e-2,},
    {36.0, 1.47e-2,},
    {38.0, 1.25e-2,},
    {40.0, 1.06e-2,},
    {45.0, 7.03e-3,},
    {50.0, 4.67e-3,},
    {55.0, 3.10e-3,},
    {60.0, 2.06e-3,},
    {65.0, 1.36e-3,},
    {70.0, 9.11e-4,},
    {75.0, 6.05e-4,},
    {80.0, 4.02e-4,}
};

// Altitude Conditions(TABLE 7-4, Vallado)
const std::map<double, std::tuple<double, double, double>> AtmosphericForce::earthAtmosphere = { // km, (km, kg/m^3, km)
    {25.0, {0.0, 1.225, 7.249}},
    {30.0, {25.0, 3.899e-2, 6.349}},
    {40.0, {30.0, 1.774e-2, 6.682}},
    {50.0, {40.0, 3.972e-3, 7.554}},
    {60.0, {50.0, 1.057e-3, 8.382}},
    {70.0, {60.0, 3.206e-4, 7.714}},
    {80.0, {70.0, 8.770e-5, 6.549}},
    {90.0, {80.0, 1.905e-5, 5.799}},
    {100.0, {90.0, 3.396e-6, 5.382}},
    {110.0, {100.0, 5.297e-7, 5.877}},
    {120.0, {110.0, 9.661e-8, 7.263}},
    {130.0, {120.0, 2.438e-8, 9.473}},
    {140.0, {130.0, 8.484e-9, 12.636 }},
    {150.0, {140.0, 3.845e-9, 16.149 }},
    {180.0, {150.0, 2.070e-9, 22.523 }},
    {200.0, {180.0, 5.464e-10, 29.740 }},
    {250.0, {200.0, 2.789e-10, 37.105 }},
    {300.0, {250.0, 7.248e-11, 45.546 }},
    {350.0, {300.0, 2.418e-11, 53.628 }},
    {400.0, {350.0, 9.158e-12, 53.298 }},
    {450.0, {400.0, 3.725e-12, 58.515 }},
    {500.0, {450.0, 1.585e-12, 60.828 }},
    {600.0, {500.0, 6.967e-13, 63.822 }},
    {700.0, {600.0, 1.454e-13, 71.835 }},
    {800.0, {700.0, 3.614e-14, 88.667 }},
    {900.0, {800.0, 1.170e-14, 124.64 }},
    {1000.0, {900.0, 5.245e-15, 181.05 }},
    {1100.0, {1000.0, 2.019e-15, 268.00 }}
};

const std::map<double, double> AtmosphericForce::titanicAtmosphere = { // km, g/cm^3
    {780.0, 1.00e-12},
    {790.0, 8.45e-12},
    {800.0, 7.16e-12},
    {810.0, 6.08e-12},
    {820.0, 5.17e-12},
    {830.0, 4.41e-12},
    {840.0, 3.77e-12},
    {850.0, 3.23e-12},
    {860.0, 2.78e-12},
    {870.0, 2.39e-12},
    {880.0, 2.06e-12},
    {890.0, 1.78e-12},
    {900.0, 1.54e-12},
    {910.0, 1.34e-12},
    {920.0, 1.16e-12},
    {930.0, 1.01e-12},
    {940.0, 8.80e-13},
    {950.0, 7.67e-13},
    {960.0, 6.69e-13},
    {970.0, 5.84e-13},
    {980.0, 5.10e-13},
    {990.0, 4.46e-13},
    {1000.0, 3.90e-13},
    {1010.0, 1.81e-13},
    {1020.0, 2.99e-13},
    {1030.0, 2.62e-13},
    {1040.0, 2.30e-13},
    {1050.0, 2.02e-13},
    {1060.0, 1.78e-13},
    {1070.0, 1.56e-13},
    {1080.0, 1.38e-13},
    {1090.0, 1.21e-13},
    {1100.0, 1.07e-13},
    {1110.0, 9.43e-14},
    {1120.0, 8.33e-14},
    {1130.0, 7.36e-14},
    {1140.0, 6.51e-14},
    {1150.0, 5.76e-14},
    {1160.0, 5.10e-14},
    {1170.0, 4.52e-14},
    {1180.0, 4.01e-14},
    {1190.0, 3.56e-14},
    {1200.0, 3.16e-14},
    {1210.0, 2.81e-14},
    {1220.0, 2.50e-14},
    {1230.0, 2.22e-14},
    {1240.0, 1.98e-14},
    {1250.0, 1.77e-14},
    {1260.0, 1.58e-14},
    {1270.0, 1.41e-14},
    {1280.0, 1.26e-14},
    {1290.0, 1.12e-14},
    {1300.0, 1.00e-14}
};