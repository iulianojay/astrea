#include <astro/systems/planetary_bodies/Uranus/Uranus.hpp>

#include <map>

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Uranus/UranusEphemerisTable.hpp>
#endif // ASTREA_BUILD_URANUS_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionUbFromSsb = get_position_at_impl<UranusEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionUbFromSsb; // TODO: Add correction for Uranus' position from Uranus barycenter
}

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea