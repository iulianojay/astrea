#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

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

OrbitalElementPartials KeplerianVop::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
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
    const quantity<one>& ecc = (elements.get_eccentricity() < checkTol * one) ? checkTol * one : elements.get_eccentricity();
    const quantity<rad>& inc = (elements.get_inclination() < checkTol * rad) ? checkTol * rad : elements.get_inclination();

    if (doWarn) { check_degenerate(ecc, inc); }

    // h
    const quantity<pow<2>(km) / s> h = sqrt(mu * a * (1 - ecc * ecc));

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
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const quantity<one> Rhatx = x / R;
    const quantity<one> Rhaty = y / R;
    const quantity<one> Rhatz = z / R;

    const quantity<one> Nhatx = (y * vz - z * vy) / h;
    const quantity<one> Nhaty = (z * vx - x * vz) / h;
    const quantity<one> Nhatz = (x * vy - y * vx) / h;

    const quantity<one> Tvx = Nhaty * Rhatz - Nhatz * Rhaty;
    const quantity<one> Tvy = Nhatz * Rhatx - Nhatx * Rhatz;
    const quantity<one> Tvz = Nhatx * Rhaty - Nhaty * Rhatx;

    const quantity<one> normTv = sqrt(Tvx * Tvx + Tvy * Tvy + Tvz * Tvz);

    const quantity<one> Thatx = Tvx / normTv;
    const quantity<one> Thaty = Tvy / normTv;
    const quantity<one> Thatz = Tvz / normTv;

    // Function for finding accel caused by perturbations
    const JulianDate julianDate   = (vehicle.get_epoch() + time).julian_day();
    AccelerationVector accelPerts = forces.compute_forces(julianDate, cartesian, vehicle, system);

    // Calculate R, N, and T
    const quantity<km / pow<2>(s)> radialPert = accelPerts[0] * Rhatx + accelPerts[1] * Rhaty + accelPerts[2] * Rhatz;
    const quantity<km / pow<2>(s)> normalPert = accelPerts[0] * Nhatx + accelPerts[1] * Nhaty + accelPerts[2] * Nhatz;
    const quantity<km / pow<2>(s)> tangentialPert = accelPerts[0] * Thatx + accelPerts[1] * Thaty + accelPerts[2] * Thatz;

    // Argument of latitude
    const quantity<rad> u = w + theta;

    // Precalculate
    const quantity cosTA = cos(theta);
    const quantity sinTA = sin(theta);
    const quantity cosU  = cos(u);
    const quantity sinU  = sin(u);

    const quantity<pow<4>(km) / pow<2>(s)> hSquared = h * h;
    const quantity<one / s> hOverRSquared           = h / (R * R);

    // Calculate the derivatives of the Keplerian elements
    const quantity<pow<2>(km / s)> dhdt = R * tangentialPert;
    const quantity<one / s> deccdt =
        h / mu * sinTA * radialPert + 1 / (mu * h) * ((hSquared + mu * R) * cosTA + mu * ecc * R) * tangentialPert;
    const quantity<rad / s> dincdt = R / h * cosU * normalPert;
    const quantity<rad / s> dthetadt =
        hOverRSquared + (1 / (ecc * h)) * ((hSquared / mu) * cosTA * radialPert - (hSquared / mu + R) * sinTA * tangentialPert);
    const quantity<rad / s> draandt = R * sinU / (h * sin(inc)) * normalPert;
    const quantity<rad / s> dwdt    = -dthetadt + (hOverRSquared - draandt * cos(inc));

    // const quantity<km/s> dadt = (-2*mu/(h*h*h)*dhdt)*(1 - ecc*ecc) + (mu/(h*h))*(-2*ecc*deccdt); // TODO: Fix this
    const quantity<km / s> dadt = 2 / (mu * (1 - ecc * ecc)) * (h * dhdt + a * mu * ecc * deccdt);
    // km^3/s^2 / km^6/s^3 * km^2/s^2 -> km^-1 * s^-1 + km^3/s^2 / km^4/s^2 * 1/s -> km^-1 / s^-1
    const KeplerianPartial dsdt(dadt, deccdt, dincdt, draandt, dwdt, dthetadt);

    return dsdt;
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