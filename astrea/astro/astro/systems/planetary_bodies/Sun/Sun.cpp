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

OrbitalElements Sun::get_keplerian_elements_at(const Date& date) const
{
    return OrbitalElements(get_keplerian_elements_at_impl<SunEphemerisTable>(date));
}

#endif // ASTREA_BUILD_SUN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea