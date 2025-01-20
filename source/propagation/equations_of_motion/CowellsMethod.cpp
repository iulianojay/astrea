#include "CowellsMethod.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "astro/types/typedefs.hpp"
#include "astro/element_sets/orbital_elements/Cartesian.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;

OrbitalElements CowellsMethod::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const {

    // Extract
    const Cartesian cartesian = state.to_cartesian(system);
    const quantity<km>& x = cartesian.get_x();
    const quantity<km>& y = cartesian.get_y();
    const quantity<km>& z = cartesian.get_z();
    const quantity R = sqrt(x*x + y*y + z*z);

    const quantity<km/s>& vx = cartesian.get_vx();
    const quantity<km/s>& vy = cartesian.get_vy();
    const quantity<km/s>& vz = cartesian.get_vz();

    // mu/R^3
    const quantity muOverRadiusCubed = mu/(R*R*R);

    // Run find functions for force model
    const auto julianDate = vehicle.get_epoch().julian_day() + time.count<days>();
    AccelerationVector accelPerts = forces.compute_forces(julianDate, state, vehicle, system);

    // Derivative
    const OrbitalElements dsdt (Cartesian{
        vx,
        vy,
        vz,
        -muOverRadiusCubed*x + accelPerts[0],
        -muOverRadiusCubed*y + accelPerts[1],
        -muOverRadiusCubed*z + accelPerts[2]
    });

    return dsdt;
}