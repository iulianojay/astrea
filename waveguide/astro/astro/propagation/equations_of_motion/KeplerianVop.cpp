#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
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

OrbitalElementPartials KeplerianVop::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
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
    const quantity<one>& ecc = (elements.get_eccentricity() < checkTol * one) ? checkTol * one : elements.get_eccentricity();
    const quantity<rad>& inc = (elements.get_inclination() < checkTol * rad) ? checkTol * rad : elements.get_inclination();

    if (doWarn) { check_degenerate(ecc, inc); }

    // h
    const SpecificAngularMomentum h = sqrt(mu * a * (1 - ecc * ecc));

    // conversions KEPLERIANs to r and v
    const VelocityVector<ECI> v = cartesian.get_velocity();
    const RadiusVector<ECI> r   = cartesian.get_radius();

    const Distance x = cartesian.get_x();
    const Distance y = cartesian.get_y();
    const Distance z = cartesian.get_z();
    const Distance R = r.norm();

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const UnitVector Rhat = r.unit();
    const UnitVector Nhat = r.cross(v).unit();
    const UnitVector That = Nhat.cross(Rhat).unit();

    // Function for finding accel caused by perturbations
    const Date date                    = vehicle.get_state().get_epoch();
    AccelerationVector<ECI> accelPerts = forces.compute_forces(date, cartesian, vehicle, get_system());

    // Calculate R, N, and T
    const Acceleration radialPert     = accelPerts.dot(Rhat);
    const Acceleration normalPert     = accelPerts.dot(Nhat);
    const Acceleration tangentialPert = accelPerts.dot(That);

    // Argument of latitude
    const Angle u = w + theta;

    // Precalculate
    const Unitless cosTA = cos(theta);
    const Unitless sinTA = sin(theta);
    const Unitless cosU  = cos(u);
    const Unitless sinU  = sin(u);

    const quantity hSquared             = h * h;
    const UnitlessPerTime hOverRSquared = h / (R * R);

    // Calculate the derivatives of the Keplerian elements
    const quantity dhdt = R * tangentialPert;
    const UnitlessPerTime deccdt =
        h / mu * sinTA * radialPert + 1.0 / (mu * h) * ((hSquared + mu * R) * cosTA + mu * ecc * R) * tangentialPert;
    const Velocity dadt      = 2.0 / (mu * (1 - ecc * ecc)) * (h * dhdt + a * mu * ecc * deccdt);
    const AngularRate dincdt = R / h * cosU * normalPert * (isq_angle::cotes_angle);
    const AngularRate dthetadt =
        (hOverRSquared + (1 / (ecc * h)) * ((hSquared / mu) * cosTA * radialPert - (hSquared / mu + R) * sinTA * tangentialPert)) *
        (isq_angle::cotes_angle);
    const AngularRate draandt = R * sinU / (h * sin(inc)) * normalPert * (isq_angle::cotes_angle);
    const AngularRate dwdt    = (-dthetadt + (hOverRSquared * isq_angle::cotes_angle - draandt * cos(inc)));


    return KeplerianPartial(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);
}

void KeplerianVop::check_degenerate(const quantity<one>& ecc, const quantity<rad>& inc) const
{
    if (ecc <= checkTol * one || inc <= checkTol * rad) {
        std::string title;
        if (ecc <= checkTol * one && inc <= checkTol * rad) { title = "Eccentricity and inclination"; }
        else if (ecc <= checkTol * one) {
            title = "Eccentricity";
        }
        else {
            title = "Inclination";
        }
        std::cout << "WARNING: Degenerate case. " << title << " smaller than acceptable tolerance (" << checkTol
                  << "). Results may be inaccurate." << std::endl
                  << std::endl;
    }
}

} // namespace astro
} // namespace waveguide