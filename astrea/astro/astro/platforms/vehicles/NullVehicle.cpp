#include <astro/platforms/vehicles/NullVehicle.hpp>

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/State.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

NullVehicle::NullVehicle(const State& state0, const Mass& mass) :
    _state0(state0),
    _state(state0),
    _mass(mass)
{
}

NullVehicle* NullVehicle::clone() const { return new NullVehicle(*this); }

void NullVehicle::update_state(const State& state) { _state = state; }

State& NullVehicle::get_state() { return _state; }

const State& NullVehicle::get_initial_state() const { return _state0; }

Mass NullVehicle::get_mass() const { return _mass; }

std::string NullVehicle::get_name() const { return "NullVehicle"; }

RadiusVector<ECI> NullVehicle::get_inertial_position(const Date& date) const
{
    return { 0.0 * km, 0.0 * km, 0.0 * km };
}

VelocityVector<ECI> NullVehicle::get_inertial_velocity(const Date& date) const
{
    return { 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
}

AccelerationVector<ECI> NullVehicle::get_inertial_acceleration(const Date& date) const
{
    return { 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s) };
}

} // namespace astro
} // namespace astrea
