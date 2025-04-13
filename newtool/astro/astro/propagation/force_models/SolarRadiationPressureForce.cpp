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
    const quantity<km>& x = state.get_x();
    const quantity<km>& y = state.get_y();
    const quantity<km>& z = state.get_z();
    const quantity<km> R  = sqrt(x * x + y * y + z * z);

    // Central body properties
    static const quantity<km>& equitorialR = center->get_equitorial_radius();
    static const bool isSun                = (center->get_name() != "Sun");

    // Find day nearest to current time
    const State& stateSunToCenter        = (center->get_closest_state(julianDate));
    const RadiusVector radiusSunToCenter = stateSunToCenter.elements.to_cartesian(sys).get_radius();

    // Radius from central body to sun
    const RadiusVector radiusCenterToSun{ // flip vector direction
                                          -radiusSunToCenter[0],
                                          -radiusSunToCenter[1],
                                          -radiusSunToCenter[2]
    };
    const quantity<km> radialMagnitudeCenterToSun = sqrt(
        radiusCenterToSun[0] * radiusCenterToSun[0] + radiusCenterToSun[1] * radiusCenterToSun[1] +
        radiusCenterToSun[2] * radiusCenterToSun[2]
    );

    const RadiusVector radiusVehicleToSun{ radiusCenterToSun[0] - x, radiusCenterToSun[1] - y, radiusCenterToSun[2] - z };
    const quantity<km> radialMagnitudeVehicleToSun = sqrt(
        radiusVehicleToSun[0] * radiusVehicleToSun[0] + radiusVehicleToSun[1] * radiusVehicleToSun[1] +
        radiusVehicleToSun[2] * radiusVehicleToSun[2]
    );

    // Solar radiation pressure
    const quantity<kN / pow<2>(km)> solarRadiationPressure =
        SRP_1AU * (au * au) / (radialMagnitudeVehicleToSun * radialMagnitudeVehicleToSun); // Scale by(1AU/R)^2 for other bodies
    quantity<one> fractionOfRecievedSunlight = 1.0 * one;
    if (isSun) {
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        const quantity<rad> refAngle =
            acos((radiusCenterToSun[0] * x + radiusCenterToSun[1] * y + radiusCenterToSun[2] * z) / (radialMagnitudeCenterToSun * R));
        const quantity<rad> refAngle1 = acos(equitorialR / R);
        const quantity<rad> refAngle2 = acos(equitorialR / radialMagnitudeCenterToSun);

        if (refAngle1 + refAngle2 <= refAngle) { // In shadow
            static const quantity<km> diamSun = 696000.0 * km;
            const quantity<km> Xu             = equitorialR * radialMagnitudeCenterToSun / (diamSun - equitorialR);

            const RadiusVector rP{ -Xu * radiusCenterToSun[0] / radialMagnitudeCenterToSun,
                                   -Xu * radiusCenterToSun[1] / radialMagnitudeCenterToSun,
                                   -Xu * radiusCenterToSun[2] / radialMagnitudeCenterToSun };
            const quantity<km> normRP = sqrt(rP[0] * rP[0] + rP[1] * rP[1] + rP[2] * rP[2]);

            const RadiusVector rPs{ x - rP[0], y - rP[1], z - rP[2] };
            const quantity<km> normRPs = sqrt(rPs[0] * rPs[0] + rPs[1] * rPs[1] + rPs[2] * rPs[2]);
            const quantity<rad> alphaps = abs(asin((-rPs[0] * rP[0] - rPs[1] * rP[1] - rPs[2] * rP[2]) / (normRP * normRPs)));

            if (alphaps < asin(equitorialR / Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0 * one;
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5 * one;
            }
        }
    }

    // accel due to srp
    const quantity<one> coefficientOfReflectivity = vehicle.get_coefficient_of_reflectivity();
    const quantity<pow<2>(m)> areaSun             = vehicle.get_solar_area();
    const quantity<kg> mass                       = vehicle.get_mass();
    const auto tempA                              = -solarRadiationPressure * coefficientOfReflectivity * (areaSun) / mass / rMagVehicleToSun * fractionOfRecievedSunlight;

    const AccelerationVector accelSRP{ tempA * radiusVehicleToSun[0], tempA * radiusVehicleToSun[1], tempA * radiusVehicleToSun[2] };

    return accelSRP;
}