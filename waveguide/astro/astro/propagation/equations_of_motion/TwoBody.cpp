#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::si;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace waveguide {
namespace astro {

OrbitalElementPartials TwoBody::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{
    // Extract
    const Cartesian cartesian = state.in<Cartesian>(get_system());

    const RadiusVector r   = cartesian.get_radius();
    const VelocityVector v = cartesian.get_velocity();

    // mu/R^3
    const Distance R                 = r.norm();
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    return CartesianPartial(v, -muOverRadiusCubed * r);
}

} // namespace astro
} // namespace waveguide