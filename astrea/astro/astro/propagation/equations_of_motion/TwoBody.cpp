#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::si;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

TwoBody::TwoBody(const AstrodynamicsSystem& system) :
    EquationsOfMotion(system),
    mu(system.get_central_body()->get_mu())
{
}

OrbitalElementPartials TwoBody::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{
    // Extract
    const Cartesian cartesian = state.in_element_set<Cartesian>(get_system());

    const RadiusVector<ECI> r   = cartesian.get_position();
    const VelocityVector<ECI> v = cartesian.get_velocity();

    // mu/R^3
    const Distance R                 = r.norm();
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    return CartesianPartial(v, -muOverRadiusCubed * r);
}

} // namespace astro
} // namespace astrea