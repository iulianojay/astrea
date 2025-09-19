#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

EquinoctialVop::EquinoctialVop(const AstrodynamicsSystem& system, const ForceModel& forces) :
    EquationsOfMotion(system),
    forces(&forces),
    mu(system.get_mu())
{
}

OrbitalElementPartials EquinoctialVop::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{

    // Get need representations
    const Equinoctial equinoctial = state.in_element_set<Equinoctial>(get_system());
    const Cartesian cartesian     = state.in_element_set<Cartesian>(get_system());

    // Extract
    const Distance& p = equinoctial.get_semilatus();
    const Unitless& f = equinoctial.get_f();
    const Unitless& g = equinoctial.get_g();
    const Unitless& h = equinoctial.get_h();
    const Unitless& k = equinoctial.get_k();
    const Angle& L    = equinoctial.get_true_longitude();

    // R and V
    const RadiusVector<ECI> r   = cartesian.get_position();
    const VelocityVector<ECI> v = cartesian.get_velocity();

    // Function for finding accel caused by perturbations
    const Date date                    = vehicle.get_state().get_epoch();
    AccelerationVector<ECI> accelPerts = forces->compute_forces(date, cartesian, vehicle, get_system());

    // Calculate R, N, and T
    const RTN rtnFrame                     = RTN::instantaneous(r, v);
    const AccelerationVector<RTN> accelRtn = rtnFrame.rotate_into_this_frame(accelPerts, date);

    const Acceleration& radialPert     = accelRtn.get_x();
    const Acceleration& normalPert     = accelRtn.get_y();
    const Acceleration& tangentialPert = accelRtn.get_z();

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
} // namespace astrea