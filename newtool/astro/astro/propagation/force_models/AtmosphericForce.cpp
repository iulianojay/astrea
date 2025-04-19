#include <astro/propagation/force_models/AtmosphericForce.hpp>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

// astro
#include <math/utils.hpp>


using namespace mp_units;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

AccelerationVector
    AtmosphericForce::compute_force(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Extract
    const auto& x = state.get_x();
    const auto& y = state.get_y();
    const auto& z = state.get_z();
    const auto& R = sqrt(x * x + y * y + z * z);

    const auto& vx = state.get_vx();
    const auto& vy = state.get_vy();
    const auto& vz = state.get_vz();

    // Central body properties
    static const auto& bodyRotationRate = center->get_rotation_rate();

    // Find velocity relative to atmosphere
    const quantity<km / s> relVx = vx - (y * bodyRotationRate.in(rad / s));
    const quantity<km / s> relVy = vy + (x * bodyRotationRate.in(rad / s));
    const quantity<km / s> relVz = vz;

    // Exponential Drag Model
    const quantity atmosphericDensity = find_atmospheric_density(julianDate, state, center);

    // Accel due to drag
    const quantity relativeVelocityMagnitude = sqrt(relVx * relVx + relVy * relVy + relVz * relVz);
    const quantity coefficientOfDrag         = vehicle.get_coefficient_of_drag();
    const quantity areaRam                   = vehicle.get_ram_area();
    const quantity mass                      = vehicle.get_mass();
    const quantity dragMagnitude = -0.5 * coefficientOfDrag * (areaRam) / mass * atmosphericDensity * relativeVelocityMagnitude;

    const quantity<km / (s * s)> accelDrag[3]{ dragMagnitude * relVx, dragMagnitude * relVy, dragMagnitude * relVz };

    // Velocity in the radial direction
    const quantity radialVelcityMagnitude = (vx * x + vy * y + vz * z) / R;

    // accel due to lift
    const quantity coefficientOfLift = vehicle.get_coefficient_of_lift();
    const quantity areaLift          = vehicle.get_lift_area();
    const quantity tempA =
        0.5 * coefficientOfLift * areaLift / mass * atmosphericDensity * radialVelcityMagnitude * radialVelcityMagnitude / R;

    const quantity<km / (s * s)> accelLift[3]{ tempA * x, tempA * y, tempA * z };

    return { accelDrag[0] + accelLift[0], accelDrag[1] + accelLift[1], accelDrag[2] + accelLift[2] };
}


const AtmosphericForce::Density
    AtmosphericForce::find_atmospheric_density(const JulianDate& julianDate, const Cartesian& state, const CelestialBodyUniquePtr& center) const
{

    // Extract
    const quantity<km>& x = state.get_x();
    const quantity<km>& y = state.get_y();
    const quantity<km>& z = state.get_z();

    // Central body properties
    static const quantity<km> equitorialR           = center->get_equitorial_radius();
    static const quantity<km> polarR                = center->get_polar_radius();
    static const quantity<rad / s> bodyRotationRate = center->get_rotation_rate();
    static const std::string& centerName            = center->get_name();

    // Find altitude
    const auto radius = state.get_radius();
    basis_array rBCI{ radius[0].numerical_value_in(radius[0].unit),
                      radius[1].numerical_value_in(radius[1].unit),
                      radius[2].numerical_value_in(radius[2].unit) };
    basis_array rBCBF{};
    basis_array lla{};
    conversions::bci_to_bcbf(rBCI, julianDate, bodyRotationRate, rBCBF);
    conversions::bcbf_to_lla(rBCBF, equitorialR, polarR, lla);

    const quantity<km> altitude(lla[2] * km);

    // Assume that bodies not listed have no significant atmosphere.Assume that
    // the atmosphere of the gas giants is defined by their radii, e.g.
    // outside of their equitorial radius, they have no noticible atmosphere
    // and inside that radius, the object will crash.
    Density atmosphericDensity;
    if (centerName == "Venus") {
        const auto iter    = venutianAtmosphere.upper_bound(altitude);
        atmosphericDensity = (iter != venutianAtmosphere.end()) ? iter->second : 0.0 * kg / (m * m * m);
    }
    else if (centerName == "Earth") {
        quantity<km> referenceAltitude;
        Density referenceDensity;
        quantity<km> scaleHeight;

        const auto iter = earthAtmosphere.upper_bound(altitude);
        if (iter != earthAtmosphere.end()) {
            const auto atmo   = iter->second;
            referenceAltitude = std::get<0>(atmo);
            referenceDensity  = std::get<1>(atmo);
            scaleHeight       = std::get<2>(atmo);
        }
        else {
            referenceAltitude = 1100.0 * km;
            referenceDensity  = 0.0 * kg / (m * m * m);
            scaleHeight       = 1.0 * km;
        }

        atmosphericDensity = referenceDensity * exp((referenceAltitude - altitude) / scaleHeight);
    }
    else if (centerName == "Mars") {
        // The values up to 80 km are almost definitely wrong.I can't find any
        // sources that contradict them though.Please fix them(and the
        // associated crash radius of Mars) if you can find better numbers.
        if (altitude <= 80.0) {
            const auto iter    = martianAtmosphere.upper_bound(altitude);
            atmosphericDensity = (iter != martianAtmosphere.end()) ? iter->second : 0.0 * kg / (m * m * m);
        }
        else if (altitude < 200.0) {
            atmosphericDensity = exp(-2.55314e-10 * pow(altitude, 5) + 2.31927e-7 * pow(altitude, 4) -
                                     8.33206e-5 * pow(altitude, 3) + 0.0151947 * pow(altitude, 2) - 1.52799 * altitude + 48.69659) *
                                 kg / (m * m * m);
        }
        else if (altitude < 300.0) {
            atmosphericDensity =
                exp(2.65472e-11 * pow(altitude, 5) - 2.45558e-8 * pow(altitude, 4) + 6.31410e-6 * pow(altitude, 3) +
                    4.73359e-4 * pow(altitude, 2) - 0.443712 * altitude + 23.79408) *
                kg / (m * m * m);
        }
        else {
            atmosphericDensity = 0.0 * kg / (m * m * m);
        }
    }
    else if (centerName == "Titan") {
        const auto iter    = titanicAtmosphere.upper_bound(altitude);
        atmosphericDensity = (iter != titanicAtmosphere.end()) ? iter->second : 0.0 * g / (cm * cm * cm);
    }

    return atmosphericDensity;
}

//------------------------------------------------------------------------//
//---------------------- ATMOSPHERIC DENSITY TABLES ----------------------//
//------------------------------------------------------------------------//

const std::map < quantity<km>, quantity<kg / (pow<3>(m))> AtmosphericForce::venutianAtmosphere = { // km, kg/m^3
    { 3.0 * km, 5.53e1 * kg / (pow<3>(m)) },    { 6.0 * km, 4.75e1 * kg / (pow<3>(m)) },
    { 9.0 * km, 4.02e1 * kg / (pow<3>(m)) },    { 12.0 * km, 3.44e1 * kg / (pow<3>(m)) },
    { 15.0 * km, 2.91e1 * kg / (pow<3>(m)) },   { 18.0 * km, 2.46e1 * kg / (pow<3>(m)) },
    { 21.0 * km, 2.06e1 * kg / (pow<3>(m)) },   { 24.0 * km, 1.70e1 * kg / (pow<3>(m)) },
    { 27.0 * km, 1.405e1 * kg / (pow<3>(m)) },  { 30.0 * km, 1.115e1 * kg / (pow<3>(m)) },
    { 33.0 * km, 9.0 * kg / (pow<3>(m)) },      { 36.0 * km, 7.15 * kg / (pow<3>(m)) },
    { 39.0 * km, 5.15 * kg / (pow<3>(m)) },     { 42.0 * km, 4.34 * kg / (pow<3>(m)) },
    { 45.0 * km, 3.30 * kg / (pow<3>(m)) },     { 48.0 * km, 2.39 * kg / (pow<3>(m)) },
    { 51.0 * km, 1.88 * kg / (pow<3>(m)) },     { 54.0 * km, 1.38 * kg / (pow<3>(m)) },
    { 57.0 * km, 9.6e-1 * kg / (pow<3>(m)) },   { 60.0 * km, 6.2e-1 * kg / (pow<3>(m)) },
    { 70.0 * km, 1.2e-1 * kg / (pow<3>(m)) },   { 80.0 * km, 1.8e-2 * kg / (pow<3>(m)) },
    { 90.0 * km, 2.3e-3 * kg / (pow<3>(m)) },   { 100.0 * km, 3.1e-4 * kg / (pow<3>(m)) },
    { 110.0 * km, 4.4e-5 * kg / (pow<3>(m)) },  { 120.0 * km, 7.2e-6 * kg / (pow<3>(m)) },
    { 130.0 * km, 1.4e-6 * kg / (pow<3>(m)) },  { 140.0 * km, 3.0e-7 * kg / (pow<3>(m)) },
    { 150.0 * km, 8.0e-8 * kg / (pow<3>(m)) },  { 160.0 * km, 2.6e-8 * kg / (pow<3>(m)) },
    { 170.0 * km, 9.5e-9 * kg / (pow<3>(m)) },  { 180.0 * km, 4.0e-9 * kg / (pow<3>(m)) },
    { 190.0 * km, 1.9e-9 * kg / (pow<3>(m)) },  { 200.0 * km, 9.4e-10 * kg / (pow<3>(m)) },
    { 210.0 * km, 4.9e-10 * kg / (pow<3>(m)) }, { 220.0 * km, 2.6e-10 * kg / (pow<3>(m)) },
    { 230.0 * km, 1.4e-10 * kg / (pow<3>(m)) }, { 240.0 * km, 7.5e-11 * kg / (pow<3>(m)) },
    { 250.0 * km, 5.5e-11 * kg / (pow<3>(m)) }, { 260.0 * km, 4.1e-11 * kg / (pow<3>(m)) },
    { 270.0 * km, 2.2e-11 * kg / (pow<3>(m)) }, { 280.0 * km, 1.2e-11 * kg / (pow<3>(m)) },
    { 290.0 * km, 6.5e-12 * kg / (pow<3>(m)) }, { 300.0 * km, 3.5e-12 * kg / (pow<3>(m)) }
};

const std::map<quantity<km>, quantity<kg / (pow<3>(m))>> AtmosphericForce::martianAtmosphere = { // km, kg/m^3
    { 2.0 * km, 1.19e-1 * kg / (pow<3>(m)) },  { 4.0 * km, 1.10e-1 * kg / (pow<3>(m)) },
    { 6.0 * km, 1.02e-1 * kg / (pow<3>(m)) },  { 8.0 * km, 9.39e-2 * kg / (pow<3>(m)) },
    { 10.0 * km, 8.64e-2 * kg / (pow<3>(m)) }, { 12.0 * km, 7.93e-2 * kg / (pow<3>(m)) },
    { 14.0 * km, 7.25e-2 * kg / (pow<3>(m)) }, { 16.0 * km, 6.61e-2 * kg / (pow<3>(m)) },
    { 18.0 * km, 6.00e-2 * kg / (pow<3>(m)) }, { 20.0 * km, 5.43e-2 * kg / (pow<3>(m)) },
    { 22.0 * km, 4.89e-2 * kg / (pow<3>(m)) }, { 24.0 * km, 3.91e-2 * kg / (pow<3>(m)) },
    { 26.0 * km, 3.32e-2 * kg / (pow<3>(m)) }, { 28.0 * km, 2.82e-2 * kg / (pow<3>(m)) },
    { 30.0 * km, 2.40e-2 * kg / (pow<3>(m)) }, { 32.0 * km, 2.04e-2 * kg / (pow<3>(m)) },
    { 34.0 * km, 1.73e-2 * kg / (pow<3>(m)) }, { 36.0 * km, 1.47e-2 * kg / (pow<3>(m)) },
    { 38.0 * km, 1.25e-2 * kg / (pow<3>(m)) }, { 40.0 * km, 1.06e-2 * kg / (pow<3>(m)) },
    { 45.0 * km, 7.03e-3 * kg / (pow<3>(m)) }, { 50.0 * km, 4.67e-3 * kg / (pow<3>(m)) },
    { 55.0 * km, 3.10e-3 * kg / (pow<3>(m)) }, { 60.0 * km, 2.06e-3 * kg / (pow<3>(m)) },
    { 65.0 * km, 1.36e-3 * kg / (pow<3>(m)) }, { 70.0 * km, 9.11e-4 * kg / (pow<3>(m)) },
    { 75.0 * km, 6.05e-4 * kg / (pow<3>(m)) }, { 80.0 * km, 4.02e-4 * kg / (pow<3>(m)) }
};

// Altitude Conditions(TABLE 7-4, Vallado)
const std::map<quantity<km>, std::tuple<quantity<km>, quantity<kg / (pow<3>(m))>, quantity<km>>> AtmosphericForce::earthAtmosphere = { // km, (km, kg/m^3, km)
    { 25.0 * km, { 0.0 * km, 1.225 * kg / (pow<3>(m)), 7.249 * km } },
    { 30.0 * km, { 25.0 * km, 3.899e-2 * kg / (pow<3>(m)), 6.349 * km } },
    { 40.0 * km, { 30.0 * km, 1.774e-2 * kg / (pow<3>(m)), 6.682 * km } },
    { 50.0 * km, { 40.0 * km, 3.972e-3 * kg / (pow<3>(m)), 7.554 * km } },
    { 60.0 * km, { 50.0 * km, 1.057e-3 * kg / (pow<3>(m)), 8.382 * km } },
    { 70.0 * km, { 60.0 * km, 3.206e-4 * kg / (pow<3>(m)), 7.714 * km } },
    { 80.0 * km, { 70.0 * km, 8.770e-5 * kg / (pow<3>(m)), 6.549 * km } },
    { 90.0 * km, { 80.0 * km, 1.905e-5 * kg / (pow<3>(m)), 5.799 * km } },
    { 100.0 * km, { 90.0 * km, 3.396e-6 * kg / (pow<3>(m)), 5.382 * km } },
    { 110.0 * km, { 100.0 * km, 5.297e-7 * kg / (pow<3>(m)), 5.877 * km } },
    { 120.0 * km, { 110.0 * km, 9.661e-8 * kg / (pow<3>(m)), 7.263 * km } },
    { 130.0 * km, { 120.0 * km, 2.438e-8 * kg / (pow<3>(m)), 9.473 * km } },
    { 140.0 * km, { 130.0 * km, 8.484e-9 * kg / (pow<3>(m)), 12.636 * km } },
    { 150.0 * km, { 140.0 * km, 3.845e-9 * kg / (pow<3>(m)), 16.149 * km } },
    { 180.0 * km, { 150.0 * km, 2.070e-9 * kg / (pow<3>(m)), 22.523 * km } },
    { 200.0 * km, { 180.0 * km, 5.464e-10 * kg / (pow<3>(m)), 29.740 * km } },
    { 250.0 * km, { 200.0 * km, 2.789e-10 * kg / (pow<3>(m)), 37.105 * km } },
    { 300.0 * km, { 250.0 * km, 7.248e-11 * kg / (pow<3>(m)), 45.546 * km } },
    { 350.0 * km, { 300.0 * km, 2.418e-11 * kg / (pow<3>(m)), 53.628 * km } },
    { 400.0 * km, { 350.0 * km, 9.158e-12 * kg / (pow<3>(m)), 53.298 * km } },
    { 450.0 * km, { 400.0 * km, 3.725e-12 * kg / (pow<3>(m)), 58.515 * km } },
    { 500.0 * km, { 450.0 * km, 1.585e-12 * kg / (pow<3>(m)), 60.828 * km } },
    { 600.0 * km, { 500.0 * km, 6.967e-13 * kg / (pow<3>(m)), 63.822 * km } },
    { 700.0 * km, { 600.0 * km, 1.454e-13 * kg / (pow<3>(m)), 71.835 * km } },
    { 800.0 * km, { 700.0 * km, 3.614e-14 * kg / (pow<3>(m)), 88.667 * km } },
    { 900.0 * km, { 800.0 * km, 1.170e-14 * kg / (pow<3>(m)), 124.64 * km } },
    { 1000.0 * km, { 900.0 * km, 5.245e-15 * kg / (pow<3>(m)), 181.05 * km } },
    { 1100.0 * km, { 1000.0 * km, 2.019e-15 * kg / (pow<3>(m)), 268.00 * km } }
};

const std::map<quantity<km>, quantity<g / (pow<3>(cm))>> AtmosphericForce::titanicAtmosphere = { // km, g/cm^3
    { 780.0 * km, 1.00e-12 * g / (pow<3>(cm)) },  { 790.0 * km, 8.45e-12 * g / (pow<3>(cm)) },
    { 800.0 * km, 7.16e-12 * g / (pow<3>(cm)) },  { 810.0 * km, 6.08e-12 * g / (pow<3>(cm)) },
    { 820.0 * km, 5.17e-12 * g / (pow<3>(cm)) },  { 830.0 * km, 4.41e-12 * g / (pow<3>(cm)) },
    { 840.0 * km, 3.77e-12 * g / (pow<3>(cm)) },  { 850.0 * km, 3.23e-12 * g / (pow<3>(cm)) },
    { 860.0 * km, 2.78e-12 * g / (pow<3>(cm)) },  { 870.0 * km, 2.39e-12 * g / (pow<3>(cm)) },
    { 880.0 * km, 2.06e-12 * g / (pow<3>(cm)) },  { 890.0 * km, 1.78e-12 * g / (pow<3>(cm)) },
    { 900.0 * km, 1.54e-12 * g / (pow<3>(cm)) },  { 910.0 * km, 1.34e-12 * g / (pow<3>(cm)) },
    { 920.0 * km, 1.16e-12 * g / (pow<3>(cm)) },  { 930.0 * km, 1.01e-12 * g / (pow<3>(cm)) },
    { 940.0 * km, 8.80e-13 * g / (pow<3>(cm)) },  { 950.0 * km, 7.67e-13 * g / (pow<3>(cm)) },
    { 960.0 * km, 6.69e-13 * g / (pow<3>(cm)) },  { 970.0 * km, 5.84e-13 * g / (pow<3>(cm)) },
    { 980.0 * km, 5.10e-13 * g / (pow<3>(cm)) },  { 990.0 * km, 4.46e-13 * g / (pow<3>(cm)) },
    { 1000.0 * km, 3.90e-13 * g / (pow<3>(cm)) }, { 1010.0 * km, 1.81e-13 * g / (pow<3>(cm)) },
    { 1020.0 * km, 2.99e-13 * g / (pow<3>(cm)) }, { 1030.0 * km, 2.62e-13 * g / (pow<3>(cm)) },
    { 1040.0 * km, 2.30e-13 * g / (pow<3>(cm)) }, { 1050.0 * km, 2.02e-13 * g / (pow<3>(cm)) },
    { 1060.0 * km, 1.78e-13 * g / (pow<3>(cm)) }, { 1070.0 * km, 1.56e-13 * g / (pow<3>(cm)) },
    { 1080.0 * km, 1.38e-13 * g / (pow<3>(cm)) }, { 1090.0 * km, 1.21e-13 * g / (pow<3>(cm)) },
    { 1100.0 * km, 1.07e-13 * g / (pow<3>(cm)) }, { 1110.0 * km, 9.43e-14 * g / (pow<3>(cm)) },
    { 1120.0 * km, 8.33e-14 * g / (pow<3>(cm)) }, { 1130.0 * km, 7.36e-14 * g / (pow<3>(cm)) },
    { 1140.0 * km, 6.51e-14 * g / (pow<3>(cm)) }, { 1150.0 * km, 5.76e-14 * g / (pow<3>(cm)) },
    { 1160.0 * km, 5.10e-14 * g / (pow<3>(cm)) }, { 1170.0 * km, 4.52e-14 * g / (pow<3>(cm)) },
    { 1180.0 * km, 4.01e-14 * g / (pow<3>(cm)) }, { 1190.0 * km, 3.56e-14 * g / (pow<3>(cm)) },
    { 1200.0 * km, 3.16e-14 * g / (pow<3>(cm)) }, { 1210.0 * km, 2.81e-14 * g / (pow<3>(cm)) },
    { 1220.0 * km, 2.50e-14 * g / (pow<3>(cm)) }, { 1230.0 * km, 2.22e-14 * g / (pow<3>(cm)) },
    { 1240.0 * km, 1.98e-14 * g / (pow<3>(cm)) }, { 1250.0 * km, 1.77e-14 * g / (pow<3>(cm)) },
    { 1260.0 * km, 1.58e-14 * g / (pow<3>(cm)) }, { 1270.0 * km, 1.41e-14 * g / (pow<3>(cm)) },
    { 1280.0 * km, 1.26e-14 * g / (pow<3>(cm)) }, { 1290.0 * km, 1.12e-14 * g / (pow<3>(cm)) },
    { 1300.0 * km, 1.00e-14 * g / (pow<3>(cm)) }
};