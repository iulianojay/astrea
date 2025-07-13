#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::si;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astro {

OrbitalElementPartials TwoBody::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{
    const Cartesian cartesian = state.in<Cartesian>(get_system());

    // Extract
    const quantity<km>& x = cartesian.get_x();
    const quantity<km>& y = cartesian.get_y();
    const quantity<km>& z = cartesian.get_z();
    const quantity R      = sqrt(x * x + y * y + z * z);

    const quantity<km / s>& vx = cartesian.get_vx();
    const quantity<km / s>& vy = cartesian.get_vy();
    const quantity<km / s>& vz = cartesian.get_vz();

    // mu/R^3
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    const CartesianPartial dsdt(vx, vy, vz, (-muOverRadiusCubed * x), (-muOverRadiusCubed * y), (-muOverRadiusCubed * z));

    return dsdt;
}

} // namespace astro