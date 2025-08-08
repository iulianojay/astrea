#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>
#include <units/units.hpp>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Equinoctial.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace waveguide {
namespace astro {

OrbitalElementPartials EquinoctialVop::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{

    // Get need representations
    const Equinoctial equinoctial = state.in<Equinoctial>(get_system());
    const Cartesian cartesian     = state.in<Cartesian>(get_system());

    // Extract
    const Distance& p = equinoctial.get_semilatus();
    const Unitless& f = equinoctial.get_f();
    const Unitless& g = equinoctial.get_g();
    const Unitless& h = equinoctial.get_h();
    const Unitless& k = equinoctial.get_k();
    const Angle& L    = equinoctial.get_true_longitude();

    // R and V
    const VelocityVector<ECI> v = cartesian.get_velocity();
    const RadiusVector<ECI> r   = cartesian.get_position();

    // Define perturbation vectors relative to the satellites SNC body frame
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
    const RTN rtnFrame(vehicle);
    const AccelerationVector<RTN> accelRtn = rtnFrame.rotate_into_this_frame(accelPerts, date);

    const Acceleration radialPert     = accelPerts.dot(Rhat);
    const Acceleration normalPert     = accelPerts.dot(Nhat);
    const Acceleration tangentialPert = accelPerts.dot(That);

    // Variables precalculated for speed
    const Unitless cosL = cos(L);
    const Unitless sinL = sin(L);

    const quantity termA = sqrt(p / mu);
    const quantity termB = 1.0 + f * cosL + g * sinL;
    const quantity sSq   = 1.0 + h * h + k * k;

    const quantity termC = (h * sinL - k * cosL) / termB;
    const quantity termD = termA * sSq / (2.0 * termB);

    // Derivative functions
    const Velocity dpdt = 2.0 * p / termB * termA * tangentialPert;
    const UnitlessPerTime dfdt =
        termA * (radialPert * sinL + ((termB + 1) * cosL + f) / termB * tangentialPert - g * termC * normalPert);
    const UnitlessPerTime dgdt =
        termA * (-radialPert * cosL + ((termB + 1) * sinL + g) / termB * tangentialPert + f * termC * normalPert);
    const UnitlessPerTime dhdt = termD * cosL * normalPert;
    const UnitlessPerTime dkdt = termD * sinL * normalPert;
    const AngularRate dLdt = (sqrt(mu * p) * termB * termB / (p * p) + termA * termC * normalPert) * (isq_angle::cotes_angle);

    return EquinoctialPartial(dpdt, dfdt, dgdt, dhdt, dkdt, dLdt);
}

} // namespace astro
} // namespace waveguide