/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/force_models/instances/SolarRadiationPressure.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;

using mp_units::pow;
using mp_units::angular::acos;
using mp_units::angular::asin;

using mp_units::one;
using mp_units::non_si::unit_symbols::au;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

Perturbation SolarRadiationPressure::compute_perturbation(const State& state, const Vehicle& vehicle) const
{
    // Extract
    const AstrodynamicsSystem& sys       = state.get_system();
    const Date date                      = state.get_epoch();
    const CelestialBodyUniquePtr& center = sys.get_central_body();
    const CelestialBodyUniquePtr& sun    = sys.add_body(CelestialBodyId::SUN);

    const RadiusVector<frames::earth::icrf> rCenterToVehicle = state.get_position<frames::earth::icrf>();
    const Distance rMagCenterToVehicle                       = rCenterToVehicle.norm();

    // Central body properties
    const bool isSun = (center->get_id() == CelestialBodyId::SUN);

    // Find day nearest to current time
    const RadiusVector<frames::solar_system_barycenter::icrf> rSsbToCenter = center->get_position_at(date);
    const RadiusVector<frames::solar_system_barycenter::icrf> rSsbToSun    = sun->get_position_at(date);

    // Radius from central body to sun
    const RadiusVector<frames::earth::icrf> rCenterToSun =
        (rSsbToSun - rSsbToCenter).force_frame_conversion<frames::earth::icrf>(); // TODO: Should this use the translate function? I hate that function.
    const Distance rMagCenterToSun = rCenterToSun.norm();

    const RadiusVector<frames::earth::icrf> rVehicleToSun = rCenterToSun - rCenterToVehicle;
    const Distance rMagVehicleToSun                       = rVehicleToSun.norm();

    // Average solar radiation pressure at 1 AU scaled to average distance from Sun
    static const quantity<N / pow<2>(m)> srpAtOneAU = 4.556485540406757e-6 * N / pow<2>(m);
    const quantity<N / pow<2>(m)> srp =
        srpAtOneAU * (au * au) / (rMagVehicleToSun * rMagVehicleToSun); // Scale by(1AU/R)^2 for other bodies

    // Scale by umbria/penumbra
    Unitless fractionOfRecievedSunlight = 1.0 * one;
    if (!isSun) {
        static const Distance& equitorialR = center->get_equitorial_radius();

        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details.
        const Angle refAngle  = acos(rCenterToSun.dot(rCenterToVehicle) / (rMagCenterToSun * rMagCenterToVehicle));
        const Angle refAngle1 = acos(equitorialR / rMagCenterToVehicle);
        const Angle refAngle2 = acos(equitorialR / rMagCenterToSun);

        if (refAngle1 + refAngle2 <= refAngle) { // In shadow
            static const Distance diamSun = 696000.0 * km;
            const Distance Xu             = equitorialR * rMagCenterToSun / (diamSun - equitorialR);

            const RadiusVector<frames::earth::icrf> rP = -Xu * rCenterToSun / rMagCenterToSun;
            const Distance normRP                      = rP.norm();

            const RadiusVector<frames::earth::icrf> rPs = rCenterToVehicle - rP;
            const Distance normRPs                      = rPs.norm();
            const Angle alphaps                         = abs(asin(-rPs.dot(rP) / (normRP * normRPs)));

            if (alphaps < asin(equitorialR / Xu)) { // Umbra
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
    const Force forceRelMag                  = -srp * fractionOfRecievedSunlight * coefficientOfReflectivity * areaSun;

    return { .force = forceRelMag * rVehicleToSun / rMagVehicleToSun };
}

} // namespace astro
} // namespace astrea