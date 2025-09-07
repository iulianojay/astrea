#include <astro/platforms/thrusters/Thruster.hpp>

namespace astrea {
namespace astro {


std::size_t Thruster::get_id() const { return _id; }

Velocity Thruster::get_impulsive_delta_v() const
{
    return get_parameters().get_thrust() / get_parent()->get_mass() * 1.0 * mp_units::si::unit_symbols::s;
}

void Thruster::generate_id_hash()
{
    // TODO: Fix the hashing. It's not unique
    _id = std::hash<Thrust>()(get_parameters().get_thrust());
}

} // namespace astro
} // namespace astrea