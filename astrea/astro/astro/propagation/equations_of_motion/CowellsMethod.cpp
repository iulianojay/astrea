#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

CowellsMethod::CowellsMethod(const AstrodynamicsSystem& system, const ForceModel& forces) :
    EquationsOfMotion(system),
    forces(&forces),
    mu(system.get_center()->get_mu())
{
}

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

constexpr std::size_t CowellsMethod::get_expected_set_id() const { return OrbitalElements::get_set_id<Cartesian>(); };

} // namespace astro
} // namespace astrea