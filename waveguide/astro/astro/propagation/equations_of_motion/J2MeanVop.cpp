#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>

#include <algorithm>
#include <cmath>
#include <exception>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <units/units.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace waveguide {
namespace astro {

OrbitalElementPartials J2MeanVop::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{

    const Keplerian elements  = state.in<Keplerian>(get_system());
    const Cartesian cartesian = state.in<Cartesian>(get_system());

    // Extract
    const quantity<km>& a = elements.get_semimajor();
    // const double<rad>& raan = elements.get_right_ascension();
    const quantity<rad>& w     = elements.get_argument_of_perigee();
    const quantity<rad>& theta = elements.get_true_anomaly();

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    const quantity<one>& ecc = (elements.get_eccentricity() < eccTol) ? eccTol : elements.get_eccentricity();
    const quantity<rad>& inc = (elements.get_inclination() < incTol) ? incTol : elements.get_inclination();

    // conversions KEPLERIANs to r and v
    const VelocityVector v = cartesian.get_velocity();
    const RadiusVector r   = cartesian.get_radius();

    const Distance x = cartesian.get_x();
    const Distance y = cartesian.get_y();
    const Distance z = cartesian.get_z();
    const Distance R = r.norm();

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
    */
    const UnitVector Nhat = r.cross(v).unit();

    // Variables to reduce calculations
    const quantity termA = -1.5 * J2 * mu * equitorialR * equitorialR / (R * R * R * R * R);
    const quantity termB = z * z / (R * R);

    // accel due to oblateness
    AccelerationVector accelOblateness = { termA * (1.0 - 5.0 * termB) * x,
                                           termA * (1.0 - 5.0 * termB) * y,
                                           termA * (1.0 - 3.0 * termB) * z };

    // Calculate R, N, and T
    const Acceleration normalPert = accelOblateness.dot(Nhat);

    // h
    const SpecificAngularMomentum h = sqrt(mu * a * (1 - ecc * ecc));

    // Calculate the derivatives of the KEPLERIANs - only raan and w considered
    static const Velocity dadt          = 0.0 * km / s;
    static const UnitlessPerTime deccdt = 0.0 * one / s;
    const AngularRate _dincdt           = R / h * cos(w + theta) * normalPert * rad;
    const AngularRate dthetadt          = h / (R * R) * rad;
    const AngularRate draandt           = R * sin(w + theta) / (h * sin(inc)) * normalPert * rad;
    const AngularRate dwdt              = -draandt * cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    AngularRate dincdt = _dincdt;
    if (inc == incTol && dincdt <= incTol * one / s) {
        dincdt    = 0.0 * rad / s;
        checkflag = true;
    }

    return KeplerianPartial(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);
}

} // namespace astro
} // namespace waveguide