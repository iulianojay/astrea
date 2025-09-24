#include <astro/platforms/thrusters/Thruster.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::s;

std::size_t Thruster::get_id() const { return _id; }

Velocity Thruster::get_impulsive_delta_v() const
{
    return get_parameters().get_thrust() / get_parent()->get_mass() * s;
}

std::size_t Thruster::generate_id_hash() const
{
    // TODO: Fix the hashing. It's not unique
    return std::hash<Thrust>()(get_parameters().get_thrust());
}

} // namespace astro
} // namespace astrea