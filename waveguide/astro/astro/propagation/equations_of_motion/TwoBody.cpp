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

OrbitalElementPartials TwoBody::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{
    const Cartesian cartesian = state.in<Cartesian>(get_system());

    // Extract
    const Distance& x = cartesian.get_x();
    const Distance& y = cartesian.get_y();
    const Distance& z = cartesian.get_z();
    const Distance R  = sqrt(x * x + y * y + z * z);

    const Velocity& vx = cartesian.get_vx();
    const Velocity& vy = cartesian.get_vy();
    const Velocity& vz = cartesian.get_vz();

    // mu/R^3
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    const CartesianPartial dsdt(vx, vy, vz, (-muOverRadiusCubed * x), (-muOverRadiusCubed * y), (-muOverRadiusCubed * z));

    return dsdt;
}

} // namespace astro
} // namespace waveguide