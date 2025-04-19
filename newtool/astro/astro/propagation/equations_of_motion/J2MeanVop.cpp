#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>

#include <algorithm>
#include <cmath>
#include <exception>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/constants/astronomical_constants.h>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

OrbitalElementPartials J2MeanVop::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{

    const Keplerian elements  = Keplerian(state, system);
    const Cartesian cartesian = Cartesian(state, system);

    // Extract
    const quantity<km>& a = elements.get_semimajor();
    // const double<rad>& raan = elements.get_right_ascension();
    const quantity<rad>& w     = elements.get_argument_of_perigee();
    const quantity<rad>& theta = elements.get_true_anomaly();

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    const quantity<one>& ecc = (elements.get_eccentricity() < eccTol) ? eccTol : elements.get_eccentricity();
    const quantity<rad>& inc = (elements.get_inclination() < incTol) ? incTol : elements.get_inclination();

    // h
    const quantity h = sqrt(mu * a * (1 - ecc * ecc));

    // conversions KEPLERIANs to r and v
    const quantity<km>& x = cartesian.get_x();
    const quantity<km>& y = cartesian.get_y();
    const quantity<km>& z = cartesian.get_z();
    const quantity<km> R  = sqrt(x * x + y * y + z * z);

    const quantity<km / s>& vx = cartesian.get_vx();
    const quantity<km / s>& vy = cartesian.get_vy();
    const quantity<km / s>& vz = cartesian.get_vz();

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
    */
    const quantity<one> Nhatx = (y * vz - z * vy) / h;
    const quantity<one> Nhaty = (z * vx - x * vz) / h;
    const quantity<one> Nhatz = (x * vy - y * vx) / h;

    // Variables to reduce calculations
    const quantity tempA = -1.5 * J2 * mu * equitorialR * equitorialR / (R * R * R * R * R);
    const quantity tempB = z * z / (R * R);

    // accel due to oblateness
    AccelerationVector accelOblateness = { tempA * (1.0 - 5.0 * tempB) * x,
                                           tempA * (1.0 - 5.0 * tempB) * y,
                                           tempA * (1.0 - 3.0 * tempB) * z };

    // Calculate R, N, and T
    const quantity<km / pow<2>(s)> normalPert =
        accelOblateness[0] * Nhatx + accelOblateness[1] * Nhaty + accelOblateness[2] * Nhatz;

    // Calculate the derivatives of the KEPLERIANs - only raan and w considered
    const quantity<km / s> dadt      = 0.0 * km / s;
    const quantity<one / s> deccdt   = 0.0 * one / s;
    const quantity<rad / s> _dincdt  = R / h * cos(w + theta) * normalPert;
    const quantity<rad / s> dthetadt = h / (R * R);
    const quantity<rad / s> draandt  = R * sin(w + theta) / (h * sin(inc)) * normalPert;
    const quantity<rad / s> dwdt     = -draandt * cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    quantity<rad / s> dincdt = _dincdt;
    if (inc == incTol && dincdt <= incTol * one / s) {
        dincdt    = 0.0 * rad / s;
        checkflag = true;
    }

    const KeplerianPartial dsdt(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);

    return dsdt;
}