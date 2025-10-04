#include <astro/systems/planetary_bodies/Sun/Sun.hpp>

#include <map>

#ifdef ASTREA_BUILD_SUN_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Sun/SunEphemerisTable.hpp>
#endif // ASTREA_BUILD_SUN_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> Sun::get_position_at(const Date& date) const
{
    return get_position_at_impl<SunEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_SUN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea