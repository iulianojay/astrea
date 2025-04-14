#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Equinoctial.hpp>
#include <astro/types/typedefs.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;

OrbitalElements EquinoctialVop::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{

    // Get need representations
    const Equinoctial equinoctial = Equinoctial(state, system);
    const Cartesian cartesian     = Cartesian(state, system);

    // Extract
    const quantity<km>& p  = equinoctial.get_semilatus();
    const quantity<one>& f = equinoctial.get_f();
    const quantity<one>& g = equinoctial.get_g();
    const quantity<one>& h = equinoctial.get_h();
    const quantity<one>& k = equinoctial.get_k();
    const quantity<rad>& L = equinoctial.get_true_longitude();

    // R and V
    const quantity<km>& x = cartesian.get_x();
    const quantity<km>& y = cartesian.get_y();
    const quantity<km>& z = cartesian.get_z();
    const quantity<km> R  = sqrt(x * x + y * y + z * z);

    const quantity<km / s>& vx = cartesian.get_vx();
    const quantity<km / s>& vy = cartesian.get_vy();
    const quantity<km / s>& vz = cartesian.get_vz();

    // Define perturbation vectors relative to the satellites SNC body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const quantity<one> Rhatx = x / R;
    const quantity<one> Rhaty = y / R;
    const quantity<one> Rhatz = z / R;

    const quantity<one> ecc                      = sqrt(f * f + g * g);
    const quantity<pow<2>(km) / s> relSpecAngMom = sqrt(mu * a * (1 - ecc * ecc));
    const quantity<one> Nhatx                    = (y * vz - z * vy) / relSpecAngMom;
    const quantity<one> Nhaty                    = (z * vx - x * vz) / relSpecAngMom;
    const quantity<one> Nhatz                    = (x * vy - y * vx) / relSpecAngMom;

    const quantity<one> Tvx = Nhaty * Rhatz - Nhatz * Rhaty;
    const quantity<one> Tvy = Nhatz * Rhatx - Nhatx * Rhatz;
    const quantity<one> Tvz = Nhatx * Rhaty - Nhaty * Rhatx;

    const quantity<one> normTv = sqrt(Tvx * Tvx + Tvy * Tvy + Tvz * Tvz);

    const quantity<one> Thatx = Tvx / normTv;
    const quantity<one> Thaty = Tvy / normTv;
    const quantity<one> Thatz = Tvz / normTv;

    // Function for finding accel caused by perturbations
    const JulianDate julianDate   = vehicle.get_epoch().julian_day() + time;
    AccelerationVector accelPerts = forces.compute_forces(julianDate, cartesian, vehicle, system);

    // Calculate R, N, and T
    const quantity<km / pow<2>(s)> radialPert = accelPerts[0] * Rhatx + accelPerts[1] * Rhaty + accelPerts[2] * Rhatz;
    const quantity<km / pow<2>(s)> normalPert = accelPerts[0] * Nhatx + accelPerts[1] * Nhaty + accelPerts[2] * Nhatz;
    const quantity<km / pow<2>(s)> tangentialPert = accelPerts[0] * Thatx + accelPerts[1] * Thaty + accelPerts[2] * Thatz;

    // Variables precalculated for speed
    const quantity<one> cosL = cos(L);
    const quantity<one> sinL = sin(L);

    const quantity tempA = sqrt(p / mu);
    const quantity tempB = 1.0 + f * cos(L) + g * sin(L);
    const quantity sSq   = 1.0 + h * h + k * k;

    const quantity tempC = (h * sinL - k * cosL) / tempB;
    const quantity tempD = tempA * sSq / (2 * tempB);

    // Derivative functions
    const quantity<km / s> dpdt = 2 * p / tempB * tempA * tangentialPert;
    const quantity<one / s> dfdt =
        tempA * (radialPert * sinL + ((tempB + 1) * cosL + f) / tempB * tangentialPert - g * tempC * normalPert);
    const quantity<one / s> dgdt =
        tempA * (-radialPert * cosL + ((tempB + 1) * sinL + g) / tempB * tangentialPert + f * tempC * normalPert);
    const quantity<one / s> dhdt = tempD * cosL * normalPert;
    const quantity<one / s> dkdt = tempD * sinL * normalPert;
    const quantity<rad / s> dLdt = sqrt(mu * p) * tempB * tempB / (p * p) + tempA * tempC * normalPert;

    const Equinoctial dsdt(dpdt * s, dfdt * s, dgdt * s, dhdt * s, dkdt * s, dLdt * s);

    return OrbitalElements(dsdt);
}