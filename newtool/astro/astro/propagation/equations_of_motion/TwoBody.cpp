#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


OrbitalElements TwoBody::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{

    const Cartesian cartesian = Cartesian(state, system);

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
    const Cartesian dsdt(vx * s, vy * s, vz * s, (-muOverRadiusCubed * x) * s, (-muOverRadiusCubed * y) * s, (-muOverRadiusCubed * z) * s);

    return OrbitalElements(dsdt);
}