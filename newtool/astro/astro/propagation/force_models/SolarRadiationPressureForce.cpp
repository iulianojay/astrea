#include <astro/propagation/force_models/SolarRadiationPressureForce.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;


AccelerationVector
    SolarRadiationPressureForce::compute_force(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Extract
    const auto& x    = state.get_x();
    const auto& y    = state.get_y();
    const auto& z    = state.get_z();
    const quantity R = sqrt(x * x + y * y + z * z);

    // Central body properties
    static const quantity& equitorialR = center->get_equitorial_radius();
    static const bool isSun            = (center->get_name() != "Sun");

    // Find day nearest to current time
    const State& stateSunToCenter        = (center->get_closest_state(julianDate));
    const RadiusVector radiusSunToCenter = stateSunToCenter.elements.to_cartesian(sys).get_radius();

    // Radius from central body to sun
    const RadiusVector radiusCenterToSun{ // flip vector direction
                                          -radiusSunToCenter[0],
                                          -radiusSunToCenter[1],
                                          -radiusSunToCenter[2]
    };
    const quantity radialMagnitudeCenterToSun = sqrt(
        radiusCenterToSun[0] * radiusCenterToSun[0] + radiusCenterToSun[1] * radiusCenterToSun[1] +
        radiusCenterToSun[2] * radiusCenterToSun[2]
    );

    const RadiusVector radiusVehicleToSun{ radiusCenterToSun[0] - x, radiusCenterToSun[1] - y, radiusCenterToSun[2] - z };
    const quantity rMagVehicleToSun = sqrt(
        radiusVehicleToSun[0] * radiusVehicleToSun[0] + radiusVehicleToSun[1] * radiusVehicleToSun[1] +
        radiusVehicleToSun[2] * radiusVehicleToSun[2]
    );

    // Solar radiation pressure
    const quantity solarRadiationPressure =
        SRP_1AU * (au * au) / (rMagVehicleToSun * rMagVehicleToSun); // Scale by(1AU/R)^2 for other bodies
    quantity fractionOfRecievedSunlight = 1.0 * one;
    if (isSun) {
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        const quantity refAngle =
            acos((radiusCenterToSun[0] * x + radiusCenterToSun[1] * y + radiusCenterToSun[2] * z) / (radialMagnitudeCenterToSun * R));
        const quantity refAngle1 = acos(equitorialR / R);
        const quantity refAngle2 = acos(equitorialR / radialMagnitudeCenterToSun);

        if (refAngle1 + refAngle2 <= refAngle) { // In shadow
            static const quantity diamSun = 696000.0 * km;
            const quantity Xu             = equitorialR * radialMagnitudeCenterToSun / (diamSun - equitorialR);

            const RadiusVector rP{ -Xu * radiusCenterToSun[0] / radialMagnitudeCenterToSun,
                                   -Xu * radiusCenterToSun[1] / radialMagnitudeCenterToSun,
                                   -Xu * radiusCenterToSun[2] / radialMagnitudeCenterToSun };
            const double normRP = sqrt(rP[0] * rP[0] + rP[1] * rP[1] + rP[2] * rP[2]);

            const RadiusVector rPs{ x - rP[0], y - rP[1], z - rP[2] };
            const quantity normRPs = sqrt(rPs[0] * rPs[0] + rPs[1] * rPs[1] + rPs[2] * rPs[2]);
            const quantity alphaps = abs(asin((-rPs[0] * rP[0] - rPs[1] * rP[1] - rPs[2] * rP[2]) / (normRP * normRPs)));

            if (alphaps < asin(equitorialR / Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0 * one;
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5 * one;
            }
        }
    }

    // accel due to srp
    const quantity coefficientOfReflectivity = vehicle.get_coefficient_of_reflectivity();
    const quantity areaSun                   = vehicle.get_solar_area();
    const quantity mass                      = vehicle.get_mass();
    const quantity tempA = -solarRadiationPressure * coefficientOfReflectivity * (areaSun) / mass / rMagVehicleToSun *
                           fractionOfRecievedSunlight;

    const AccelerationVector accelSRP{ tempA * radiusVehicleToSun[0], tempA * radiusVehicleToSun[1], tempA * radiusVehicleToSun[2] };

    return accelSRP;
}