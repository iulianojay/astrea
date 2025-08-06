#include <astro/propagation/force_models/SolarRadiationPressure.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;

namespace waveguide {
namespace astro {

AccelerationVector<ECI>
    SolarRadiationPressure::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_center();

    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();
    const Distance R  = sqrt(x * x + y * y + z * z);

    // Central body properties
    static const Distance& equitorialR = center->get_equitorial_radius();
    static const bool isSun            = (center->get_name() != "Sun");

    // Find day nearest to current time
    const State& stateSunToCenter             = center->get_state_at(date); // assumes center is a planet
    const RadiusVector<ECI> radiusSunToCenter = stateSunToCenter.get_elements().in<Cartesian>(sys).get_radius();

    // Radius from central body to sun
    const RadiusVector<ECI> radiusCenterToSun{ // flip vector direction
                                               -radiusSunToCenter[0],
                                               -radiusSunToCenter[1],
                                               -radiusSunToCenter[2]
    };
    const Distance radialMagnitudeCenterToSun = sqrt(
        radiusCenterToSun[0] * radiusCenterToSun[0] + radiusCenterToSun[1] * radiusCenterToSun[1] +
        radiusCenterToSun[2] * radiusCenterToSun[2]
    );

    const RadiusVector<ECI> radiusVehicleToSun{ radiusCenterToSun[0] - x, radiusCenterToSun[1] - y, radiusCenterToSun[2] - z };
    const Distance radialMagnitudeVehicleToSun = sqrt(
        radiusVehicleToSun[0] * radiusVehicleToSun[0] + radiusVehicleToSun[1] * radiusVehicleToSun[1] +
        radiusVehicleToSun[2] * radiusVehicleToSun[2]
    );

    // Average solar radiation pressure at 1 AU
    static const quantity<N / pow<2>(m)> SRP_1AU = 4.556485540406757e-6 * N / pow<2>(m);

    // Scaled to average distance from Sun
    const quantity<kg / (m * pow<2>(s))> solarRadiationPressure =
        SRP_1AU * (au * au) / (radialMagnitudeVehicleToSun * radialMagnitudeVehicleToSun); // Scale by(1AU/R)^2 for other bodies

    // Scale by umbria/penumbra
    Unitless fractionOfRecievedSunlight = 1.0 * one;
    if (!isSun) {
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        const Angle refAngle = angular::acos(
            (radiusCenterToSun[0] * x + radiusCenterToSun[1] * y + radiusCenterToSun[2] * z) / (radialMagnitudeCenterToSun * R)
        );
        const Angle refAngle1 = angular::acos(equitorialR / R);
        const Angle refAngle2 = angular::acos(equitorialR / radialMagnitudeCenterToSun);

        if (refAngle1 + refAngle2 <= refAngle) { // In shadow
            static const Distance diamSun = 696000.0 * km;
            const Distance Xu             = equitorialR * radialMagnitudeCenterToSun / (diamSun - equitorialR);

            const RadiusVector<ECI> rP{ -Xu * radiusCenterToSun[0] / radialMagnitudeCenterToSun,
                                        -Xu * radiusCenterToSun[1] / radialMagnitudeCenterToSun,
                                        -Xu * radiusCenterToSun[2] / radialMagnitudeCenterToSun };
            const Distance normRP = sqrt(rP[0] * rP[0] + rP[1] * rP[1] + rP[2] * rP[2]);

            const RadiusVector<ECI> rPs{ x - rP[0], y - rP[1], z - rP[2] };
            const Distance normRPs = sqrt(rPs[0] * rPs[0] + rPs[1] * rPs[1] + rPs[2] * rPs[2]);
            const Angle alphaps = abs(angular::asin((-rPs[0] * rP[0] - rPs[1] * rP[1] - rPs[2] * rP[2]) / (normRP * normRPs)));

            if (alphaps < angular::asin(equitorialR / Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0 * one;
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5 * one;
            }
        }
    }

    // accel due to srp
    const Unitless coefficientOfReflectivity = vehicle.get_coefficient_of_reflectivity();
    const SurfaceArea areaSun                = vehicle.get_solar_area();
    const Mass mass                          = vehicle.get_mass();
    const quantity accelRelativeMagnitude    = -solarRadiationPressure * coefficientOfReflectivity * (areaSun) / mass /
                                            radialMagnitudeVehicleToSun * fractionOfRecievedSunlight;

    const AccelerationVector<ECI> accelSRP{ accelRelativeMagnitude * radiusVehicleToSun[0],
                                            accelRelativeMagnitude * radiusVehicleToSun[1],
                                            accelRelativeMagnitude * radiusVehicleToSun[2] };

    return accelSRP;
}

} // namespace astro
} // namespace waveguide