#include <astro/propagation/force_models/SolarRadiationPressure.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>


namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::non_si::unit_symbols::au;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

AccelerationVector<frames::earth::icrf>
    SolarRadiationPressure::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_central_body();

    // Extract
    const Distance& x                         = state.get_x();
    const Distance& y                         = state.get_y();
    const Distance& z                         = state.get_z();
    const RadiusVector<frames::earth::icrf> r = state.get_position();
    const Distance R                          = sqrt(x * x + y * y + z * z);

    // Central body properties
    static const Distance& equitorialR = center->get_equitorial_radius();
    static const bool isSun            = (center->get_name() == "Sun");

    // Find day nearest to current time
    const OrbitalElements& stateSunToCenter = center->get_elements_at(date); // assumes center is a planet
    const RadiusVector<frames::earth::icrf> radiusSunToCenter = stateSunToCenter.in_element_set<Cartesian>(sys).get_position();

    // Radius from central body to sun
    const RadiusVector<frames::earth::icrf> radiusCenterToSun = -radiusSunToCenter;
    const Distance radialMagnitudeCenterToSun                 = radiusCenterToSun.norm();

    const RadiusVector<frames::earth::icrf> radiusVehicleToSun = radiusCenterToSun - r;
    const Distance radialMagnitudeVehicleToSun                 = radiusVehicleToSun.norm();

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

            const RadiusVector<frames::earth::icrf> rP = -Xu * radiusCenterToSun / radialMagnitudeCenterToSun;
            const Distance normRP                      = rP.norm();

            const RadiusVector<frames::earth::icrf> rPs = r - rP;
            const Distance normRPs                      = rPs.norm();
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

    const AccelerationVector<frames::earth::icrf> accelSRP = { accelRelativeMagnitude * radiusVehicleToSun[0],
                                                               accelRelativeMagnitude * radiusVehicleToSun[1],
                                                               accelRelativeMagnitude * radiusVehicleToSun[2] };

    return accelSRP;
}

} // namespace astro
} // namespace astrea