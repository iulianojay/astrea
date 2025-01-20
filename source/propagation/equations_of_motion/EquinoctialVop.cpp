#include "EquinoctialVop.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "astro/types/typedefs.hpp"
#include "astro/element_sets/orbital_elements/Equinoctial.hpp"
#include "astro/element_sets/orbital_elements/Cartesian.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;

OrbitalElements EquinoctialVop::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const {

    // Get need representations
    const Equinoctial equinoctial = state.to_equinoctial(system);
    const Cartesian cartesian = state.to_cartesian(system);

    // Extract
    const quantity<km>& p = equinoctial.get_semilatus();
    const quantity<one>& f = equinoctial.get_f();
    const quantity<one>& g = equinoctial.get_g();
    const quantity<one>& h = equinoctial.get_h();
    const quantity<one>& k = equinoctial.get_k();
    const quantity<rad>& L = equinoctial.get_true_longitude();

    // R and V
    const quantity<km>& x = cartesian.get_x();
    const quantity<km>& y = cartesian.get_y();
    const quantity<km>& z = cartesian.get_z();
    const quantity R = sqrt(x*x + y*y + z*z);

    const quantity<km/s>& vx = cartesian.get_vx();
    const quantity<km/s>& vy = cartesian.get_vy();
    const quantity<km/s>& vz = cartesian.get_vz();

    // Define perturbation vectors relative to the satellites SNC body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const quantity Rhatx = x/R;
    const quantity Rhaty = y/R;
    const quantity Rhatz = z/R;

    const quantity Nhatx = (y*vz - z*vy)/h;
    const quantity Nhaty = (z*vx - x*vz)/h;
    const quantity Nhatz = (x*vy - y*vx)/h;

    const quantity Tvx = Nhaty*Rhatz - Nhatz*Rhaty;
    const quantity Tvy = Nhatz*Rhatx - Nhatx*Rhatz;
    const quantity Tvz = Nhatx*Rhaty - Nhaty*Rhatx;

    const quantity normTv = sqrt(Tvx*Tvx + Tvy*Tvy + Tvz*Tvz);

    const quantity Thatx = Tvx/normTv;
    const quantity Thaty = Tvy/normTv;
    const quantity Thatz = Tvz/normTv;

    // Function for finding accel caused by perturbations
    const auto julianDate = vehicle.get_epoch().julian_day() + time.count<days>();
    AccelerationVector accelPerts = forces.compute_forces(julianDate, cartesianState, vehicle, system);

    // Calculate R, N, and T
    const quantity radialPert     = accelPerts[0]*Rhatx + accelPerts[1]*Rhaty + accelPerts[2]*Rhatz;
    const quantity normalPert     = accelPerts[0]*Nhatx + accelPerts[1]*Nhaty + accelPerts[2]*Nhatz;
    const quantity tangentialPert = accelPerts[0]*Thatx + accelPerts[1]*Thaty + accelPerts[2]*Thatz;

    // Variables precalculated for speed
    const quantity cosL = cos(L);
    const quantity sinL = sin(L);

    const quantity tempA = sqrt(p/mu);
    const quantity tempB = 1.0 + f*cos(L) + g*sin(L);
    const quantity sSq = 1.0 + h*h + k*k;

    const quantity tempC = (h*sinL - k*cosL)/tempB;
    const quantity tempD = tempA*sSq/(2*tempB);

    // Derivative functions
    const OrbitalElements dsdt({
        2*p/tempB*tempA*tangentialPert,                                                                 // dpdt
        tempA*( radialPert*sinL + ((tempB + 1)*cosL + f)/tempB*tangentialPert - g*tempC*normalPert),    // dfdt
        tempA*(-radialPert*cosL + ((tempB + 1)*sinL + g)/tempB*tangentialPert + f*tempC*normalPert),    // dgdt
        tempD*cosL*normalPert,                                                                          // dhdt
        tempD*sinL*normalPert,                                                                          // dkdt
        sqrt(mu*p)*tempB*tempB/(p*p) + tempA*tempC*normalPert                                           // dLdt
    }, ElementSet::EQUINOCTIAL);

    return dsdt;
}