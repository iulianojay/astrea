#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

OrbitalElementPartials CowellsMethod::operator()(const OrbitalElements& state, const Vehicle& vehicle) const
{
    // Extract
    const Cartesian cartesian = state.in_element_set<Cartesian>(get_system());

    const RadiusVector<ECI> r   = cartesian.get_position();
    const VelocityVector<ECI> v = cartesian.get_velocity();

    // mu/R^3
    const Distance R                 = r.norm();
    const quantity muOverRadiusCubed = mu / (R * R * R);

    // Run find functions for force model
    const Date date                    = vehicle.get_state().get_epoch();
    AccelerationVector<ECI> accelPerts = forces->compute_forces(date, cartesian, vehicle, get_system());

    // Derivative
    return CartesianPartial(v, -muOverRadiusCubed * r + accelPerts);
}

} // namespace astro
} // namespace astrea